#include <ncurses.h>

//return new window
WINDOW *newWindow(int height, int width, int starty, int startx);

//destroy the given window
void destroyWindow(WINDOW *localWindow);
