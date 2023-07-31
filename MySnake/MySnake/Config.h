#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include<vector>

enum EKey_Type {
	EKT_None,
	EKT_Up,
	EKT_Down,
	EKT_Left,
	EKT_Right
};
enum ESnake_Direction {
	ESD_None,
	ESD_Left,
	ESD_Right,
	ESD_Up,
	ESD_down
};

//Coordinates grid
static int Grid[] = { 11,
21,31,41,51,61,71,81,91,101,111,
121,131,141,151,161,171,181,191,201,211,
221,231,241,251,261,271,281,291,301,311,
321,331,341,351,361,371,381,391,401,411,
421,431,441,451 };

