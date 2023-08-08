#include "Engine.h"

//CsEngine
//---------------------------------------------------------------------------------
CsEngine::CsEngine():Hwnd(0), BG_Pen(0), BG_Brush(0) {}
//---------------------------------------------------------------------------------
void CsEngine::Init(HWND hWnd) {
    //Starting snake from random position
    Snake.Init();
    APPLE.Init();
    Game_Board.Init();
    BG_Pen = CreatePen(BS_SOLID,0,RGB(0, 0, 0));
    BG_Brush = CreateSolidBrush(RGB(0, 0, 0));
    
    Hwnd = hWnd;
    SetTimer(Hwnd, Timer_ID, 100, 0);
    Snake.Redraw(Hwnd);
}
//---------------------------------------------------------------------------------

void CsEngine::Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Game_Board.Draw(hdc);
    Snake.Draw(hdc, paint_area,BG_Pen,BG_Brush);
    APPLE.Draw(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int CsEngine::On_Timer() {//Snake`s moving on timer
    Snake.Move();
    if (Snake.X_Pos == APPLE.Apple.left && Snake.Y_Pos == APPLE.Apple.top) {
        APPLE.Redraw(Hwnd);
        Snake.Body.insert(Snake.Body.begin(), Snake.Prev_Body[0]);
        Snake.Snake_Len = (int)Snake.Body.size() - 1;
        Snake.Prev_Body.resize(Snake.Prev_Body.size() + 1);
    }

    Snake.Redraw(Hwnd);
    return 0;
}
int CsEngine::On_Key_Down(EKey_Type key) {//Changing direction of Snake`s moving on key down
    switch (key)
    {
    case EKT_None:
        break;
    case EKT_Up:if(Snake.Direction!= ESD_down)Snake.Direction = ESD_Up;
        break;
    case EKT_Down: if (Snake.Direction != ESD_Up)Snake.Direction = ESD_down;
        break;
    case EKT_Left: if (Snake.Direction != ESD_Right)Snake.Direction = ESD_Left;
        break;
    case EKT_Right: if (Snake.Direction != ESD_Left)Snake.Direction = ESD_Right;
        break;
    default:
        break;
    }
    return 0;
}