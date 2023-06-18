#pragma once
#include <Windows.h>


//Global Variables

const int ToolBar_Height = 50;
const int Game_Screen_Width = 640;
const int Game_Screen_Height = 480;
const int Timer_ID = WM_USER + 1;


void Init(HWND hWnd);
void Draw_Frame(HDC);
int On_Timer();

