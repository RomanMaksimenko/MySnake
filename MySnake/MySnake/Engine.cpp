#include "Engine.h"
#include <iostream>




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
    Snake.Move(Hwnd);
}
//---------------------------------------------------------------------------------

void CsEngine::Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Game_Board.Draw(hdc);
    Snake.Draw(hdc, paint_area,BG_Pen,BG_Brush);
    APPLE.Draw(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int CsEngine::On_Timer() {//Snake`s moving on timer
    switch (Snake.Direction)
    {
    case ESD_None:
        break;
    case ESD_Left:Snake.X_Pos -= Snake.Snake_Size ; if (Snake.X_Pos <= Game_Board.GB_X_Offset)Snake.X_Pos = Grid[44]+CsSnake::Snake_Size;
        break;
    case ESD_Right:Snake.X_Pos += Snake.Snake_Size ; if (Snake.X_Pos >= Game_Board.GB_Width - Snake.Snake_Size - Game_Board.Border_Width / 2)Snake.X_Pos = Grid[0];
        break;
    case ESD_Up:Snake.Y_Pos -= Snake.Snake_Size ; if (Snake.Y_Pos <= Game_Board.GB_Y_Offset)Snake.Y_Pos = Grid[38]+CsSnake::Snake_Size;
        break;
    case ESD_down:Snake.Y_Pos += Snake.Snake_Size ; if (Snake.Y_Pos >= Game_Board.GB_Height - Snake.Snake_Size - Game_Board.Border_Width / 2)Snake.Y_Pos = Grid[0];
        break;
    default:
        break;
    }
    if (Snake.X_Pos == APPLE.Apple.left && Snake.Y_Pos== APPLE.Apple.top) {
        APPLE.Redraw(Hwnd);
        Snake.SNAKE.insert(Snake.SNAKE.begin(), Snake.PREV_SNAKE[0]);
        Snake.Snake_Len = (int)Snake.SNAKE.size() - 1;
        Snake.PREV_SNAKE.resize(Snake.PREV_SNAKE.size() + 1);
    }

    Snake.Move(Hwnd);
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