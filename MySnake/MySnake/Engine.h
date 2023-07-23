#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include<vector>
#include "GameBoard.h"
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
	CApple();
	void Init();
	RECT  Apple;
	void Redraw(CsEngine* engine);
	void Draw(HDC hdc, RECT& paint_area);
	static const int Apple_Size = 10;
private:
	int X_Pos, Y_Pos;
	HPEN Apple_Pen;
	HBRUSH  Apple_Brush;
};

class CsSnake {
public:
	CsSnake();
	void Init();
	static const int Snake_Size = 10;
	int X_Pos;
	int Y_Pos;
	ESnake_Direction Direction;
	void Move(CsEngine* engine);
	void Draw(HDC hdc, RECT& paint_area, CsEngine* engine);
	int Snake_Len;
	std::vector<RECT>SNAKE;
	std::vector<RECT>PREV_SNAKE;
private:
	HPEN Snake_Pen;
	HBRUSH  Snake_Brush;
	RECT Snake, Prev_Snake;

};


class CsEngine{
public:
  CsEngine();
  HWND Hwnd;
  HPEN BG_Pen;
  HBRUSH  BG_Brush;
  CsGame_Board Game_Board;
  void Init(HWND hWnd);
  void Draw_Frame(HDC, RECT&);
  int On_Timer();
  int On_Key_Down(EKey_Type);

private:
	CApple APPLE;
	CsSnake Snake;
	
};