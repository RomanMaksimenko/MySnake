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
RECT Game_Board,Snake,Prev_Snake,Apple,Prev_Apple;
const int GB_X_Offset = 5;
const int GB_Y_Offset = 5;
const int GB_Width = Game_Screen_Height - GB_X_Offset;
const int GB_Height = Game_Screen_Height - ToolBar_Height - GB_Y_Offset-10 ;
const int Border_Width = 5;
const int Snake_Size = 10;
const int Apple_Size = 8;

HPEN Snake_Pen,BG_Pen,GB_Pen,Apple_Pen;
HBRUSH GB_Brush, Snake_Brush,BG_Brush,Apple_Brush;
HWND Hwnd;
int Snake_X_Pos;
int Snake_Y_Pos;
int Prev_Snake_X_Pos= Snake_X_Pos;
int Prev_Snake_Y_Pos= Snake_Y_Pos;
int Snake_Len;
int Apple_X_Pos, Apple_Y_Pos;
bool Is_Intersect = false;
ESnake_Direction Direction=ESD_None;
std::vector<RECT>SNAKE(3);
std::vector<RECT>PREV_SNAKE(3);


void Redraw_Snake();
//---------------------------------------------------------------------------------
void Init(HWND hWnd) {
    //Starting snake from random position
    srand(time(NULL));
    Snake_X_Pos = rand() % GB_Width;
    Snake_Y_Pos = rand() % GB_Height;

    Apple_X_Pos = rand() % GB_Width;
    Apple_Y_Pos = rand() % GB_Height;

    Apple.left = Apple_X_Pos;
    Apple.top = Apple_Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    
    //Init boarders of gamefield
    Game_Board.left = GB_X_Offset;
    Game_Board.top = GB_Y_Offset;
    Game_Board.right = GB_Width;
    Game_Board.bottom = GB_Height;

    GB_Brush = CreateSolidBrush(RGB(255, 255, 255));
    GB_Pen = CreatePen(BS_SOLID, 0, RGB(255, 255, 255));
    Snake_Pen = CreatePen(BS_SOLID, 0, RGB(237, 28, 36));
    Snake_Brush = CreateSolidBrush(RGB(237, 28, 36));
    BG_Pen = CreatePen(BS_SOLID,0,RGB(0, 0, 0));
    BG_Brush = CreateSolidBrush(RGB(0, 0, 0));
    Apple_Pen = CreatePen(BS_SOLID, 0, RGB(255, 255, 255));
    Apple_Brush = CreateSolidBrush(RGB(255, 255, 255));
    
    Hwnd = hWnd;
    Snake_Len =(int)SNAKE.size()-1;
    SNAKE[Snake_Len].left = Snake_X_Pos;
    SNAKE[Snake_Len].top = Snake_Y_Pos;
    SNAKE[Snake_Len].right = SNAKE[Snake_Len].left + Snake_Size;
    SNAKE[Snake_Len].bottom = SNAKE[Snake_Len].top + Snake_Size;
    for (int i = 0; i != Snake_Len; ++i)
        SNAKE[i] = SNAKE[Snake_Len];
    
    Redraw_Snake();
    SetTimer(Hwnd, Timer_ID, 100, 0);
}
//---------------------------------------------------------------------------------
void Draw_Game_Board() {
    InvalidateRect(Hwnd, &Game_Board, FALSE);
}
//---------------------------------------------------------------------------------
void Draw_Game_Board(HDC hdc) {//Drawing boarders of gamefield

    
    SelectObject(hdc, GB_Pen);
    SelectObject(hdc, GB_Brush);
    //Top Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.top, Game_Board.right, Game_Board.top + Border_Width);
    //Bottom Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.bottom - Border_Width, Game_Board.right, Game_Board.bottom);
    //Left Gamefield border
    Rectangle(hdc, Game_Board.left, Game_Board.top, Game_Board.left + Border_Width, Game_Board.bottom);
    //Right Gamefield border
    Rectangle(hdc, Game_Board.right- Border_Width, Game_Board.top, Game_Board.right, Game_Board.bottom);
    


}
//---------------------------------------------------------------------------------
void Redraw_Apple() {//redraiwng apple
    Prev_Apple = Apple;
    //get new apple position
    Apple_X_Pos = rand() % GB_Width;
    Apple_Y_Pos = rand() % GB_Height;
    Apple.left = Apple_X_Pos;
    Apple.top = Apple_Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    //erase previos apple
    InvalidateRect(Hwnd, &Prev_Apple, TRUE);
    //draw new apple
    InvalidateRect(Hwnd, &Apple, FALSE);
}
//---------------------------------------------------------------------------------
void Redraw_Snake() {//redrawing snake
    PREV_SNAKE = SNAKE;
    //New head position
    SNAKE[Snake_Len].left = Snake_X_Pos;
    SNAKE[Snake_Len].top = Snake_Y_Pos;
    SNAKE[Snake_Len].right = SNAKE[Snake_Len].left + Snake_Size;
    SNAKE[Snake_Len].bottom = SNAKE[Snake_Len].top + Snake_Size;
    //update snake body coordinates
    for (int i = 0; i != Snake_Len; ++i)
        SNAKE[i] = PREV_SNAKE[i+1];
    //snake eat`s apple
    if (Is_Intersect) {
         Redraw_Apple();
        SNAKE.insert(SNAKE.begin(), PREV_SNAKE[0]);
        Snake_Len = (int)SNAKE.size() - 1;
        PREV_SNAKE.resize(PREV_SNAKE.size() + 1);
        Is_Intersect = false;
    }
    RECT tmp;
    if (IntersectRect(&tmp,&SNAKE[Snake_Len],&Apple)) {
        Is_Intersect = true;
    }
    //erase previos snake
    for(int i= Snake_Len;i>=0;--i)
    InvalidateRect(Hwnd, &PREV_SNAKE[i], FALSE);
    //draw new snake
    for (int i = Snake_Len; i >= 0; --i)
    InvalidateRect(Hwnd, &SNAKE[i], FALSE);

}
//---------------------------------------------------------------------------------
void Draw_Snake(HDC hdc, RECT& paint_area) {//Drawing a snake
    //Delete previos snake`s frame
    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);
    for(int i= Snake_Len;i>=0;--i)
    Rectangle(hdc, PREV_SNAKE[i].left, PREV_SNAKE[i].top, PREV_SNAKE[i].left + Snake_Size, PREV_SNAKE[i].top + Snake_Size);
    //Drawing snake
    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    for(int i= Snake_Len;i>=0;--i)
    Rectangle(hdc, SNAKE[i].left, SNAKE[i].top, SNAKE[i].left + Snake_Size, SNAKE[i].top + Snake_Size);

}
//---------------------------------------------------------------------------------
void Draw_Apple(HDC hdc, RECT& paint_area) {

    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);
    Ellipse(hdc, Prev_Apple.left, Prev_Apple.top, Prev_Apple.left+Apple_Size, Prev_Apple.top + Apple_Size);

    SelectObject(hdc, Apple_Pen);
    SelectObject(hdc, Apple_Brush);
   Ellipse( hdc,Apple_X_Pos,Apple_Y_Pos, Apple_X_Pos+Apple_Size, Apple_Y_Pos + Apple_Size);
}
//---------------------------------------------------------------------------------
void Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Draw_Game_Board(hdc);
    Draw_Snake(hdc, paint_area);
    Draw_Apple(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int On_Timer() {//Snake`s moving on timer
    switch (Direction)
    {
    case ESD_None:
        break;
    case ESD_Left:Snake_X_Pos -= Snake_Size / 2; if (Snake_X_Pos <= GB_X_Offset)Snake_X_Pos = GB_Width - Snake_Size - Border_Width;
        break;
    case ESD_Right:Snake_X_Pos += Snake_Size / 2; if (Snake_X_Pos >= GB_Width - Snake_Size - Border_Width / 2)Snake_X_Pos = GB_X_Offset + Border_Width;
        break;
    case ESD_Up:Snake_Y_Pos -= Snake_Size / 2; if (Snake_Y_Pos <= GB_Y_Offset)Snake_Y_Pos = GB_Height - Snake_Size - Border_Width;
        break;
    case ESD_down:Snake_Y_Pos += Snake_Size / 2; if (Snake_Y_Pos >= GB_Height - Snake_Size - Border_Width / 2)Snake_Y_Pos = GB_Y_Offset + Border_Width;
        break;
    default:
        break;
    }
    if (Is_Intersect) {
        Redraw_Apple();
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