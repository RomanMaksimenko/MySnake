#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include<vector>
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



static const int Timer_ID = WM_USER + 1;
class CsEngine;

class CApple {
public:
	static const int Apple_Size = 8;
	int Apple_X_Pos, Apple_Y_Pos;
	RECT  Apple, Prev_Apple;
	HPEN Apple_Pen;
	HBRUSH  Apple_Brush;
    void Redraw_Apple(CsEngine* engine);
	void Draw_Apple(HDC hdc, RECT& paint_area, CsEngine* engine);
};

class CsEngine{
public:
	CsEngine():Is_Intersect(false), Direction(ESD_None),SNAKE(3),PREV_SNAKE(3){}
  static const int ToolBar_Height = 50;
  static const int Game_Screen_Width = 640;
  static const int Game_Screen_Height = 480;
  static const int GB_X_Offset = 5;
  static const int GB_Y_Offset = 5;
  static const int GB_Width = Game_Screen_Height - GB_X_Offset;
  static const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset - 10;
  static const int Border_Width = 5;
  static const int Snake_Size = 10;
  HWND Hwnd;
  HPEN BG_Pen;
  HBRUSH  BG_Brush;
  
  void Init(HWND hWnd);
  void Draw_Frame(HDC, RECT&);
  int On_Timer();
  int On_Key_Down(EKey_Type);

private:
	RECT Game_Board, Snake, Prev_Snake;
	HPEN Snake_Pen , GB_Pen, Apple_Pen;
	HBRUSH GB_Brush, Snake_Brush, Apple_Brush;
	
	int Snake_X_Pos;
	int Snake_Y_Pos;
	int Prev_Snake_X_Pos;
	int Prev_Snake_Y_Pos;
	int Snake_Len;
	bool Is_Intersect;
	CApple APPLE;
	ESnake_Direction Direction;
	std::vector<RECT>SNAKE;
	std::vector<RECT>PREV_SNAKE;

	void Draw_Game_Board();
	void Draw_Game_Board(HDC hdc);
	void Redraw_Snake();
	void Draw_Snake(HDC hdc, RECT& paint_area);
	
};