#include "stdafx.h"
#include "Automation.h"
#include "windows.h"

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
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec+ullSuspendedMilliSec)
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
		while(GetTickCount64()<ullStartMilliSec+SleepMilliSec)
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
	while(GetTickCount64()<ullStartMilliSec+SleepMilliSec+ullSuspendedMilliSec)
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

int WaitForKey(LPVOID Halt, LPVOID Suspend, BYTE byKey)
{
	
	short shKey;
	while(1)
	{
		shKey = GetAsyncKeyState (byKey);
		if((shKey>=0)) 
		{
			return 0;
		}

		
		if(K_Sleep(Halt, Suspend, 1)<0){return -1;}
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


int atoi_hex(CString sData, BYTE* byData)
{
	BYTE byDataLocal;
	byDataLocal = 0;

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

int KeyDownAndUp(CStringArray* saData)
{
	BYTE bySendKey;

	if(saData->GetAt(0).Left(2).Compare(_T("0x"))==0)
	{
		atoi_hex(saData->GetAt(0), &bySendKey);
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
		atoi_hex(saData->GetAt(0), &bySendKey);
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
		atoi_hex(saData->GetAt(0), &bySendKey);
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
	case COMMAND_BREAK:
		{
			iRet = Break(Halt, Special1);
			return iRet;
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
	case COMMAND_WAIT_FOR_CTRL_RELEASED:
		{
			return WaitForKey(Halt, Suspend, VK_CONTROL);
		}
	case COMMAND_WAIT_FOR_SHIFT_RELEASED:
		{
			return WaitForKey(Halt, Suspend, VK_SHIFT);
		}
	case COMMAND_NOTING:{return 0;}
	default:{return -1;}
	}
	return iRet;
}