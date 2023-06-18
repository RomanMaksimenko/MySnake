#include "Engine.h"

//Global Variables
RECT Game_Board;
const int GB_X_Offset = 5;
const int GB_Y_Offset = 5;
const int GB_Width = Game_Screen_Height - GB_X_Offset;
const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset-10 ;

HPEN Snake_Pen;
HBRUSH GB_Brush, Snake_Brush;
HWND Hwnd;




//---------------------------------------------------------------------------------
void Init(HWND hWnd) {
    Game_Board.left = GB_X_Offset;
    Game_Board.top = GB_Y_Offset;
    Game_Board.right = GB_Width;
    Game_Board.bottom = GB_Height;

    GB_Brush = CreateSolidBrush(RGB(255, 255, 255));
    Snake_Pen = CreatePen(BS_SOLID, 0, RGB(237, 28, 36));
    Snake_Brush = CreateSolidBrush(RGB(237, 28, 36));
    
    Hwnd = hWnd;
    SetTimer(Hwnd, Timer_ID, 50, 0);
}
//---------------------------------------------------------------------------------
void Draw_Game_Board(HDC hdc) {//Drawing board of gamefield

    
    SelectObject(hdc, GB_Brush);
    FrameRect(hdc, &Game_Board, GB_Brush);

}
//---------------------------------------------------------------------------------
void Draw_Snake(HDC hdc) {//Drawing a snake

    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    Rectangle(hdc, 50, 150, 50 + 10, 150 + 10);
}
//---------------------------------------------------------------------------------
void Draw_Frame(HDC hdc) {//Drawing game screen
    Draw_Game_Board(hdc);
    Draw_Snake(hdc);
}
//---------------------------------------------------------------------------------
int On_Timer() {

    return 0;
}