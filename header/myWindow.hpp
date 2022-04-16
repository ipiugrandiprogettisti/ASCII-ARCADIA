
#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

// return new window
WINDOW *newWindow(int height, int width, int starty, int startx);

// destroy the given window
void destroyWindow(WINDOW *localWindow);

/*
draw the main menu and returns choice taken by user:
-1: error
- 0: Play
- 1: Credits
*/