#include <stdlib.h>
#include <time.h>
#include<vector>
#include "Engine.h"

enum ESnake_Direction {
    ESD_None,
    ESD_Left,
    ESD_Right,
    ESD_Up,
    ESD_down
};

//Global Variables
RECT Game_Board,Snake,Prev_Snake;
const int GB_X_Offset = 5;
const int GB_Y_Offset = 5;
const int GB_Width = Game_Screen_Height - GB_X_Offset;
const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset-10 ;

HPEN Snake_Pen,BG_Pen;
HBRUSH GB_Brush, Snake_Brush,BG_Brush;
HWND Hwnd;
int Snake_X_Pos;
int Snake_Y_Pos;
int Prev_Snake_X_Pos= Snake_X_Pos;
int Prev_Snake_Y_Pos= Snake_Y_Pos;
int Snake_Size = 10;
ESnake_Direction Direction=ESD_None;
std::vector<RECT>SNAKE(3);
std::vector<RECT>PREV_SNAKE(3);



void Redraw_Snake();
//---------------------------------------------------------------------------------
void Init(HWND hWnd) {

    srand(time(NULL));
    Snake_X_Pos = rand() % GB_Width;
    Snake_Y_Pos = rand() % GB_Height;
    Game_Board.left = GB_X_Offset;
    Game_Board.top = GB_Y_Offset;
    Game_Board.right = GB_Width;
    Game_Board.bottom = GB_Height;

    GB_Brush = CreateSolidBrush(RGB(255, 255, 255));
    Snake_Pen = CreatePen(BS_SOLID, 0, RGB(237, 28, 36));
    Snake_Brush = CreateSolidBrush(RGB(237, 28, 36));
    BG_Pen = CreatePen(BS_SOLID,0,RGB(0, 0, 0));
    BG_Brush = CreateSolidBrush(RGB(0, 0, 0));
    
    Hwnd = hWnd;

    SNAKE[2].left = Snake_X_Pos;
    SNAKE[2].top = Snake_Y_Pos;
    SNAKE[2].right = SNAKE[2].left + Snake_Size;
    SNAKE[2].bottom = SNAKE[2].top + Snake_Size;
    SNAKE[1] = SNAKE[0] = SNAKE[2];

    Redraw_Snake();
    SetTimer(Hwnd, Timer_ID, 100, 0);
}
//---------------------------------------------------------------------------------
void Draw_Game_Board(HDC hdc) {//Drawing board of gamefield

    
    SelectObject(hdc, GB_Brush);
    FrameRect(hdc, &Game_Board, GB_Brush);

}
//---------------------------------------------------------------------------------
void Redraw_Snake() {
    PREV_SNAKE = SNAKE;

    SNAKE[2].left = Snake_X_Pos;
    SNAKE[2].top = Snake_Y_Pos;
    SNAKE[2].right = SNAKE[2].left + Snake_Size;
    SNAKE[2].bottom = SNAKE[2].top + Snake_Size;
    SNAKE[1] = PREV_SNAKE[2];
    SNAKE[0] = PREV_SNAKE[1];
    for(int i=2;i>=0;--i)
    InvalidateRect(Hwnd, &PREV_SNAKE[i], FALSE);
    for (int i = 2; i >= 0; --i)
    InvalidateRect(Hwnd, &SNAKE[i], FALSE);
}
//---------------------------------------------------------------------------------
void Draw_Snake(HDC hdc, RECT& paint_area) {//Drawing a snake

    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);
    for(int i=2;i>=0;--i)
    Rectangle(hdc, PREV_SNAKE[i].left, PREV_SNAKE[i].top, PREV_SNAKE[i].left + Snake_Size, PREV_SNAKE[i].top + Snake_Size);

    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    for(int i=2;i>=0;--i)
    Rectangle(hdc, SNAKE[i].left, SNAKE[i].top, SNAKE[i].left + Snake_Size, SNAKE[i].top + Snake_Size);

}
//---------------------------------------------------------------------------------
void Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Draw_Game_Board(hdc);
    Draw_Snake(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int On_Timer() {//Snake`s moving on timer
    switch (Direction)
    {
    case ESD_None:
        break;
    case ESD_Left:Snake_X_Pos -= Snake_Size/2;
        break;
    case ESD_Right:Snake_X_Pos += Snake_Size/2;
        break;
    case ESD_Up:Snake_Y_Pos -= Snake_Size/2;
        break;
    case ESD_down:Snake_Y_Pos += Snake_Size/2;
        break;
    default:
        break;
    }
    Redraw_Snake();
    return 0;
}
int On_Key_Down(EKey_Type key) {//Changing direction of Snake`s moving on key down
    switch (key)
    {
    case EKT_None:
        break;
    case EKT_Up:if(Direction!= ESD_down)Direction = ESD_Up;
        break;
    case EKT_Down: if (Direction != ESD_Up)Direction = ESD_down;
        break;
    case EKT_Left: if (Direction != ESD_Right)Direction = ESD_Left;
        break;
    case EKT_Right: if (Direction != ESD_Left)Direction = ESD_Right;
        break;
    default:
        break;
    }
    return 0;
}