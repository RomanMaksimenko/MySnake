#include "Engine.h"

//Global Variables
RECT Game_Board;
const int GB_X_Offset = 5;
const int GB_Y_Offset = 5;
const int GB_Width = Game_Screen_Height - 2 * GB_X_Offset;
const int GB_Height = Game_Screen_Height - ToolBar_Height - 2 * GB_Y_Offset - 3;



//---------------------------------------------------------------------------------
void Init() {
    Game_Board.left = GB_X_Offset;
    Game_Board.top = GB_Y_Offset;
    Game_Board.right = GB_Width;
    Game_Board.bottom = GB_Height;
}
//---------------------------------------------------------------------------------
void Draw_Game_Board(HDC hdc) {//Drawing board of game field

    HBRUSH gb_brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, gb_brush);
    FrameRect(hdc, &Game_Board, gb_brush);

}
//---------------------------------------------------------------------------------
void Draw_Frame(HDC hdc) {//Drawing game screen
    Draw_Game_Board(hdc);
}