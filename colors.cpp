#include "header/colors.hpp"
int maxcol = COLORS;           // maximum numb of colors
int maxcolpairs = COLOR_PAIRS; // maximum numb of pairs
/*
colors
COLOR_BLACK	0
COLOR_RED	1
COLOR_GREEN	2
COLOR_YELLOW	3
COLOR_BLUE	4
COLOR_MAGENTA	5
COLOR_CYAN	6
COLOR_WHITE	7

*/

int start_color();
init_pair(1, COLOR_YELLOW, COLOR_BLACK); // first color is font color, second is background color
init_pair(2, COLOR_BLACK, COLOR_YELLOW); // color for selected item
init_pair(3, COLOR_WHITE, COLOR_BLACK);  // bianco su nero
init_pair(4, COLOR_BLACK, COLOR_WHITE);  // nero su bianco
