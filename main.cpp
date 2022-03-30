#include <ncurses.h>
#include "header/game.hpp"

int main(int argc, char *argv[])
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

   
    int choice = getMenu(maxX, maxY, 0, 0); //draw main menu and get user choice;:0: Play, 1: Credits, 2: Exit
    
    

    endwin(); // End curses mode

    return 0;
}
