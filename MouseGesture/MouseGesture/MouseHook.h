
#include "stdafx.h"

#ifndef MOUSE_HOOK
#define MOUSE_HOOK
 LRESULT CALLBACK  MouseHookProc(int code, WPARAM wParam, LPARAM lParam);
 
extern HHOOK g_hhook;
#endif