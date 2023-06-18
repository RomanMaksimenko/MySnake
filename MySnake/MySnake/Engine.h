#pragma once
#include <Windows.h>
// Enums
enum EKey_Type {
	EKT_None,
	EKT_Up,
	EKT_Down,
	EKT_Left,
	EKT_Right
};

//Global Variables

const int ToolBar_Height = 50;
const int Game_Screen_Width = 640;
const int Game_Screen_Height = 480;
const int Timer_ID = WM_USER + 1;


void Init(HWND hWnd);
void Draw_Frame(HDC, RECT&);
int On_Timer();
int On_Key_Down(EKey_Type);

