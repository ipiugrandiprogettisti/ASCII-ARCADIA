#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#include "header/game.hpp"
#include "header/utils.hpp"
using namespace std;

//!!TODO!!
// tutte le funzioni clear, erease, ecc.... ritornano ERR o OK; bisogna fare un handler in caso di errori
// fonte: https://linux.die.net/man/3/clear

int main(int argc, char *argv[])
{
    initscr();
    setlocale(LC_ALL, "");

    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    checkScreen(COLS, LINES); // check if screen size is correct to play the game; 110x40
    checkColors();            // check if screen supports color

    int maxY, maxX, offY = 0, offX = 0;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW *myWin = newwin(maxY, maxX, offY, offX);
    int choice = getMenu(myWin); // draw main menu and get user choice: 0: Play, 1: Credits, 2: Exit
    MyString choiceString = itoa(choice);
    mvaddstr(0, 0, choiceString.get()); // FIXME stampa??????
    wclear(myWin);
    wrefresh(myWin);

    switch (choice) // handle choice
    {
    case 2: // EXIT
        endwin();
        cout << "You chose to exit\n";
        return 0;
        break;
    case 1: // CREDITS
        endwin();
        cout << "You chose to see the credits\n";
        return 0;
        break;
    case 0: // PLAY
        startGame(myWin);
        return 0;
        break;
    default:
        endwin();
        cout << "ERROR:\nWrong choice!\n";
        exit(1);
        break;
    }

    endwin(); // End curses mode

    return 0;
}
