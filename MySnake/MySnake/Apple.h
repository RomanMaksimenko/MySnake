#pragma once
#include "Config.h"

class CApple {
public:
	CApple();
	void Init();
	RECT  Apple;
	void Redraw(HWND hwnd);
	void Draw(HDC hdc, RECT& paint_area);
	static const int Apple_Size = 10;
private:
	int X_Pos, Y_Pos;
	HPEN Apple_Pen;
	HBRUSH  Apple_Brush;
};
