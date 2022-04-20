#include <ncurses.h>
#include <stdlib.h>
#include "header/MyString.hpp"
#include "header/game.hpp"
#include "header/utils.hpp"
#include "header/Map.hpp"

// print main menu, sel is selected item to highlight
void printMenu(int sel, int totItems, char menuItems[][MAX_LENGTH_ITEM])
{
    int halfY = LINES / 2 - 2;
    int halfX = COLS / 2 - 2;
    int padding = 0; // set padding between menu items when displayed
    for (int i = 0; i < totItems; i++)
    {

        // check if current item is the selected one, if it is like so print it glowly
        if (i == sel)
        {
            attron(COLOR_PAIR(2));
            mvaddstr(halfY + padding, halfX, menuItems[i]);
            attroff(COLOR_PAIR(2));
        }
        else
        {
            attron(COLOR_PAIR(1));
            mvaddstr(halfY + padding, halfX, menuItems[i]);
            attroff(COLOR_PAIR(1));
        }
        padding += 3;
    }
}

/*
draw the main menu and returns choice taken by user:
- 0: Play
- 1: Credits
- 2: Exit
*/
int getMenu(WINDOW *myWin)
{
    const int MAX_ITEMS = 3,
              MIN_ITEMS = 0;
    int width, height, halfX, halfY;
    char menuItems[MAX_ITEMS][MAX_LENGTH_ITEM] = {"Play", "Credits", "Exit"};
    int selectedItem = 0; // could only be -1, 0 or 1. 0 is default

    // WINDOW *myWin = newwin(maxY, maxX, offY, offX);
    wrefresh(myWin);

    start_color();                           /* Start color 			*/
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // first color is font color, second is background color
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // color for selected item
    wbkgd(myWin, COLOR_PAIR(1));             // sets all window attribute
    wrefresh(myWin);
    printMenu(selectedItem, MAX_ITEMS, menuItems);

    int ch; // pressed key
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 10: // 10 is the ASCII for the enter key
            return selectedItem;
            break;
        case KEY_DOWN:
            clrtoeol();
            /*
            clrtoeol():
            erase the current line to the right of the cursor,
            inclusive, to the end of the current line.
            Blanks created by erasure have the current background
            rendition (as set by wbkgdset) merged into them.
            */
            if (selectedItem + 1 >= MAX_ITEMS)
                selectedItem = MIN_ITEMS; // reset selectedItem to MIN_ITEMS (0)
            else
                selectedItem++;
            printMenu(selectedItem, MAX_ITEMS, menuItems);
            wrefresh(myWin);
            break;

        case KEY_UP:
            clrtoeol();
            wrefresh(myWin);
            if (selectedItem - 1 < MIN_ITEMS)
                selectedItem = MAX_ITEMS - 1; // reset selectedItem to MAX_ITEMS (2) //Forse, fixare
            else
                selectedItem--;
            printMenu(selectedItem, MAX_ITEMS, menuItems);
            wrefresh(myWin);
            break;
        }
    }

    return selectedItem;
}

// starts the game
void startGame(WINDOW *myWin)
{
    clear();

    Map myMap = Map(myWin); // Map initialize

    // Now game draws first room, where the player spawns safely
    myMap.rooms->currentRoom.draw(COLS, LINES);
    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());
    door bs;
    MyString str = MyString();
    int doorSide = 0;
    int ch; // pressed key
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case KEY_RIGHT:
            // mvaddstr(4, 0, "Freccia destra"); //just debug info
            // myMap.rooms.
            myMap.rooms->currentRoom.draw(COLS, LINES);
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
            break;
        case KEY_LEFT:
            // if(personaggio è dentro la porta) then...
            // getDoorSide() //per printare poi la porta dal lato giusto nella nuova stanza come previous door
            // creates door0 room

            /*myMap.createRoom(myMap.rooms->currentRoom.getDoor(doorSide));
            if (myMap.rooms->door0 == NULL)
            {
                MyString str = MyString();
                // just debug information
                str.append("La stanza rooms->door0 non esiste");
                mvaddstr(6, 0, str.get());
            }*/
            bs = myMap.rooms->currentRoom.getDoor(0);
            str.append("Bottom side: ");
            str.append("y: ");
            str.append(itoa(bs.y));
            str.append(", x: ");
            str.append(itoa(bs.x));
            mvaddstr(0, 15, str.get());
            str.reset();
            bs = myMap.rooms->currentRoom.getDoor(1);
            str.append("Left side: ");
            str.append("y: ");
            str.append(itoa(bs.y));
            str.append(", x: ");
            str.append(itoa(bs.x));
            mvaddstr(1, 15, str.get());
            str.reset();
            bs = myMap.rooms->currentRoom.getDoor(2);
            str.append("Top side: ");
            str.append("y: ");
            str.append(itoa(bs.y));
            str.append(", x: ");
            str.append(itoa(bs.x));
            mvaddstr(2, 15, str.get());
            str.reset();
            bs = myMap.rooms->currentRoom.getDoor(3);
            str.append("Right side: ");
            str.append("y: ");
            str.append(itoa(bs.y));
            str.append(", x: ");
            str.append(itoa(bs.x));
            mvaddstr(3, 15, str.get());

            // myMap.enterRoom(myMap.rooms->door0->currentRoom.getKey());

            break;
        default:
            break;
        }
    }
}