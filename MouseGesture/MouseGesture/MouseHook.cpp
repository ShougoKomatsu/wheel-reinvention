#include "stdafx.h"
#include "MouseHook.h"
#include "math.h"

BOOL SendEscape()
{
	INPUT inputs[2] = {};
	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=VK_ESCAPE;

	inputs[0].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=VK_ESCAPE;
	inputs[1].ki.dwFlags=KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));

	return 0;
}

BOOL SendFowardPage()
{
	INPUT inputs[2] = {};
	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=VK_BROWSER_FORWARD;

	inputs[0].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=VK_BROWSER_FORWARD;
	inputs[1].ki.dwFlags=KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));

	return 0;
}

BOOL SendBackPage()
{
	INPUT inputs[2] = {};
	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=VK_BROWSER_BACK;

	inputs[0].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=VK_BROWSER_BACK;
	inputs[1].ki.dwFlags=KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));

	return 0;
}

BOOL SendRefleshPage()
{
	INPUT inputs[2] = {};
	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=VK_BROWSER_REFRESH;

	inputs[0].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=VK_BROWSER_REFRESH;
	inputs[1].ki.dwFlags=KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));

	return 0;
}


BOOL SendClose()
{
	INPUT inputs[4] = {};

	inputs[0].type=INPUT_KEYBOARD;
	inputs[0].ki.wVk=VK_CONTROL;
	inputs[0].ki.dwFlags=0;

	inputs[1].type=INPUT_KEYBOARD;
	inputs[1].ki.wVk=0x57;
	inputs[1].ki.dwFlags=0;

	//SendInput(2, inputs, sizeof(INPUT));

//	Sleep(10);
	
	inputs[2].type=INPUT_KEYBOARD;
	inputs[2].ki.wVk=0x57;
	inputs[2].ki.dwFlags=KEYEVENTF_KEYUP;

	inputs[3].type=INPUT_KEYBOARD;
	inputs[3].ki.wVk=VK_CONTROL;
	inputs[3].ki.dwFlags=KEYEVENTF_KEYUP;

	SendInput(4, inputs, sizeof(INPUT));
	return 0;
}


int g_x_start;
int g_g_y_start;

int g_iRightHolding = 0;
int g_iLeftHolding = 0;

int g_iMoving;
int g_path[10];
int g_pathIndex=0;
int g_iAnyAction=0;

void trim(int* iPathIn, int iPathNumIn, int* iPathOut, int* iPathNumOut)
{
	if(iPathNumIn<=0){*iPathNumOut=0;return;}
	*iPathNumOut=1;
	iPathOut[0]=iPathIn[0];
	for(int i=1; i<iPathNumIn; i++)
	{
		if(iPathIn[i] != iPathOut[(*iPathNumOut)-1])
		{
			iPathOut[*iPathNumOut]=iPathIn[i];
			(*iPathNumOut)++;
		}
	}
}

LRESULT CALLBACK  MouseHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	CString sss;
	switch(wParam)
	{
	case WM_MOUSEMOVE:
		{
			if(g_iRightHolding!=1){break;}
			if(g_pathIndex>=10){break;}

			POINT p;
			GetCursorPos(&p);
			double ddx, ddy;
			ddx = p.x-g_x_start;
			ddy = p.y-g_g_y_start;
			if((fabs(ddx)>=50) || (fabs(ddy)>=50))
			{
				if(fabs(ddx)>fabs(ddy))
				{
					if(ddx>0)
					{
						if(g_pathIndex>=2)
						{
							if(g_path[g_pathIndex-1]==0){g_x_start=p.x;g_g_y_start=p.y;break;}
						}
						g_path[g_pathIndex]=0;
					}
					else
					{
						if(g_pathIndex>=2)
						{
							if(g_path[g_pathIndex-1]==180){g_x_start=p.x;g_g_y_start=p.y;break;}
						}
						g_path[g_pathIndex]=180;
					}
				}
				else
				{
					if(ddy>0)
					{
						if(g_pathIndex>=2)
						{
							if(g_path[g_pathIndex-1]==270){g_x_start=p.x;g_g_y_start=p.y;break;}
						}
						g_path[g_pathIndex]=270;
					}
					else
					{
						if(g_pathIndex>=2)
						{
							if(g_path[g_pathIndex-1]!=90){g_x_start=p.x;g_g_y_start=p.y;break;}
						}
						g_path[g_pathIndex]=90;
					}
				}
				g_pathIndex++;
				g_x_start=p.x;
				g_g_y_start=p.y;

			}
			break;
		}
	case WM_LBUTTONDOWN:
		{
			g_iLeftHolding=1;
			if(g_iRightHolding==1)
			{
				SendBackPage();
				g_pathIndex=0;
				g_iAnyAction=1;
				return 0;
			}
			g_iAnyAction=0;
			break;
		}

	case WM_RBUTTONDOWN:
		{
			g_iRightHolding=1;
			if(g_iLeftHolding==1)
			{
				SendFowardPage();
				g_pathIndex=0;
				g_iAnyAction=1;
				return 0;
			}

			POINT p;
			GetCursorPos(&p);
			g_x_start=p.x;
			g_g_y_start=p.y;

			g_pathIndex=0;

			g_iAnyAction=0;
			break;
		}


	case WM_LBUTTONUP:
		{
			g_iLeftHolding=0;
			if(g_iRightHolding==1)
			{
				SendEscape();
				g_iLeftHolding=0;
				g_iAnyAction=1;
				return 0;
			}

			g_iAnyAction=0;
			break;
		}
	case WM_RBUTTONUP:
		{
			g_iRightHolding=0;
			if(g_iAnyAction==1)
			{
				SendEscape();
				g_pathIndex=0;
				g_iAnyAction=0;
				return 0;
			}


			int iPathOut[10];
			int iPathNum;
			trim(g_path,g_pathIndex,iPathOut, &iPathNum);

			if(iPathNum==1)
			{
				if(iPathOut[0]==180){SendBackPage();g_iAnyAction=1;}
				if(iPathOut[0]==0){SendFowardPage();g_iAnyAction=1;}
			}
			if(iPathNum==2)
			{
				if((iPathOut[0]==90) && (iPathOut[1]==270)){SendRefleshPage();g_iAnyAction=1;}
				if((iPathOut[0]==270) && (iPathOut[1]==0)){SendClose();g_iAnyAction=1;}

			}
			g_pathIndex=0;
			if(g_iAnyAction==1)
			{
				SendEscape();
				g_iAnyAction=0;
				return 0;
			}

			g_iAnyAction=0;
			g_iRightHolding=0;
			break;
		}
	case WM_KEYDOWN:{break;}
	case WM_KEYUP:{break;}
	case WM_LBUTTONDBLCLK:{break;}
	case WM_RBUTTONDBLCLK:{break;}
	case WM_MBUTTONUP:{break;}
	case WM_MBUTTONDOWN:{break;}
	default :{break;}

	}

	CallNextHookEx(g_hhook, code, wParam, lParam);
	return 0;
}