#pragma once
#include "Config.h"
class CsGame_Board {
public:
	CsGame_Board();
	void Init();
	RECT Game_Board;
	void Draw(HDC hdc);
	static const int ToolBar_Height = 50;
	static const int Game_Screen_Width = 640;
	static const int Game_Screen_Height = 480;
	static const int GB_X_Offset = 5;
	static const int GB_Y_Offset = 5;
	static const int GB_Width = Game_Screen_Height - GB_X_Offset;
	static const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset - 10;
	static const int Border_Width = 5;
private:
	HPEN GB_Pen;
	HBRUSH GB_Brush;
};
