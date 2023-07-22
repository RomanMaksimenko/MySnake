#include "Engine.h"
#include <iostream>
//Coordinates grid
int Grid[45];

//CApple
//---------------------------------------------------------------------------------
void CApple::Init() {
    Apple_X_Pos = Grid[rand() % 45];
    Apple_Y_Pos = Grid[rand() % 39];

    Apple.left = Apple_X_Pos;
    Apple.top = Apple_Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    Apple_Pen = CreatePen(BS_SOLID, 0, RGB(255, 255, 255));
    Apple_Brush = CreateSolidBrush(RGB(255, 255, 255));
}
//---------------------------------------------------------------------------------
void CApple::Redraw_Apple(CsEngine* engine) {//redraiwng apple
    //get new apple position
    Apple_X_Pos = Grid[rand() % 45];
    Apple_Y_Pos = Grid[rand() % 39];
    Apple.left = Apple_X_Pos;
    Apple.top = Apple_Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    //draw new apple
    InvalidateRect(engine->Hwnd, &Apple, FALSE);
}
//---------------------------------------------------------------------------------
void CApple::Draw_Apple(HDC hdc, RECT& paint_area) {
    RECT intersection_rect;
    if (!IntersectRect(&intersection_rect, &paint_area, &Apple))
        return;
    // Prev_Apple will be  redrawing with the head of snake because it have the same coordinates   
    //SelectObject(hdc, engine->BG_Pen);
    //SelectObject(hdc,engine->BG_Brush);
    //Ellipse(hdc, Prev_Apple.left, Prev_Apple.top, Prev_Apple.left + Apple_Size, Prev_Apple.top + Apple_Size);

    SelectObject(hdc, Apple_Pen);
    SelectObject(hdc, Apple_Brush);
    Ellipse(hdc, Apple_X_Pos, Apple_Y_Pos, Apple_X_Pos + Apple_Size, Apple_Y_Pos + Apple_Size);
}

//CsSnake
//---------------------------------------------------------------------------------
void CsSnake::Init() {
    srand(time(NULL));
    Snake_X_Pos = Grid[rand() % 45];
    Snake_Y_Pos = Grid[rand() % 39];
    Snake_Pen = CreatePen(BS_SOLID, 0, RGB(237, 28, 36));
    Snake_Brush = CreateSolidBrush(RGB(237, 28, 36));
    Snake_Len = (int)SNAKE.size() - 1;
    SNAKE[Snake_Len].left = Snake_X_Pos;
    SNAKE[Snake_Len].top = Snake_Y_Pos;
    SNAKE[Snake_Len].right = SNAKE[Snake_Len].left + Snake_Size;
    SNAKE[Snake_Len].bottom = SNAKE[Snake_Len].top + Snake_Size;
    for (int i = 0; i != Snake_Len; ++i)
        SNAKE[i] = SNAKE[Snake_Len];
}
//---------------------------------------------------------------------------------
void CsSnake::Redraw_Snake(CsEngine* engine) {//redrawing snake
    PREV_SNAKE = SNAKE;
    //New head position
    SNAKE[Snake_Len].left = Snake_X_Pos;
    SNAKE[Snake_Len].top = Snake_Y_Pos;
    SNAKE[Snake_Len].right = SNAKE[Snake_Len].left + Snake_Size;
    SNAKE[Snake_Len].bottom = SNAKE[Snake_Len].top + Snake_Size;
    //update snake body coordinates
    for (int i = 0; i != Snake_Len; ++i)
        SNAKE[i] = PREV_SNAKE[i + 1];
    //erase previos snake
    for (int i = Snake_Len; i >= 0; --i)
        InvalidateRect(engine->Hwnd, &PREV_SNAKE[i], FALSE);
    //draw new snake
    for (int i = Snake_Len; i >= 0; --i)
        InvalidateRect(engine->Hwnd, &SNAKE[i], FALSE);
}
//---------------------------------------------------------------------------------

void CsSnake::Draw_Snake(HDC hdc, RECT& paint_area, CsEngine* engine) {//Drawing a snake
    RECT intersection_rect;
    for (int i = Snake_Len; i >= 0; --i)
        if (!IntersectRect(&intersection_rect, &paint_area, &SNAKE[i]))
            return;
    //Delete previos snake`s frame
    SelectObject(hdc,engine->BG_Pen);
    SelectObject(hdc,engine->BG_Brush);
    for (int i = Snake_Len; i >= 0; --i)
        Rectangle(hdc, PREV_SNAKE[i].left, PREV_SNAKE[i].top, PREV_SNAKE[i].left + Snake_Size, PREV_SNAKE[i].top + Snake_Size);
    //Drawing snake
    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    for (int i = Snake_Len; i >= 0; --i)
        Rectangle(hdc, SNAKE[i].left, SNAKE[i].top, SNAKE[i].left + Snake_Size, SNAKE[i].top + Snake_Size);

}

//CsGame_Board
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
void CsGame_Board::Draw_Game_Board(HDC hdc) {//Drawing boarders of gamefield
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
//---------------------------------------------------------------------------------
void CsEngine::Init(HWND hWnd) {
    //Starting snake from random position

    int grid = 11;
    for (int i = 0; i != 45; ++i) {
            Grid[i] = grid;
            grid += 10;
    }

    Snake.Init();
    APPLE.Init();
    Game_Board.Init();
    BG_Pen = CreatePen(BS_SOLID,0,RGB(0, 0, 0));
    BG_Brush = CreateSolidBrush(RGB(0, 0, 0));
    
    Hwnd = hWnd;
    SetTimer(Hwnd, Timer_ID, 100, 0);
    Snake.Redraw_Snake(this);
}
//---------------------------------------------------------------------------------
//void CsEngine::Draw_Game_Board() {
//    InvalidateRect(Hwnd, &Game_Board, FALSE);
//}
//---------------------------------------------------------------------------------

void CsEngine::Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Game_Board.Draw_Game_Board(hdc);
    Snake.Draw_Snake(hdc, paint_area,this);
    APPLE.Draw_Apple(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int CsEngine::On_Timer() {//Snake`s moving on timer
    switch (Snake.Direction)
    {
    case ESD_None:
        break;
    case ESD_Left:Snake.Snake_X_Pos -= Snake.Snake_Size ; if (Snake.Snake_X_Pos <= Game_Board.GB_X_Offset)Snake.Snake_X_Pos = Grid[44]+CsSnake::Snake_Size;
        break;
    case ESD_Right:Snake.Snake_X_Pos += Snake.Snake_Size ; if (Snake.Snake_X_Pos >= Game_Board.GB_Width - Snake.Snake_Size - Game_Board.Border_Width / 2)Snake.Snake_X_Pos = Grid[0];
        break;
    case ESD_Up:Snake.Snake_Y_Pos -= Snake.Snake_Size ; if (Snake.Snake_Y_Pos <= Game_Board.GB_Y_Offset)Snake.Snake_Y_Pos = Grid[38]+CsSnake::Snake_Size;
        break;
    case ESD_down:Snake.Snake_Y_Pos += Snake.Snake_Size ; if (Snake.Snake_Y_Pos >= Game_Board.GB_Height - Snake.Snake_Size - Game_Board.Border_Width / 2)Snake.Snake_Y_Pos = Grid[0];
        break;
    default:
        break;
    }
    if (Snake.Snake_X_Pos == APPLE.Apple.left && Snake.Snake_Y_Pos== APPLE.Apple.top) {
        APPLE.Redraw_Apple(this);
        Snake.SNAKE.insert(Snake.SNAKE.begin(), Snake.PREV_SNAKE[0]);
        Snake.Snake_Len = (int)Snake.SNAKE.size() - 1;
        Snake.PREV_SNAKE.resize(Snake.PREV_SNAKE.size() + 1);
    }

    Snake.Redraw_Snake(this);
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