#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "CList.h"
// Enums
enum EKey_Type {
	EKT_None,
	EKT_Up,
	EKT_Down,
	EKT_Left,
	EKT_Right
};

enum ESnake_Direction {
	ESD_None,
	ESD_Left,
	ESD_Right,
	ESD_Up,
	ESD_down
};
//Global Variables
class CsEngine {
public:

	static const int ToolBar_Height = 50;
	static const int Game_Screen_Width = 640;
	static const int Game_Screen_Height = 480;
	static const int Timer_ID = WM_USER + 1;
	void Init(HWND hWnd);
	void Draw_Frame(HDC, RECT&);
	int On_Timer();
	int On_Key_Down(EKey_Type);
private:
	RECT Game_Board, Snake, Prev_Snake, Apple, Prev_Apple;
	static const int GB_X_Offset = 5;
	static const int GB_Y_Offset = 5;
	static const int GB_Width = Game_Screen_Height - GB_X_Offset;
	static const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset - 10;
	static const int Border_Width = 5;
	static const int Snake_Size = 10;
	static const int Apple_Size = 8;

	HPEN Snake_Pen, BG_Pen, GB_Pen, Apple_Pen;
	HBRUSH GB_Brush, Snake_Brush, BG_Brush, Apple_Brush;
	HWND Hwnd;
	int Snake_X_Pos;
	int Snake_Y_Pos;
	int Prev_Snake_X_Pos = Snake_X_Pos;
	int Prev_Snake_Y_Pos = Snake_Y_Pos;
	int Snake_Len, _Snake_Len;
	int Apple_X_Pos, Apple_Y_Pos;
	int To_Turn = 0;
	bool Is_Intersect = false, Turn = true;
	ESnake_Direction Direction = ESD_None;
	CList<RECT> _SNAKE, _SNAKE_TAIL;
	CList<RECT> _Prev_SNAKE, _Prev_SNAKE_TAIL;
	
	int Random_int(int min, int max);
	void Draw_Game_Board();
	void Draw_Game_Board(HDC hdc);
	void Redraw_Apple();
	void Check_Snake_Eat_Apple();
	void Redraw_Snake();
	void Draw_Snake(HDC hdc, RECT& paint_area);
	void Draw_Apple(HDC hdc, RECT& paint_area);
};
