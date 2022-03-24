#include <ncurses.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include "header/myLib.hpp"

int main(int argc, char *argv[])
{

    initscr();            /* Start curses mode 		*/
                          /* Line buffering disabled, Pass on
                           * everty thing to me 		*/
    keypad(stdscr, TRUE); /* I need that nifty F1 	*/
    noecho();
    curs_set(0);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    // draw main menu and get user choice 0 is play, 1 is credits. -1 is error.
    int choice = getMenu(maxX, maxY, 0, 0);

    endwin(); // End curses mode

    return 0;
}
