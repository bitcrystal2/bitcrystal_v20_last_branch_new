#ifndef WINDOWS_DEFS_H
#define WINDOWS_DEFS_H
#include "my_predef.h"
#ifndef OS_WIN
typedef void * PVOID;
typedef int                 BOOL;
#ifndef FALSE
#define FALSE               0
#endif
#ifndef TRUE
#define TRUE                1
#endif
#ifdef _M_IX86
#define _M_IX86_X64
#elif defined _M_X64
#define _M_IX86_X64
#endif
//#define NULL ( (void *) 0)
#define NULL 0
#define CONST const
typedef CONST void *LPCVOID;
typedef void *LPVOID;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef char CHAR;
typedef char CCHAR;
typedef DWORD COLORREF;
typedef BYTE BOOLEAN;
typedef long long __int64;
typedef unsigned __int64 DWORDLONG;
#if defined(_WIN64)
 typedef __int64 LONG_PTR; 
#else
 typedef long LONG_PTR;
#endif
typedef LONG_PTR LPARAM;
#if defined(_WIN64)
 typedef unsigned __int64 ULONG_PTR;
#else
 typedef unsigned long ULONG_PTR;
#endif
typedef ULONG_PTR SIZE_T;
#if !defined(_M_IX86)
 typedef unsigned __int64 ULONGLONG;
#else
 typedef double ULONGLONG;
#endif
typedef unsigned long size_t;
typedef unsigned int ULONG32;
typedef unsigned __int64 ULONG64;
typedef unsigned short USHORT;
typedef CHAR *LPSTR;
typedef CONST CHAR *PCSTR;
typedef CHAR *PSTR;
typedef USHORT WCHAR;
typedef WCHAR *PWSTR;
typedef WCHAR *LPWSTR;
typedef DWORD *PDWORD;
typedef DWORD *LPDWORD;
typedef PVOID HANDLE;
typedef HANDLE *LPHANDLE;
#ifndef _UNICODE
#ifdef UNICODE 
#define _UNICODE UNICODE
#endif
#else
#ifndef UNICODE
#define UNICODE _UNICODE
#endif
#endif
#ifdef UNICODE
 typedef WCHAR TBYTE;
#else
 typedef unsigned char TBYTE;
#endif

#ifdef UNICODE
 typedef LPWSTR PTSTR;
#else typedef LPSTR PTSTR;
#endif
#ifdef UNICODE
 typedef LPWSTR LPTSTR;
#else
 typedef LPSTR LPTSTR;
#endif
typedef struct _UNICODE_STRING {
  USHORT  Length;
  USHORT  MaximumLength;
  PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
#ifdef _UNICODE
#define L(str) L##str
#else
#define L(str) str
#endif
#define __stdcall
#define CALLBACK __stdcall
#define WINAPI __stdcall
typedef struct _MEMORY_BASIC_INFORMATION {
  PVOID  BaseAddress;
  PVOID  AllocationBase;
  DWORD  AllocationProtect;
  SIZE_T RegionSize;
  DWORD  State;
  DWORD  Protect;
  DWORD  Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
BOOL WINAPI VirtualProtect(LPVOID lpAddress,SIZE_T dwSize,DWORD  flNewProtect,PDWORD lpflOldProtect);
SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength);
LPVOID WINAPI VirtualAlloc(LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect);
#else
#include <windows.h>
#endif
#define _LONG_PTR(a) ((LONG_PTR)((a)))
#define _ULONG_PTR(a) ((ULONG_PTR)((a)))
typedef struct _vma_it_func
{
	unsigned long long start_address;
	unsigned long long end_address;
	unsigned long long page_size;
	unsigned long long page_alignment_size;
    unsigned long long free_pages;
    unsigned long long free_pages_size;
    unsigned long long reserved_pages_size;
    unsigned long long reserved_pages;
	unsigned long long size;
	unsigned long long base_start_address;
	unsigned long long base_end_address;
	unsigned int base_flags;
	unsigned char ret;
} vma_it_func;
int vma_iterate_func(void *data,unsigned long long start, unsigned long long end,unsigned int flags);
int vma_iterate_full_addressing_func(void *data,unsigned long long start, unsigned long long end,unsigned int flags);
#endif