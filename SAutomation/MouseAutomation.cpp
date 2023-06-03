#include "stdafx.h"
#include "MouseAutomation.h"

int g_iClickDulation = 50;

void MouseLDown(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, dwX, dwY, NULL, NULL);
	Sleep(50);
}
void MouseLDown(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseLDown(g_iC, g_iR);}
	else{MouseLDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

void MouseRDown(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, dwX, dwY, NULL, NULL);
	Sleep(50);
}
void MouseRDown(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseRDown(g_iC, g_iR);}
	else{MouseRDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

void MouseLUp(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, dwX, dwY, NULL, NULL);
}
void MouseLUp(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseLUp(g_iC, g_iR);}
	else{MouseLUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

void MouseRUp(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, dwX, dwY, NULL, NULL);
}
void MouseRUp(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseRUp(g_iC, g_iR);}
	else{MouseRUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}

void MouseLClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseLDown(nX, nY);
	Sleep(g_iClickDulation);
	MouseLUp(nX, nY);
}

void MouseLClick(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseLClick(g_iC, g_iR);}
	else{MouseLClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}


void MouseRClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseRDown(nX, nY);
	Sleep(g_iClickDulation);
	MouseRUp(nX, nY);
}

void MouseRClick(CStringArray* saData)
{
	if(saData->GetCount()==0){MouseRClick(g_iC, g_iR);}
	else{MouseRClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));}
}


void MoveMouse(UINT nX, UINT nY)
{
	DWORD dwX, dwY;
	dwX = (nX+1) * 65535/ ::GetSystemMetrics(SM_CXSCREEN);
	dwY = (nY+1) * 65535/ ::GetSystemMetrics(SM_CYSCREEN);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, dwX, dwY, NULL, NULL);
}
void MoveMouse(CStringArray* saData)
{
	MoveMouse(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

void MouseVWheel(int iWheel)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL, 0, 0, iWheel, NULL);
}
void MouseVWheel(CStringArray* saData)
{
	MouseVWheel(_ttoi(saData->GetAt(0)));
}