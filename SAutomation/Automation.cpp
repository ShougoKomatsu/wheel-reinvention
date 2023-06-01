#include "stdafx.h"
#include "Automation.h"
#include "windows.h"

#include <TlHelp32.h>
int Maximize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MAXIMIZE );
	return 0;
}

int Minimize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MINIMIZE );
	return 0;
}


int SetWindowForward(CString sWindowName)
{
	HWND hwnd;
	hwnd = FindWindow(nullptr,sWindowName);
	if(hwnd <=0){return -1;}


	if(SetForegroundWindow(hwnd) == FALSE){return -1;};
	return 0;
}
int WindowSize(CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return -1;}

	iWidth = _ttoi(saData->GetAt(0));
	iHeight = _ttoi(saData->GetAt(1));
	iLeft = rect.left;
	iTop = rect.top;
	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOMOVE) ;
	return 0;
}
int WindowPos(CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return -1;}
	
	iWidth = rect.Width();
	iHeight = rect.Height();
	iLeft = _ttoi(saData->GetAt(0));
	iTop = _ttoi(saData->GetAt(1));

	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOSIZE) ;
	return 0;
}

int K_Sleep(LPVOID Halt, LPVOID Suspend, DWORD SleepMilliSec)
{
	if((Halt==NULL)&&(Suspend == NULL)){Sleep(SleepMilliSec);return 0;}



	if(Halt==NULL)
	{
		ULONGLONG ullStartMilliSec;
		ULONGLONG ullSuspendStartMilliSec;
		ULONGLONG ullSuspendedMilliSec;
		ullStartMilliSec = GetTickCount64();
		ullSuspendedMilliSec=0;
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
		{
			if((*(int*)Suspend) == 1)
			{
				ullSuspendStartMilliSec = GetTickCount64();
				while((*(int*)Suspend) == 1)
				{
					Sleep(1);
				}
				ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
			}
			Sleep(1);
		}
		return 0;
	}

	if(Suspend==NULL)
	{
		ULONGLONG ullStartMilliSec;
		ullStartMilliSec = GetTickCount64();
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult)
		{
			if((*(int*)Halt) == 1){return -1;}
			Sleep(1);
		}
		return 0;
	}

	ULONGLONG ullStartMilliSec;
	ULONGLONG ullSuspendStartMilliSec;
	ULONGLONG ullSuspendedMilliSec;
	ullStartMilliSec = GetTickCount64();
	ullSuspendedMilliSec=0;
	while(GetTickCount64()<ullStartMilliSec+SleepMilliSec/g_dSpeedMult+ullSuspendedMilliSec)
	{
		if((*(int*)Halt) == 1){return -1;}
		if((*(int*)Suspend) == 1)
		{
			ullSuspendStartMilliSec = GetTickCount64();
			while((*(int*)Suspend) == 1)
			{
				if((*(int*)Halt) == 1){return -1;}
				Sleep(1);
			}
			ullSuspendedMilliSec += GetTickCount64() - ullSuspendStartMilliSec;
		}
		Sleep(1);
	}


	return 0;
}


int Break(LPVOID Halt, LONGLONG* Special1)
{
	while ((*(int*)Special1) == 0)
	{
		if((*(int*)Halt) == 1){return -1;}
		Sleep(1);
	}
	return 0;
}

int KeyDownAndUp(BYTE bySendKey)
{
	INPUT inputs[2] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	inputs[1].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=bySendKey;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2,inputs,sizeof(INPUT)); 
	return 0;
}

int KeyDownAndUpUnicode(TCHAR tch)
{
	INPUT input[2];
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = tch;
	input[0].ki.dwFlags = KEYEVENTF_UNICODE;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = tch;
	input[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	input[1].ki.time = 0;
	input[1].ki.dwExtraInfo = 0;

	SendInput(2, input, sizeof(INPUT));
	return 0;
}

int KeyDown(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;

	SendInput(1,inputs,sizeof(INPUT)); 
	return 0;
}

int KeyUp(BYTE bySendKey)
{
	INPUT inputs[1] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=bySendKey;
	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1,inputs,sizeof(INPUT)); 
	return 0;
}


int GetKeyCode(CString sData, BYTE* byData)
{
	BYTE byDataLocal;
	byDataLocal = 0;
	if(sData.Compare(_T("ctrl"))==0){*byData= VK_CONTROL;return 0;}
	if(sData.Compare(_T("shift"))==0){*byData= VK_SHIFT;return 0;}

	if(sData.GetLength()==2)
	{
		if(sData.Compare(_T("f1"))==0){*byData = VK_F1;return 0;}
		if(sData.Compare(_T("f2"))==0){*byData = VK_F2;return 0;}
		if(sData.Compare(_T("f3"))==0){*byData = VK_F3;return 0;}
		if(sData.Compare(_T("f4"))==0){*byData = VK_F4;return 0;}
		if(sData.Compare(_T("f5"))==0){*byData = VK_F5;return 0;}
		if(sData.Compare(_T("f6"))==0){*byData = VK_F6;return 0;}
		if(sData.Compare(_T("f7"))==0){*byData = VK_F7;return 0;}
		if(sData.Compare(_T("f8"))==0){*byData = VK_F8;return 0;}
		if(sData.Compare(_T("f9"))==0){*byData = VK_F9;return 0;}
	}

	if(sData.GetLength()==3)
	{
		if(sData.Compare(_T("f10"))==0){*byData = VK_F10;return 0;}
		if(sData.Compare(_T("f11"))==0){*byData = VK_F11;return 0;}
		if(sData.Compare(_T("f12"))==0){*byData = VK_F12;return 0;}
		if(sData.Compare(_T("f13"))==0){*byData = VK_F13;return 0;}
		if(sData.Compare(_T("f14"))==0){*byData = VK_F14;return 0;}
		if(sData.Compare(_T("f15"))==0){*byData = VK_F15;return 0;}
		if(sData.Compare(_T("f16"))==0){*byData = VK_F16;return 0;}
		if(sData.Compare(_T("f17"))==0){*byData = VK_F17;return 0;}
		if(sData.Compare(_T("f18"))==0){*byData = VK_F18;return 0;}
		if(sData.Compare(_T("f19"))==0){*byData = VK_F19;return 0;}

		if(sData.Compare(_T("f20"))==0){*byData = VK_F20;return 0;}
		if(sData.Compare(_T("f21"))==0){*byData = VK_F21;return 0;}
		if(sData.Compare(_T("f22"))==0){*byData = VK_F22;return 0;}
		if(sData.Compare(_T("f23"))==0){*byData = VK_F23;return 0;}
		if(sData.Compare(_T("f24"))==0){*byData = VK_F24;return 0;}
	}

	if(sData.Compare(_T("lshift"))==0){*byData = VK_SHIFT;return 0;}
	if(sData.Compare(_T("rshift"))==0){*byData = VK_SHIFT;return 0;}
	if(sData.Compare(_T("lctrl"))==0){*byData = VK_CONTROL;return 0;}
	if(sData.Compare(_T("rctrl"))==0){*byData = VK_CONTROL;return 0;}
	if(sData.Compare(_T("lalt"))==0){*byData = VK_MENU;return 0;}
	if(sData.Compare(_T("ralt"))==0){*byData = VK_MENU;return 0;}

	if(sData.Compare(_T("tab"))==0){*byData = VK_TAB;return 0;}
	if(sData.Compare(_T("enter"))==0){*byData = VK_RETURN;return 0;}
	if(sData.Compare(_T("return"))==0){*byData = VK_RETURN;return 0;}
	if(sData.Compare(_T("space"))==0){*byData = VK_SPACE;return 0;}


	if(sData.Left(2).Compare(_T("0x"))!=0){return -1;}
	if(sData.GetLength()!=4){return -1;}

	char cChar;
	cChar = sData.GetAt(2);
	if((cChar >= '0') && (cChar<= '9'))
	{
		byDataLocal = cChar-'0';
	}
	else if((cChar >= 'a') && (cChar<= 'f'))
	{
		byDataLocal = cChar-'a' + 10;
	}
	else
	{
		return -1;
	}
	byDataLocal *= 0x10;

	cChar = sData.GetAt(3);
	if((cChar >= '0') && (cChar<= '9'))
	{
		byDataLocal += cChar-'0';
	}
	else if((cChar >= 'a') && (cChar<= 'f'))
	{
		byDataLocal += cChar-'a' + 10;
	}
	else
	{
		return -1;
	}
	*byData = byDataLocal;
	return 0;
}
BOOL isProcessExist(CString sExePath)
{
		int iFoundPosLast;
	int iFoundPos;

	iFoundPos = 0;
	while(iFoundPos>=0)
	{
		iFoundPosLast = iFoundPos;
		iFoundPos = sExePath.Find(_T("\\"), iFoundPosLast+1);
	}
	CString sExeName;
	if(iFoundPosLast==0){return FALSE;}
	sExeName.Format(_T("%s"), sExePath.Right(sExePath.GetLength()-iFoundPosLast-1));

	PROCESSENTRY32 entry;
	entry.dwSize=sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(Process32First(snapshot,&entry)==TRUE)
	{
		while(Process32Next(snapshot, &entry)==TRUE)
		{
			if(sExeName.Compare( entry.szExeFile)==0)
			{
				CloseHandle(snapshot);
				return TRUE;

			}
		}
	}
				CloseHandle(snapshot);
	return FALSE;
}
int RunExe(CString sExePath)
{
	BOOL bAlreadyExist;

	bAlreadyExist = isProcessExist(sExePath);
	if(bAlreadyExist==TRUE){return 0;}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, NULL, sizeof(si));
	si.cb=sizeof(si);
	memset(&pi, NULL, sizeof(pi));

	wchar_t* szTmp;
	szTmp = new wchar_t[wcslen(sExePath) + 1];
	memset(szTmp, NULL, sizeof(szTmp)/sizeof(wchar_t));
	wcscpy_s(szTmp, wcslen(sExePath) + 1, sExePath);

	CreateProcess(NULL,  szTmp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	delete [] szTmp;
	return 0;
}

int WaitForKey(LPVOID Halt, LPVOID Suspend, CStringArray* saData)
{

	int iWaitOn;

	BYTE byKey;
	int iRet;
	iRet = GetKeyCode(saData->GetAt(0),&byKey);
	if(iRet < 0){return iRet;}

	if(saData->GetAt(1).Compare(_T("on"))==0){iWaitOn=1;}
	else if(saData->GetAt(1).Compare(_T("off"))==0){iWaitOn=0;}
	else{return -1;}



	short shKey;
	while(1)
	{
		shKey = GetAsyncKeyState (byKey);
		if(iWaitOn==1)
		{
			if((shKey<0)) {return 0;}

		}
		else
		{
			if((shKey>=0)) {return 0;}
		}


		if(K_Sleep(Halt, Suspend, 1)<0){return -1;}
	}
	return 0;
}

int KeyDownAndUp(CStringArray* saData)
{
	BYTE bySendKey;

	if(saData->GetAt(0).Left(2).Compare(_T("0x"))==0)
	{
		GetKeyCode(saData->GetAt(0), &bySendKey);
		return KeyDownAndUp(bySendKey);
	}

	if(saData->GetAt(0).Compare(_T("©"))==0){return KeyDownAndUp(VK_LEFT);}
	if(saData->GetAt(0).Compare(_T("ª"))==0){return KeyDownAndUp(VK_UP);}
	if(saData->GetAt(0).Compare(_T("¨"))==0){return KeyDownAndUp(VK_RIGHT);}
	if(saData->GetAt(0).Compare(_T("«"))==0){return KeyDownAndUp(VK_DOWN);}

	if(saData->GetAt(0).Compare(_T("_"))==0){return KeyDownAndUpUnicode(L'_');}
	if(saData->GetAt(0).Compare(_T("."))==0){return KeyDownAndUpUnicode(L'.');}
	if(saData->GetAt(0).Compare(_T("/"))==0){return KeyDownAndUpUnicode(L'/');}
	if(saData->GetAt(0).Compare(_T("*"))==0){return KeyDownAndUpUnicode(L'*');}
	if(saData->GetAt(0).Compare(_T("-"))==0){return KeyDownAndUpUnicode(L'-');}
	if(saData->GetAt(0).Compare(_T("@"))==0){return KeyDownAndUpUnicode(L'@');}
	if(saData->GetAt(0).Compare(_T("["))==0){return KeyDownAndUpUnicode(L'[');}
	if(saData->GetAt(0).Compare(_T("]"))==0){return KeyDownAndUpUnicode(L']');}
	if(saData->GetAt(0).Compare(_T("{"))==0){return KeyDownAndUpUnicode(L'{');}
	if(saData->GetAt(0).Compare(_T("}"))==0){return KeyDownAndUpUnicode(L'}');}
	if(saData->GetAt(0).Compare(_T(";"))==0){return KeyDownAndUpUnicode(L';');}
	if(saData->GetAt(0).Compare(_T(":"))==0){return KeyDownAndUpUnicode(L':');}
	if(saData->GetAt(0).Compare(_T("|"))==0){return KeyDownAndUpUnicode(L'|');}
	if(saData->GetAt(0).Compare(_T("\\"))==0){return KeyDownAndUpUnicode(L'\\');}
	if(saData->GetAt(0).Compare(_T("^"))==0){return KeyDownAndUpUnicode(L'^');}
	if(saData->GetAt(0).Compare(_T("="))==0){return KeyDownAndUpUnicode(L'=');}
	if(saData->GetAt(0).Compare(_T("-"))==0){return KeyDownAndUpUnicode(L'-');}
	if(saData->GetAt(0).Compare(_T("`"))==0){return KeyDownAndUpUnicode(L'`');}
	if(saData->GetAt(0).Compare(_T(">"))==0){return KeyDownAndUpUnicode(L'>');}
	if(saData->GetAt(0).Compare(_T("<"))==0){return KeyDownAndUpUnicode(L'<');}
	if(saData->GetAt(0).Compare(_T("?"))==0){return KeyDownAndUpUnicode(L'?');}
	if(saData->GetAt(0).Compare(_T("!"))==0){return KeyDownAndUpUnicode(L'!');}
	if(saData->GetAt(0).Compare(_T("\""))==0){return KeyDownAndUpUnicode(L'\"');}
	if(saData->GetAt(0).Compare(_T("#"))==0){return KeyDownAndUpUnicode(L'#');}
	if(saData->GetAt(0).Compare(_T("$"))==0){return KeyDownAndUpUnicode(L'$');}
	if(saData->GetAt(0).Compare(_T("%%"))==0){return KeyDownAndUpUnicode(L'%');}
	if(saData->GetAt(0).Compare(_T("&"))==0){return KeyDownAndUpUnicode(L'&');}
	if(saData->GetAt(0).Compare(_T("'"))==0){return KeyDownAndUpUnicode(L'\'');}
	if(saData->GetAt(0).Compare(_T("("))==0){return KeyDownAndUpUnicode(L'(');}
	if(saData->GetAt(0).Compare(_T(")"))==0){return KeyDownAndUpUnicode(L')');}
	bySendKey = (BYTE)(saData->GetAt(0).GetAt(0));


	if((bySendKey>=0x00)&&(bySendKey<=0x2F))
	{
		return KeyDownAndUp(bySendKey);
	}

	if((bySendKey>='a')&&(bySendKey<='z'))
	{
		bySendKey+='A'-'a';
		return KeyDownAndUp(bySendKey);
	}

	if((bySendKey>='A')&&(bySendKey<='Z'))
	{
		KeyDown(VK_SHIFT);
		KeyDownAndUp(bySendKey);
		KeyUp(VK_SHIFT);
		return 0;
	}

	return KeyDown(bySendKey);
}


int KeyDown(CStringArray* saData)
{
	BYTE bySendKey;

	if(saData->GetAt(0).Left(2).Compare(_T("0x"))==0)
	{
		GetKeyCode(saData->GetAt(0), &bySendKey);
		return KeyDown(bySendKey);
	}

	bySendKey = (BYTE)(saData->GetAt(0).GetAt(0));


	if((bySendKey>=0x00)&&(bySendKey<=0x2F))
	{
		return KeyDown(bySendKey);
	}

	if((bySendKey>='a')&&(bySendKey<='z'))
	{
		bySendKey+='A'-'a';
		return KeyDown(bySendKey);
	}

	return KeyDown(bySendKey);
}



int KeyUp(CStringArray* saData)
{
	BYTE bySendKey;

	if(saData->GetAt(0).Left(2).Compare(_T("0x"))==0)
	{
		GetKeyCode(saData->GetAt(0), &bySendKey);
		return KeyUp(bySendKey);
	}

	bySendKey = (BYTE)(saData->GetAt(0).GetAt(0));


	if((bySendKey>=0x00)&&(bySendKey<=0x2F))
	{
		return KeyUp(bySendKey);
	}

	if((bySendKey>='a')&&(bySendKey<='z'))
	{
		bySendKey+='A'-'a';
		return KeyUp(bySendKey);
	}

	return KeyUp(bySendKey);
}

int OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine)
{
	int iCommandType=COMMAND_UNDEFINED;
	BOOL bRet;
	int iRet;
	CStringArray saData;
	bRet = PerseCommand(iSceneData, sDataLine, &iCommandType, &saData);
	if(iCommandType == COMMAND_NOTING){return 0;}
	if(bRet != TRUE){return -1;}

	switch(iCommandType)
	{
	case COMMAND_MOUSE_L_DOWN:
		{
			MoveMouse(&saData);
			MouseLDown(&saData);
			return 0;
		}

	case COMMAND_MOUSE_L_UP:
		{
			MoveMouse(&saData);
			MouseLUp(&saData);
			return 0;
		}

	case COMMAND_MOUSE_MOVE:
		{
			MoveMouse(&saData);
			return 0;
		}
	case COMMAND_DELAY:
		{
			iRet = K_Sleep(Halt, Suspend, _ttoi(saData.GetAt(0)));
			return iRet;
		}
	case COMMAND_WHEEL:
		{
			MouseVWheel(&saData);
			return 0;
		}
	case COMMAND_MOUSE_L_CLICK:
		{
			MouseLClick(&saData);
			return 0;
		}
	case COMMAND_KEY_DOWN_UP:
		{
			iRet = KeyDownAndUp(&saData);
			return iRet;
		}

	case COMMAND_KEY_DOWN:
		{
			iRet = KeyDown(&saData);
			return iRet;
		}

	case COMMAND_KEY_UP:
		{
			iRet = KeyUp(&saData);
			return iRet;
		}
	case COMMAND_WAIT:
		{
			return WaitForKey(Halt, Suspend, &saData);
		}
	case COMMAND_MAXIMIZE:
		{
			return Maximize();
		}
	case COMMAND_MINIMIZE:
		{
			return Minimize();
		}
	case COMMAND_WINDOW_FORWARD:
		{
			return SetWindowForward(saData.GetAt(0));
		}
	case COMMAND_WINDOW_SIZE:
		{
			return WindowSize(&saData);
		}
	case COMMAND_WINDOW_POS:
		{
			return WindowPos(&saData);
		}
	case COMMAND_RUN:
		{
			return RunExe(saData.GetAt(0));
		}
	case COMMAND_NOTING:{return 0;}
	default:{return -1;}
	}
	return iRet;
}