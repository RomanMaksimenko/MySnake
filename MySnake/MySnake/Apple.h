#pragma once
#include "Config.h"

class CApple {
public:
	CApple();

	void Init();
	void Redraw(HWND hwnd);
	void Draw(HDC hdc, RECT& paint_area);

	static const int Apple_Size = 10;

	RECT  Apple;

private:

	int X_Pos, Y_Pos;
	HPEN Apple_Pen;
	HBRUSH  Apple_Brush;
};
