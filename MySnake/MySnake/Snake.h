#pragma once
#include "Config.h"

class CsSnake {
public:
	CsSnake();
	void Init();
	static const int Snake_Size = 10;
	int X_Pos;
	int Y_Pos;
	ESnake_Direction Direction;
	void Move(HWND hwnd);
	void Draw(HDC hdc, RECT& paint_area, HPEN bg_pen, HBRUSH bg_brush);
	int Snake_Len;
	std::vector<RECT>SNAKE;
	std::vector<RECT>PREV_SNAKE;
private:
	HPEN Snake_Pen;
	HBRUSH  Snake_Brush;
	RECT Snake, Prev_Snake;

};
