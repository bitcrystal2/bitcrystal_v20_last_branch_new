#include "mhook.h"
#ifdef USE_SUBHOOK
#include "subhook/hookerpref.c"
void Mhook_MyInit()
{
	if(mhooks_bool_init==TRUE)
		return;
	int i;
	for(i = 0; i < MHOOKS_MAX_SUPPORTED_HOOKS; i++)
	{
		mhooks_subhooks[i]=NULL;
	}
	mhooks_bool_init=TRUE;
}

BOOL Mhook_SetHookEx(PVOID ppSystemFunction, PVOID pHookFunction) {
	return Mhook_SetHookEx((PVOID*)(&ppSystemFunction),pHookFunction);
}

BOOL Mhook_UnhookEx(PVOID ppHookedFunction) {
	return Mhook_Unhook((PVOID*)(&ppHookedFunction));
}

BOOL Mhook_SetHook(PVOID * ppSystemFunctionP, PVOID pHookFunction) {
	Mhook_MyInit();
	if(ppSystemFunctionP==NULL||pHookFunction==NULL)
	{
		return FALSE;
	}
	PVOID ppSystemFunction=(void*)(*ppSystemFunctionP);
	if(ppSystemFunction==NULL)
		return FALSE;
	if(mhooks_subhooks_count>=MHOOKS_MAX_SUPPORTED_HOOKS)
	{
		return FALSE;
	} else if(mhooks_subhooks_count<0)
	{
		mhooks_subhooks_count=0;
	}
	mhooks_subhooks[mhooks_subhooks_count]=subhook_new(ppSystemFunction, pHookFunction);
	if(mhooks_subhooks[mhooks_subhooks_count]==NULL)
	{
		return FALSE;
	}
	subhook_install(mhooks_subhooks[mhooks_subhooks_count]);
	if(subhook_is_installed(mhooks_subhooks[mhooks_subhooks_count]))
	{
		void * rr= subhook_get_trampoline(mhooks_subhooks[mhooks_subhooks_count]);
		if(rr==NULL)
		{
			subhook_remove(mhooks_subhooks[mhooks_subhooks_count]);
			subhook_free(mhooks_subhooks[mhooks_subhooks_count]);
			mhooks_subhooks[mhooks_subhooks_count]=NULL;
			return FALSE;
		}
		*ppSystemFunctionP=(void*)rr;
	}
	mhooks_subhooks_count++;
	return TRUE;
}
BOOL Mhook_Unhook(PVOID * ppHookedFunctionP) {
	Mhook_MyInit();
	if(ppHookedFunctionP==NULL)
		return FALSE;
	PVOID ppHookedFunction=(void*)(*ppHookedFunctionP);
	if(ppHookedFunction==NULL)
		return FALSE;
	int i;
	void * src=NULL;
	if(ppHookedFunction!=NULL)
	{
		for(i = 0; i < mhooks_subhooks_count; i++)
		{
			if(mhooks_subhooks[i]==NULL)
			{
				continue;
			}
			src=(void*)subhook_get_src(mhooks_subhooks[i]);
			if(src==ppHookedFunction)
			{
				*ppHookedFunctionP=(void*)src;
				subhook_remove(mhooks_subhooks[i]);
				subhook_free(mhooks_subhooks[i]);
				mhooks_subhooks[i]=NULL;
				if(i+1==mhooks_subhooks_count)
				{
					mhooks_subhooks_count--;
				}
				return TRUE;
			}
		}
		return FALSE;
	} else {
			i = mhooks_subhooks_count - 1;
			if(i<0)
			{
				return FALSE;
			}
			if(mhooks_subhooks[i]==NULL)
				return FALSE;
			src=(void*)subhook_get_src(mhooks_subhooks[i]);
			*ppHookedFunctionP=(void*)src;
			subhook_remove(mhooks_subhooks[i]);
			subhook_free(mhooks_subhooks[i]);
			mhooks_subhooks[i]=NULL;
			mhooks_subhooks_count--;
			return TRUE;
	}
	return FALSE;
}
#else
	#ifdef OS_WIN
		#include "cpu.c"
		#include "disasm_n.c"
		#include "mhook_lib/mhook-lib/mhook.c"
		BOOL Mhook_SetHookEx(PVOID ppSystemFunction, PVOID pHookFunction) {
			return Mhook_SetHook((PVOID*)(&ppSystemFunction),pHookFunction);
		}
		BOOL Mhook_UnhookEx(PVOID ppHookedFunction) {
			return Mhook_Unhook((PVOID*)(&ppHookedFunction));
		}
	
		void Mhook_MyInit()
		{
			return;
		}
	#elif defined(OS_UNIX_STRUCT)
		#include "subhook/windows_defs.c"
		BOOL Mhook_SetHook(PVOID * ppSystemFunctionP, PVOID pHookFunction) {
			return FALSE;
		}
		
		BOOL Mhook_Unhook(PVOID * ppHookedFunctionP) {
			return FALSE;
		}
		
		BOOL Mhook_SetHookEx(PVOID ppSystemFunction, PVOID pHookFunction) {
			return FALSE;
		}
		
		BOOL Mhook_UnhookEx(PVOID ppHookedFunction) {
			return FALSE;
		}
	
		void Mhook_MyInit()
		{
			return;
		}
	#else
		#include "subhook/windows_defs.c"
		BOOL Mhook_SetHook(PVOID * ppSystemFunctionP, PVOID pHookFunction) {
			return FALSE;
		}
		
		BOOL Mhook_Unhook(PVOID * ppHookedFunctionP) {
			return FALSE;
		}
		
		BOOL Mhook_SetHookEx(PVOID ppSystemFunction, PVOID pHookFunction) {
			return FALSE;
		}
		
		BOOL Mhook_UnhookEx(PVOID ppHookedFunction) {
			return FALSE;
		}
	
		void Mhook_MyInit()
		{
			return;
		}
	#endif
#endif