#include "header/utils.hpp"
#include <ctime>

// custom itoa, converts int to const char *
MyString itoa(int num)
{
    MyString str;
    bool isNeg = false;
    if (num < 0)
    {
        isNeg = true;
        num *= -1;
    }

    if (num == 0)
        str += '0';

    for (int i = 0; num > 0; i++)
    {
        char c = '0' + num % 10;
        str += c;
        num = num / 10;
    }

    if (isNeg)
        str += '-';

    str.reverse();
    return str;
}

// check if screen size is correct to play the game; 110x40
void checkScreen(int screenCols, int screenLines)
{
    while ((screenCols < MIN_COLS) || (screenLines < MIN_LINES))
    {
        refresh();
        move(0, 0);
        printw("Resize your screen...");
        move(1, 0);
        MyString str;
        str += "Minimum resolution is ";
        str += itoa(MIN_LINES);
        str += "x";
        str += itoa(MIN_COLS);
        mvwaddstr(stdscr, 0, 0, str.get());
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
                mvaddstr(y, x + i - 1, " ");
            }
        }
    }
    else
    {
        for (int i = length; i != 0; i--)
        {
            mvaddstr(y, x + i - 1, " ");
        }
    }
    refresh();
    wrefresh(win);
}
