#include <ncurses.h>
#include <stdlib.h>
#include "myLib.hpp"

int main(int argc, char *argv[])
{
    const int MAX_ITEMS = 2, MIN_ITEMS = 0;
    int startX = LINES, startY = COLS, width, height;
    int ch;
    char string[2][20] = {"Gioca", "Crediti"};
    int selectedItem = 0; // could only be -1, 0 or 1. 0 is default

    initscr();            /* Start curses mode 		*/
                          /* Line buffering disabled, Pass on
                           * everty thing to me 		*/
    keypad(stdscr, TRUE); /* I need that nifty F1 	*/
    noecho();
    curs_set(0);
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color(); /* Start color 			*/
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvaddstr(startY, startY, "CIAOO");
    attroff(COLOR_PAIR(1));
    // center string
    startY = LINES / 2 - 1;
    startX = COLS / 2 - 1;
    mvaddstr(startY, startX, string[0]);
    mvaddstr(startY + 3, startX, string[1]);

    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
        case KEY_UP:
            if (selectedItem++ > MAX_ITEMS - 1)
                selectedItem = MIN_ITEMS; // reset selectedItem to 0
            else
                selectedItem++;
            break;
        case KEY_DOWN:
            if (selectedItem-- < MIN_ITEMS - 1)
                selectedItem = MAX_ITEMS; // reset selectedItem to 0
            else
                selectedItem--;
            break;
        }
    }

    endwin(); /* End curses mode		  */
    return 0;
}
