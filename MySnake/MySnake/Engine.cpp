
#include "Engine.h"
//---------------------------------------------------------------------------------
int CsEngine::Random_int(int min,int max) {
    
    int num= rand() % GB_Width;
    while(num<=min||num>=max)
        num = rand() % GB_Width;
    return num;
} 
//---------------------------------------------------------------------------------
void CsEngine::Init(HWND hWnd) {
    //Starting snake from random position
    srand(time(NULL));
    Snake_X_Pos = Random_int(GB_X_Offset+ Border_Width, GB_Width- Border_Width);
    Snake_Y_Pos = Random_int(GB_Y_Offset + Border_Width, GB_Height - Border_Width);

    Apple_X_Pos = Random_int(GB_X_Offset + Border_Width, GB_Width - Border_Width-Apple_Size);
    Apple_Y_Pos = Random_int(GB_Y_Offset + Border_Width, GB_Height - Border_Width - Apple_Size);

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
    //initilization of Snake
    _Snake_Len = 6;
    _SNAKE = new Node<RECT>;
    _Prev_SNAKE = new Node<RECT>;
    _Prev_SNAKE->item = _SNAKE->item;
    CList<RECT> tmp = _SNAKE;
    CList<RECT> prev_tmp = _Prev_SNAKE;
    for (int i = 0; i != _Snake_Len; ++i) {
        tmp->next = new Node<RECT>;
        prev_tmp->next = new Node<RECT>;
        tmp->item.left = Snake_X_Pos;
        tmp->item.top = Snake_Y_Pos;
        tmp->item.right = tmp->item.left + Snake_Size;
        tmp->item.bottom = tmp->item.top + Snake_Size;
        prev_tmp->item = tmp->item;
        if (i == _Snake_Len - 1) {
            _SNAKE_TAIL = tmp;
            _Prev_SNAKE_TAIL = prev_tmp;
        }
        tmp = tmp->next;
        prev_tmp = prev_tmp->next;
    }

    Redraw_Snake();
    SetTimer(Hwnd, Timer_ID, 100, 0);
}
//---------------------------------------------------------------------------------
void CsEngine::Draw_Game_Board() {
    InvalidateRect(Hwnd, &Game_Board, FALSE);
}
//---------------------------------------------------------------------------------
void CsEngine::Draw_Game_Board(HDC hdc) {//Drawing boarders of gamefield

    
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
void CsEngine::Redraw_Apple() {//redraiwng apple
    Prev_Apple = Apple;
    //get new apple position
    Apple_X_Pos = Random_int(GB_X_Offset + Border_Width, GB_Width - Border_Width - Apple_Size);
    Apple_Y_Pos = Random_int(GB_Y_Offset + Border_Width, GB_Height - Border_Width - Apple_Size);
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
void CsEngine::Check_Snake_Eat_Apple() {

    if (Is_Intersect) {
        Redraw_Apple();
        _SNAKE_TAIL->next = new Node<RECT>(_Prev_SNAKE_TAIL->item);
        _SNAKE_TAIL = _SNAKE_TAIL->next;
        Is_Intersect = false;
    }
    RECT tmp;
   if (IntersectRect(&tmp, &_SNAKE->item, &Apple)) {
        Is_Intersect = true;
    }
}
//---------------------------------------------------------------------------------
void CsEngine::Redraw_Snake() {//redrawing snake
    CList<RECT> tmp, prev_tmp;
    tmp = _SNAKE;
    prev_tmp = _Prev_SNAKE;
    while (tmp) {
        if (tmp->next && !prev_tmp->next) {
            prev_tmp->next = new Node<RECT>;
            _Prev_SNAKE_TAIL = prev_tmp->next;
        }
            prev_tmp->item = tmp->item;
            tmp = tmp->next;
            prev_tmp = prev_tmp->next;

    }
    //New head position
    _SNAKE->item.left = Snake_X_Pos;
    _SNAKE->item.top = Snake_Y_Pos;
    _SNAKE->item.right = _SNAKE->item.left + Snake_Size;
    _SNAKE->item.bottom =_SNAKE->item.top + Snake_Size;

    //update snake body coordinates
    
    tmp = _SNAKE->next;
    prev_tmp = _Prev_SNAKE;
    while (tmp) {
        tmp->item = prev_tmp->item;
        tmp = tmp->next;
        prev_tmp = prev_tmp->next;
    }
    //snake eat`s apple
    Check_Snake_Eat_Apple();
    //erase previos snake

    prev_tmp = _Prev_SNAKE;
    while (prev_tmp) {
        InvalidateRect(Hwnd, &prev_tmp->item, FALSE);
        prev_tmp = prev_tmp->next;
    }

    //draw new snake

    tmp = _SNAKE;
    while (prev_tmp) {
        InvalidateRect(Hwnd, &tmp->item, FALSE);
        tmp = tmp->next;
    }


}
//---------------------------------------------------------------------------------
void CsEngine::Draw_Snake(HDC hdc, RECT& paint_area) {//Draw a snake
    //Delete previos snake`s frame
    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);
    Node<RECT>* tmp = _Prev_SNAKE;
    while (tmp) {
        Rectangle(hdc, tmp->item.left, tmp->item.top, tmp->item.left + Snake_Size, tmp->item.top + Snake_Size);
        tmp = tmp->next;
    }

    //Drawing snake
    SelectObject(hdc, Snake_Pen);
    SelectObject(hdc, Snake_Brush);
    tmp = _SNAKE;
    while (tmp) {
        Rectangle(hdc, tmp->item.left, tmp->item.top, tmp->item.left + Snake_Size, tmp->item.top + Snake_Size);
        tmp = tmp->next;
    }

}
//---------------------------------------------------------------------------------
void CsEngine::Draw_Apple(HDC hdc, RECT& paint_area) {

    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);
    Ellipse(hdc, Prev_Apple.left, Prev_Apple.top, Prev_Apple.left+Apple_Size, Prev_Apple.top + Apple_Size);

    SelectObject(hdc, Apple_Pen);
    SelectObject(hdc, Apple_Brush);
   Ellipse( hdc,Apple_X_Pos,Apple_Y_Pos, Apple_X_Pos+Apple_Size, Apple_Y_Pos + Apple_Size);
}
//---------------------------------------------------------------------------------
void CsEngine::Draw_Frame(HDC hdc,RECT& paint_area) {//Draw game screen
    Draw_Game_Board(hdc);
    Draw_Snake(hdc, paint_area);
    Draw_Apple(hdc, paint_area);
}
//---------------------------------------------------------------------------------
int CsEngine::On_Timer() {//Snake`s moving on timer
    To_Turn++;
    if (To_Turn == 2) {
        Turn = true;
        To_Turn = 0;
    }
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
int CsEngine::On_Key_Down(EKey_Type key) {//Changing direction of Snake`s moving on key down
    switch (key)
    {
    case EKT_None:
        break;
    case EKT_Up:if (Direction != ESD_down && Turn) {
        Direction = ESD_Up; To_Turn = 0; Turn = false;
    }
        break;
    case EKT_Down: if (Direction != ESD_Up && Turn) { Direction = ESD_down; To_Turn = 0; Turn = false; }
        break;
    case EKT_Left: if (Direction != ESD_Right && Turn) { Direction = ESD_Left; To_Turn = 0; Turn = false; }
        break;
    case EKT_Right: if (Direction != ESD_Left && Turn) { Direction = ESD_Right; To_Turn = 0; Turn = false; }
        break;
    default:
        break;
    }
    return 0;
}