#include <ncurses.h>
#include <stdlib.h>
#include <ctime>
#include "header/game.hpp"
#include "header/utils.hpp"
#include "header/Map.hpp"

// debug info at top screen printing the room key, cols and lines
void debugRoom(Map myMap)
{
    MyString string1, string2, string3;
    string1 += "Room key: ";
    string1 += itoa(myMap.rooms->currentRoom.getKey());
    mvaddstr(0, 0, string1.get());
    string2 = "Colonne: ";
    string2 += itoa(COLS);
    mvaddstr(1, 0, string2.get());
    string3 = "Righe: ";
    string3 += itoa(LINES);
    mvaddstr(2, 0, string3.get());

    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());

    /*clearScreen(0, 0, string1.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
    clearScreen(1, 0, string2.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
    clearScreen(2, 0, string3.getLength(), myMap.rooms->currentRoom.getWindow(), 2);*/
}
// debug info at top screen printing the coords of the doors
void debugDoors(Map myMap, int y, int x)
{
    MyString string1, string2, string3, string4;
    door myDoor = myMap.rooms->currentRoom.getDoor(1);
    string1 += "Next door: ";
    string1 += "y= ";
    string1 += itoa(myDoor.y);
    string1 += ", x= ";
    string1 += itoa(myDoor.x);
    string1 += ", side= ";
    string1 += itoa(myDoor.side);
    mvaddstr(y, x, string1.get());
    myDoor = myMap.rooms->currentRoom.getDoor(0);
    string2 += "Previous door: ";
    string2 += "y= ";
    string2 += itoa(myDoor.y);
    string2 += ", x= ";
    string2 += itoa(myDoor.x);
    string2 += ", side= ";
    string2 += itoa(myDoor.side);
    mvaddstr(y + 1, x, string2.get());

    /*myDoor = myMap.rooms->currentRoom.getDoor(2);
    string3 += "Top side: ";
    string3 += "y: ";
    string3 += itoa(myDoor.y);
    string3 += ", x: ";
    string3 += itoa(myDoor.x);
    mvaddstr(y + 2, x, string3.get());
    myDoor = myMap.rooms->currentRoom.getDoor(3);
    string4 += "Right side: ";
    string4 += "y: ";
    string4 += itoa(myDoor.y);
    string4 += ", x: ";
    string4 += itoa(myDoor.x);
    mvaddstr(y + 3, x, string4.get());
*/
    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());

    /*clearScreen(y, x, string1.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
    clearScreen(y + 1, x, string2.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
    clearScreen(y + 2, x, string3.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
    clearScreen(y + 3, x, string4.getLength(), myMap.rooms->currentRoom.getWindow(), 2);*/
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
/*void changeRoom(Map myMap, int side)
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
}*/

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
    // myMap.createRooms(-1, NULL); // first room
    // debugDoors(myMap, 0, 40);
    debugRoom(myMap);
    // debugDoors(myMap, 0, 40);
    MyString str;
    door tmp;
    int ch; // pressed key

    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case KEY_LEFT:

            // simula entrata player porta sinistra
            if (myMap.rooms->currentRoom.getDoor(1).side == 1)
            { // check if next door is located on left side. FIXME: check if PLAYERS is located on left side && porta deve essere aperta!!!
                if (myMap.createRoom(myMap.rooms->currentRoom.getDoor(1)))
                {
                    str += "Stanza successiva creata, key: ";
                    str += itoa(myMap.rooms->nextRoom->currentRoom.getKey());
                    mvaddstr(0, 56, str.get());
                    refresh();
                    wrefresh(myMap.rooms->currentRoom.getWindow());
                    str.reset();
                    if (myMap.changeRoom(1))
                    {
                        wclear(myMap.rooms->previousRoom->currentRoom.getWindow());
                        wclear(myMap.rooms->currentRoom.getWindow());
                        str += "Entrato nella stanza: ";
                        str += itoa(myMap.rooms->currentRoom.getKey());
                        mvaddstr(1, 56, str.get());
                        myMap.rooms->currentRoom.drawLook();
                        refresh();
                        wrefresh(myMap.rooms->currentRoom.getWindow());
                        str.reset();

                        // clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);

                        /*myMap.rooms->currentRoom.drawLook();
                        refresh();
                        wrefresh(myMap.rooms->currentRoom.getWindow());*/
                    }
                    else
                    {
                        str += "Impossibile entrare";
                        mvaddstr(0, 56, str.get());
                        // clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
                    }
                }
                else
                {
                    str += "Stanza successiva già esistente";
                    mvaddstr(0, 58, str.get());
                    refresh();
                    wrefresh(myMap.rooms->currentRoom.getWindow());
                }
            }
            else
            {
                str += "Non esite nessuna stanza in LEFT SIDE";
                mvaddstr(0, 56, str.get());
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
                clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
                str.reset();
            }

            // if (myMap.rooms->currentRoom.getDoorSide(1)){}
            // str = "Next door side: ";
            // str += itoa(myMap.rooms->currentRoom.getDoor(1).side);
            // mvaddstr(6, 0, str.get());
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

            // str += itoa(myMap.rooms->door[0]->currentRoom.getKey());
            // tmp = myMap.rooms->door[0]->currentRoom.getDoor(0);

            break;

        case KEY_RIGHT:
            // simula entrata player porta destra
            //  mvaddstr(4, 0, "Freccia destra"); //just debug info
            //  myMap.rooms.
            if (myMap.rooms->currentRoom.getDoor(1).side == 3) // check if next door is located on left side. FIXME: check if PLAYERS is located on left side
            {
                if (myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor)) // FIXME dovrebbe essere nextroom
                {
                    myMap.rooms->currentRoom.drawLook();
                    refresh();
                    wrefresh(myMap.rooms->currentRoom.getWindow());
                }
                else
                {
                    str += "Stanza già disegnata";
                    mvaddstr(0, 56, str.get());
                    refresh();
                    wrefresh(myMap.rooms->currentRoom.getWindow());
                    clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
                }
            }
            else
            {
                str += "Non esite nessuna stanza in RIGHT SIDE";
                mvaddstr(0, 56, str.get());
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
                clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
                str.reset();
            }
            break;

        case KEY_UP:
            // simula entrata player porta superiore

            break;

        case KEY_DOWN:
            // simula entrata player porta inferiore

            break;

        case 'd':
            // DEBUGGING INFO
            clearScreen(0, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            clearScreen(1, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            clearScreen(2, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);

            debugRoom(myMap);
            debugDoors(myMap, 0, 40);
            break;
        case 'c':
            clearScreen(0, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            clearScreen(1, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            clearScreen(2, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            clearScreen(3, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
            break;

        case '0':
            str = "Door 0 room key: ";
            str += itoa(myMap.getKeyByDoor(0));
            mvaddstr(4, 0, str.get());
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
            clearScreen(4, 0, str.getLength(), myMap.rooms->currentRoom.getWindow(), 2);
            str.reset();
            break;

        case '1':
            str = "Door 1 room key: ";
            str += itoa(myMap.getKeyByDoor(1));
            mvaddstr(4, 0, str.get());
            str.reset();
            break;
        default:
            break;
        }

        str.reset();
    }
}
