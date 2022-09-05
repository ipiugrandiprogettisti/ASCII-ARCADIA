#include "header/utils.hpp"
#include <iostream>
#include <ctime>


// check if screen size is correct to play the game; 110x40
void checkScreen(int screenCols, int screenLines)
{
    while ((screenCols < MIN_COLS) || (screenLines < MIN_LINES))
    {
        refresh();
        move(0, 0);
        printw("Resize your screen...");
        move(1, 0);
        mvprintw(0, 0, "Minimum screen size is %dx%d", MIN_LINES, MIN_COLS);
        getmaxyx(stdscr, screenCols, screenLines);
    }
}

// check if color is supported by user's terminal
void checkColors()
{
    if (has_colors() == FALSE)
    {
        endwin();
        std::cout << "Your terminal does not support color\n";
        exit(1);
    }
}

// clear the screen with " " in int delay seconds
void clearScreen(int y, int x, int length, WINDOW *win, int delay)
{
    if (delay > 0)
    {
        delay *= CLOCKS_PER_SEC;
        clock_t now = clock();
        while (clock() - now < delay)
        {
            for (int i = length; i != 0; i--)
            {
                mvprintw(y, x + i - 1, " ");
            }
        }
    }
    else
    {
        for (int i = length; i != 0; i--)
        {
            mvprintw(y, x + i - 1, " ");
        }
    }
    refresh();
    wrefresh(win);
}
