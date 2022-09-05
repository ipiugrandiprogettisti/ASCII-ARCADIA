#ifndef _UTILS
#define _UTILS
#include <ncurses.h>

const int MIN_COLS = 40, MIN_LINES = 110;

// check if screen size is correct to play the game; 110x40
void checkScreen(int screenCols, int screenLines);

// check if color is supported by user's terminal
void checkColors();

// clear the screen with " "
void clearScreen(int y, int x, int length, WINDOW *win, int delay);

#endif