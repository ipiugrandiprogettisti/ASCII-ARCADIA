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

    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());
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

// FIXME: a volte la stessa stanza è ripetuta 2 volte di fila
Map crossRoom(int enteringSide, Map myMap)
{
    MyString str;

    if (myMap.rooms->currentRoom.getDoor(1).side == enteringSide && myMap.rooms->currentRoom.getDoor(1).isOpen == true) // GO TO NEXT ROOM
    {
        myMap.createRoom(myMap.rooms->currentRoom.getDoor(1));

        refresh();
        wrefresh(myMap.rooms->currentRoom.getWindow());

        if (myMap.changeRoom(1))
        {
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
        }
        else
        {
            str += "Impossibile entrare";
            mvaddstr(0, 56, str.get());
            clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
        }
    }
    else if (myMap.rooms->currentRoom.getDoor(0).side == enteringSide && myMap.rooms->currentRoom.getDoor(0).isOpen == true) // GO TO PREVIOUS ROOM
    {
        if (myMap.changeRoom(0))
        {
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
        }
    }
    else
    {
        /*str += "Non esite (o è chiusa) nessuna stanza in ";
        str += itoa(enteringSide);
        str += " SIDE";
        mvaddstr(0, 56, str.get());
        refresh();
        wrefresh(myMap.rooms->currentRoom.getWindow());
        clearScreen(0, 56, str.getLength(), myMap.rooms->currentRoom.getWindow(), 1);
        str.reset();*/
    }

    str.reset();

    return myMap;
}

// starts the game
void startGame(WINDOW *myWin)
{
    clear();

    // prova
    p_inventA headA = NULL;
    p_inventP headP = NULL;
    Protagonist P(10, headA, headP, 10, 10, 1, 3, 1, ACS_PI); // creato protagonista

    Map myMap = Map(myWin); // Map initialize
    door emptyDoor;         // empty door
    // Now game draws first room, where the player spawns safely
    myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor);
    // prova:

    myMap.rooms->currentRoom.placeObject(P.position, P.tag);
    myMap.rooms->currentRoom.drawLook();
    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());

    // DEBUG INFO
    // myMap.createRooms(-1, NULL); // first room
    // debugDoors(myMap, 0, 40);
    // debugRoom(myMap);
    // debugDoors(myMap, 0, 40);

    MyString str;
    pos position;
    int ch; // pressed key

    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case KEY_LEFT:

            // prova di movimento del player:

            pos newPosLeft;
            newPosLeft.y = P.position.y;
            newPosLeft.x = P.position.x - 1;
            if (myMap.rooms->currentRoom.getTile(newPosLeft) == ' ')
            {
                myMap.rooms->currentRoom.placeObject(P.position, ' ');
                P.setPosition(newPosLeft.y, newPosLeft.x);
                myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }

            // simula entrata player porta sinistra
            myMap = crossRoom(1, myMap);
            break;

        case KEY_RIGHT:
            // prova di movimento del player
            pos newPosRight;
            newPosRight.y = P.position.y;
            newPosRight.x = P.position.x + 1;
            if (myMap.rooms->currentRoom.getTile(newPosRight) == ' ')
            {
                myMap.rooms->currentRoom.placeObject(P.position, ' ');
                P.setPosition(newPosRight.y, newPosRight.x);
                myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }

            // simula entrata player porta destra
            myMap = crossRoom(3, myMap);
            break;

        case KEY_UP:
            // prova di movimento del player
            pos newPosUp;
            newPosUp.y = P.position.y - 1;
            newPosUp.x = P.position.x;
            if (myMap.rooms->currentRoom.getTile(newPosUp) == ' ')
            {
                myMap.rooms->currentRoom.placeObject(P.position, ' ');
                P.setPosition(newPosUp.y, newPosUp.x);
                myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }

            // simula entrata player porta superiore
            myMap = crossRoom(2, myMap);
            break;

        case KEY_DOWN:
            // prova di movimento del player
            pos newPosDown;
            newPosDown.y = P.position.y + 1;
            newPosDown.x = P.position.x;
            if (myMap.rooms->currentRoom.getTile(newPosDown) == ' ')
            {
                myMap.rooms->currentRoom.placeObject(P.position, ' ');
                P.setPosition(newPosDown.y, newPosDown.x);
                myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }

            // simula entrata player porta inferiore
            myMap = crossRoom(0, myMap);

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

        case 'o': // opens all doors
            myMap.rooms->currentRoom.openDoors(true);

            /*str += "Cols: ";
            str += itoa(COLS);
            str += "Lines: ";
            str += itoa(LINES);
            mvaddstr(0, 0, str.get());*/
            break;

        case 'p': // closes all doors
            myMap.rooms->currentRoom.openDoors(false);
            break;

        // ESEMPIO .placeObject() senza struct
        case '1': // oggetto in alto a sinistra
            myMap.rooms->currentRoom.placeObject(1, 1, ACS_BULLET);
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
            break;

        // ESEMPIO .placeObject() scon struct pos
        case '2': // oggetto in basso a destra
            position.y = myMap.rooms->currentRoom.getMaxWidth() - 2;
            position.x = myMap.rooms->currentRoom.getMaxHeight() - 2;
            myMap.rooms->currentRoom.placeObject(position, ACS_BULLET);
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
            break;

        default:
            break;
        }

        str.reset();
    }
}
