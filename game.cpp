#include <ncurses.h>
#include <stdlib.h>
#include "header/game.hpp"
#include "header/utils.hpp"
#include "header/Map.hpp"

// debug info at top screen printing the room key, cols and lines
void debugRoom(Map myMap)
{
    MyString string;
    string += "Room key: ";
    string += itoa(myMap.rooms->currentRoom.getKey());
    mvaddstr(0, 0, string.get());
    string = "Colonne: ";
    string += itoa(COLS);
    mvaddstr(1, 0, string.get());
    string = "Righe: ";
    string += itoa(LINES);
    mvaddstr(2, 0, string.get());
}
// debug info at top screen printing the coords of the doors
void debugDoors(Map myMap, int y, int x)
{
    MyString debug;
    door bs = myMap.rooms->currentRoom.getDoor(0);
    debug += "Bottom side: ";
    debug += "y: ";
    debug += itoa(bs.y);
    debug += ", x: ";
    debug += itoa(bs.x);
    mvaddstr(y, x, debug.get());
    debug.reset();
    bs = myMap.rooms->currentRoom.getDoor(1);
    debug += "Left side: ";
    debug += "y: ";
    debug += itoa(bs.y);
    debug += ", x: ";
    debug += itoa(bs.x);
    mvaddstr(y + 1, x, debug.get());
    debug.reset();
    bs = myMap.rooms->currentRoom.getDoor(2);
    debug += "Top side: ";
    debug += "y: ";
    debug += itoa(bs.y);
    debug += ", x: ";
    debug += itoa(bs.x);
    mvaddstr(y + 2, x, debug.get());
    debug.reset();
    bs = myMap.rooms->currentRoom.getDoor(3);
    debug += "Right side: ";
    debug += "y: ";
    debug += itoa(bs.y);
    debug += ", x: ";
    debug += itoa(bs.x);
    mvaddstr(y + 3, x, debug.get());
    debug.reset();
}

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

// when character enter doors, room is changed
void changeRoom(Map myMap, int side)
{
    MyString str;
    pListRooms previousRoom = myMap.rooms;
    door previousDoor = myMap.rooms->currentRoom.getDoor(side);

    if (myMap.enterRoom(side)) // returns true if players has entered the room (it isnt null)
    {
        bool firsTimeInitRoom = myMap.rooms->currentRoom.setUp(COLS, LINES, previousDoor);
        if (firsTimeInitRoom) // if room is created for the first time, then initialize its Room
        {
            myMap.createRooms(side, previousRoom);
        }

        myMap.rooms->currentRoom.drawLook();

        debugRoom(myMap);
        // debugDoors(myMap, 0, 40);
        refresh();
        wrefresh(myMap.rooms->currentRoom.getWindow());
    }
    else
    {
        str = "Stanza non esistente";
        mvaddstr(20, 0, str.get());
    }
}

// starts the game
void startGame(WINDOW *myWin)
{
    clear();

    Map myMap = Map(myWin); // Map initialize
    door emptyDoor;         // empty door
    // Now game draws first room, where the player spawns safely
    myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor);
    myMap.rooms->currentRoom.drawLook();
    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());

    // DEBUG INFO
    myMap.createRooms(-1, NULL); // first room
    // debugDoors(myMap, 0, 40);
    debugRoom(myMap);
    // debugDoors(myMap, 0, 40);
    int doorSide = 0;
    MyString str;
    door tmp;
    int ch; // pressed key
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case KEY_RIGHT:
            // mvaddstr(4, 0, "Freccia destra"); //just debug info
            // myMap.rooms.
            if (myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor))
            {
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }
            else
                mvaddstr(0, 56, "Stanza già disegnata");
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
                str+="La stanza rooms->door0 non esiste");
                mvaddstr(6, 0, str.get());
            }*/

            // myMap.enterRoom(myMap.rooms->door0->currentRoom.getKey());
            str = "Door 0 room key: ";
            // str += itoa(myMap.rooms->door[0]->currentRoom.getKey());
            // tmp = myMap.rooms->door[0]->currentRoom.getDoor(0);
            str += itoa(myMap.getKeyByDoor(0));
            mvaddstr(4, 0, str.get());
            break;

        case 'd':
            // DEBUGGING INFO
            debugRoom(myMap);
            debugDoors(myMap, 0, 40);
            break;

        case '1':
            // TODO FIXME: prima stanza viene ricreata quando si fa changeRoom
            changeRoom(myMap, 0);
            break;

        case '2':
            changeRoom(myMap, 1);
            break;

        case '3':
            changeRoom(myMap, 2);
            break;

        case '4':
            changeRoom(myMap, 3);
            break;
        case 'c':
            break;
        default:
            break;
        }
    }
}
