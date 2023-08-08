#pragma once
#include "GameBoard.h"

class CsSnake {
public:
	CsSnake();
	void Init();
	static const int Snake_Size = 10;
	int X_Pos;
	int Y_Pos;
	ESnake_Direction Direction;
	void Redraw(HWND hwnd);
	void Draw(HDC hdc, RECT& paint_area, HPEN bg_pen, HBRUSH bg_brush);
	void Move();
	int Snake_Len;
	std::vector<RECT>Body;
	std::vector<RECT>Prev_Body;
private:
	HPEN Snake_Pen;
	HBRUSH  Snake_Brush;
};
