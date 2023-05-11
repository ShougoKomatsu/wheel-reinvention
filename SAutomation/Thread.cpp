#include "stdafx.h"
#include "Thread.h"
#include "Common.h"
#include "Automation.h"

HANDLE g_hThread1;
HANDLE g_hThread2;
HANDLE g_hThread3;

int g_iSceneData1;
int g_iSceneData2;
int g_iSceneData3;


CString g_sFilePath1;
CString g_sFilePath2;
CString g_sFilePath3;
BOOL g_bHalt;
BOOL g_bSuspend = FALSE;
LONGLONG g_llStepIn = 0;
LONGLONG g_llStepOut = 1;

DWORD WINAPI GetKeyThread(LPVOID arg)
{
	short shSpace;
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shSpace = GetKeyState(VK_SPACE);
		if((shSpace<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			g_bSuspend = TRUE;  
		}
		else        	
		{
			g_bSuspend = FALSE;
		}
		Sleep(1);
	}

	return 0;
} 
DWORD WINAPI GetStepKeyThread(LPVOID arg)
{
	short shStep;
	short shCtrl;
	short shShift;
	while(1)
	{

		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shStep = GetKeyState(0x53);
		if((shStep<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			if(g_llStepOut==1){g_llStepIn=1;}
		}

		Sleep(1);
	}
	return 0;
} 

DWORD WINAPI CommandThread(LPVOID arg)
{
	HANDLE hGetKey;
	HANDLE hGetStepKey;
	DWORD dwThreadID;
	int* iSceneData;
	hGetKey = CreateThread(NULL, 0, GetKeyThread, NULL, 0, &dwThreadID);
	hGetStepKey = CreateThread(NULL, 0, GetStepKeyThread, NULL, 0, &dwThreadID);
	CStringArray saCommands;
	if(((*(int*)arg)&0x03) ==1)
	{
		ReadTextFile(g_sFilePath1,&saCommands);
		g_iSceneData1=0;
		iSceneData=&g_iSceneData1;
	} 
	if(((*(int*)arg)&0x03) ==2)
	{
		ReadTextFile(g_sFilePath2,&saCommands);
		g_iSceneData2=2;
		iSceneData=&g_iSceneData2;
	}
	if(((*(int*)arg)&0x03) ==3)
	{
		ReadTextFile(g_sFilePath3,&saCommands);
		g_iSceneData3=3;
		iSceneData=&g_iSceneData3;
	}


	int iLoop;
	iLoop = (*(int*)arg)>>4;
	(*(int*)arg) = 0;  

	int iListLength;
	int iRet;
	for(int j=0; j<iLoop; j++)
	{
		iListLength =(int) saCommands.GetCount();
		for(int i=0; i<iListLength; i++)
		{
			if(g_bHalt == TRUE){g_bHalt = FALSE;return 0;}
			iRet = OperateCommand(iSceneData, &g_bHalt, &g_bSuspend, &g_llStepIn, saCommands.GetAt(i));
			if(iRet != 0){g_bHalt = FALSE; return 0;}
			g_llStepOut=1;
			g_llStepIn=0;
		}
	}
	TerminateThread(hGetKey, 0);
	TerminateThread(hGetStepKey, 0);
	return 0;
}
BOOL WaitUntilCtrlShiftReleased()
{
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_LSHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		if((shShift>=0)&&(shCtrl>=0)) 
		{
			return TRUE;
		}

		Sleep(1);
	}
	return FALSE;
}