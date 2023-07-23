#include "GameBoard.h"

//CsGame_Board
//---------------------------------------------------------------------------------
CsGame_Board::CsGame_Board() :Game_Board{}, GB_Pen(0), GB_Brush(){}
//---------------------------------------------------------------------------------
void CsGame_Board::Init() {
    //Init boarders of gamefield
    Game_Board.left = GB_X_Offset;
    Game_Board.top = GB_Y_Offset;
    Game_Board.right = GB_Width;
    Game_Board.bottom = GB_Height;

    GB_Brush = CreateSolidBrush(RGB(255, 255, 255));
    GB_Pen = CreatePen(BS_SOLID, 0, RGB(255, 255, 255));
}
//---------------------------------------------------------------------------------
void CsGame_Board::Draw(HDC hdc) {//Drawing boarders of gamefield
    SelectObject(hdc, GB_Pen);
    SelectObject(hdc, GB_Brush);
    //Top Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.top, Game_Board.right, Game_Board.top + Border_Width);
    //Bottom Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.bottom - Border_Width + 1, Game_Board.right, Game_Board.bottom + 1);
    //Left Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.top, Game_Board.left + Border_Width, Game_Board.bottom);
    //Right Gamefield border
    Rectangle(hdc, Game_Board.right - Border_Width + 1, Game_Board.top, Game_Board.right + 1, Game_Board.bottom);
}


