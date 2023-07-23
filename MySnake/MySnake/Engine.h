#pragma once

#include "GameBoard.h"
#include "Apple.h"
#include "Snake.h"
// Enums
enum EKey_Type {
	EKT_None,
	EKT_Up,
	EKT_Down,
	EKT_Left,
	EKT_Right
};






static const int Timer_ID = WM_USER + 1;

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