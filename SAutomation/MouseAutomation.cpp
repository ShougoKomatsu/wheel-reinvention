#include "stdafx.h"
#include "MouseAutomation.h"
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
	MouseLDown(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
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
	MouseLUp(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
}

void MouseLClick(UINT nX, UINT nY)
{
	MoveMouse(nX, nY);
	MouseLDown(nX, nY);
	Sleep(50);
	MouseLUp(nX, nY);
}

void MouseLClick(CStringArray* saData)
{
	MouseLClick(_ttoi(saData->GetAt(0)),_ttoi(saData->GetAt(1)));
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