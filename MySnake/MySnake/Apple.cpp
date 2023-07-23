#include "Apple.h"


//CApple
//---------------------------------------------------------------------------------
CApple::CApple() :Apple{}, X_Pos(0), Y_Pos(0), Apple_Pen(0), Apple_Brush(0) {}
//---------------------------------------------------------------------------------
void CApple::Init() {
    X_Pos = Grid[rand() % 45];
    Y_Pos = Grid[rand() % 39];

    Apple.left = X_Pos;
    Apple.top = Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    Apple_Pen = CreatePen(BS_SOLID, 0, RGB(255, 255, 255));
    Apple_Brush = CreateSolidBrush(RGB(255, 255, 255));
}
//---------------------------------------------------------------------------------
void CApple::Redraw(HWND hwnd) {//redraiwng apple
    //get new apple position
    X_Pos = Grid[rand() % 45];
    Y_Pos = Grid[rand() % 39];
    Apple.left = X_Pos;
    Apple.top = Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    //draw new apple
    InvalidateRect(hwnd, &Apple, FALSE);
}
//---------------------------------------------------------------------------------
void CApple::Draw(HDC hdc, RECT& paint_area) {
    RECT intersection_rect;
    if (!IntersectRect(&intersection_rect, &paint_area, &Apple))
        return;
    // Prev_Apple will be  redrawing with the head of snake because it have the same coordinates   
    //SelectObject(hdc, engine->BG_Pen);
    //SelectObject(hdc,engine->BG_Brush);
    //Ellipse(hdc, Prev_Apple.left, Prev_Apple.top, Prev_Apple.left + Apple_Size, Prev_Apple.top + Apple_Size);

    SelectObject(hdc, Apple_Pen);
    SelectObject(hdc, Apple_Brush);
    Ellipse(hdc, X_Pos, Y_Pos, X_Pos + Apple_Size, Y_Pos + Apple_Size);
}

