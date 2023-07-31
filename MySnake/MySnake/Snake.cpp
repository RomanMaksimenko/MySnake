#include "Snake.h"

//CsSnake
//---------------------------------------------------------------------------------
CsSnake::CsSnake() :Direction(ESD_None), SNAKE(3), PREV_SNAKE(3), X_Pos(0), Y_Pos(0), Snake_Len(0), Snake_Pen(0), Snake_Brush(0),
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
void CsSnake::Redraw(HWND hwnd) {//redrawing snake
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
        InvalidateRect(hwnd, &PREV_SNAKE[i], FALSE);
    //draw new snake
    for (int i = Snake_Len; i >= 0; --i)
        InvalidateRect(hwnd, &SNAKE[i], FALSE);
}
//---------------------------------------------------------------------------------

void CsSnake::Draw(HDC hdc, RECT& paint_area,HPEN bg_pen,HBRUSH bg_brush) {//Drawing a snake
    RECT intersection_rect;
    for (int i = Snake_Len; i >= 0; --i)
        if (!IntersectRect(&intersection_rect, &paint_area, &SNAKE[i]))
            return;
    //Delete previos snake`s frame
    SelectObject(hdc, bg_pen);
    SelectObject(hdc, bg_brush);
    for (int i = Snake_Len; i >= 0; --i)
        Rectangle(hdc, PREV_SNAKE[i].left, PREV_SNAKE[i].top, PREV_SNAKE[i].left + Snake_Size, PREV_SNAKE[i].top + Snake_Size);
    //Drawing snake
    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    for (int i = Snake_Len; i >= 0; --i)
        Rectangle(hdc, SNAKE[i].left, SNAKE[i].top, SNAKE[i].left + Snake_Size, SNAKE[i].top + Snake_Size);

}
//---------------------------------------------------------------------------------
void CsSnake::Move()
{
    switch (Direction)
    {
    case ESD_None:
        break;
    case ESD_Left:X_Pos -= Snake_Size; if (X_Pos <= CsGame_Board::GB_X_Offset)X_Pos = Grid[44] + Snake_Size;
        break;
    case ESD_Right:X_Pos += Snake_Size; if (X_Pos >= CsGame_Board::GB_Width - Snake_Size - CsGame_Board::Border_Width / 2)X_Pos = Grid[0];
        break;
    case ESD_Up:Y_Pos -= Snake_Size; if (Y_Pos <= CsGame_Board::GB_Y_Offset)Y_Pos = Grid[38] + Snake_Size;
        break;
    case ESD_down:Y_Pos += Snake_Size; if (Y_Pos >= CsGame_Board::GB_Height -Snake_Size - CsGame_Board::Border_Width / 2)Y_Pos = Grid[0];
        break;
    default:
        break;
    }

}
//---------------------------------------------------------------------------------
