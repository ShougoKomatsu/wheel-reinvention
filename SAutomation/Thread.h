#include "stdafx.h"

extern BOOL g_bHalt;

extern HANDLE g_hThread1;
extern HANDLE g_hThread2;
extern HANDLE g_hThread3;
extern CString g_sFilePath1;
extern CString g_sFilePath2;
extern CString g_sFilePath3;

DWORD WINAPI GetKeyThread(LPVOID arg);

DWORD WINAPI GetStepKeyThread(LPVOID arg);
DWORD WINAPI CommandThread(LPVOID arg);