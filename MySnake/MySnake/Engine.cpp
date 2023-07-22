#include "Engine.h"
#include <iostream>
//Coordinates grid
int Grid[45];

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
void CApple::Redraw(CsEngine* engine) {//redraiwng apple
    //get new apple position
    X_Pos = Grid[rand() % 45];
    Y_Pos = Grid[rand() % 39];
    Apple.left = X_Pos;
    Apple.top = Y_Pos;
    Apple.right = Apple.left + Apple_Size;
    Apple.bottom = Apple.top + Apple_Size;
    //draw new apple
    InvalidateRect(engine->Hwnd, &Apple, FALSE);
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



//CsSnake
//---------------------------------------------------------------------------------
CsSnake::CsSnake() :Direction(ESD_None), SNAKE(3), PREV_SNAKE(3), X_Pos(0), Y_Pos(0),Snake_Len(0), Snake_Pen(0), Snake_Brush(0),
Snake{}, Prev_Snake{}{}
//---------------------------------------------------------------------------------
void CsSnake::Init() {
    srand(time(NULL));
    X_Pos = Grid[rand() % 45];
    Y_Pos = Grid[rand() % 39];
    Snake_Pen = CreatePen(BS_SOLID, 0, RGB(237, 28, 36));
    Snake_Brush = CreateSolidBrush(RGB(237, 28, 36));
    Snake_Len = (int)SNAKE.size() - 1;
    SNAKE[Snake_Len].left = X_Pos;
    SNAKE[Snake_Len].top = Y_Pos;
    SNAKE[Snake_Len].right = SNAKE[Snake_Len].left + Snake_Size;
    SNAKE[Snake_Len].bottom = SNAKE[Snake_Len].top + Snake_Size;
    for (int i = 0; i != Snake_Len; ++i)
        SNAKE[i] = SNAKE[Snake_Len];
}
//---------------------------------------------------------------------------------
void CsSnake::Move(CsEngine* engine) {//redrawing snake
    PREV_SNAKE = SNAKE;
    //New head position
    SNAKE[Snake_Len].left = X_Pos;
    SNAKE[Snake_Len].top = Y_Pos;
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

void CsSnake::Draw(HDC hdc, RECT& paint_area, CsEngine* engine) {//Drawing a snake
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



//CsEngine
//---------------------------------------------------------------------------------
CsEngine::CsEngine():Hwnd(0), BG_Pen(0), BG_Brush(0) {}
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
    Snake.Move(this);
}
//---------------------------------------------------------------------------------
//void CsEngine::Draw() {
//    InvalidateRect(Hwnd, &Game_Board, FALSE);
//}
//---------------------------------------------------------------------------------

void CsEngine::Draw_Frame(HDC hdc,RECT& paint_area) {//Drawing game screen
    Game_Board.Draw(hdc);
    Snake.Draw(hdc, paint_area,this);
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
        APPLE.Redraw(this);
        Snake.SNAKE.insert(Snake.SNAKE.begin(), Snake.PREV_SNAKE[0]);
        Snake.Snake_Len = (int)Snake.SNAKE.size() - 1;
        Snake.PREV_SNAKE.resize(Snake.PREV_SNAKE.size() + 1);
    }

    Snake.Move(this);
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