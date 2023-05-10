#pragma once
#include "stdafx.h"


#include "Automation.h"

#define COMMAND_MOUSE_MOVE (COMMAND_MOUSE+MOUSEEVENTF_MOVE)
#define COMMAND_MOUSE_L_DOWN (COMMAND_MOUSE+MOUSEEVENTF_LEFTDOWN)
#define COMMAND_MOUSE_L_UP (COMMAND_MOUSE+MOUSEEVENTF_LEFTUP)
#define COMMAND_WHEEL (COMMAND_MOUSE+MOUSEEVENTF_WHEEL)

#define COMMAND_MOUSE_L_CLICK (COMMAND_MOUSE+100+MOUSEEVENTF_LEFTDOWN)


void MouseLDown(UINT nX, UINT nY);
void MouseLDown(CStringArray* saData);
void MouseLUp(UINT nX, UINT nY);
void MouseLUp(CStringArray* saData);
void MoveMouse(UINT nX, UINT nY);
void MoveMouse(CStringArray* saData);
void MouseVWheel(int iWheel);
void MouseVWheel(CStringArray* saData);
void MouseLClick(UINT nX, UINT nY);
void MouseLClick(CStringArray* saData);
