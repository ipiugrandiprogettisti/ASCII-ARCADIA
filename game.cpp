#include "header/game.hpp"

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

void printRoomKey(int key)
{
    MyString str;
    str += "Room: ";
    str += itoa(key);
    clearScreen(0, 0, str.getLength(), stdscr, 0);
    mvaddstr(0, 0, str.get());
}

void printInfo(int life, int score)
{
    clearScreen(0, 15, 204, stdscr, 0);
    MyString string;
    string += "HEARTS: ";
    string += itoa(life);

    mvaddstr(0, 30, string.get());

    MyString string2;
    string2 += "LIFEPOINTS: ";
    string2 += itoa(10 * life);

    mvaddstr(0, 80, string2.get());

    MyString string3;
    string3 += "SCORE: ";
    string3 += itoa(score);

    mvaddstr(0, 120, string3.get());
}

void printDebug(int n)
{
    MyString str;
    str += "Debug: ";
    str += itoa(n);
    clearScreen(10, 0, str.getLength(), stdscr, 0);
    mvaddstr(10, 0, str.get());
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

        if (myMap.changeRoom(1)) // changeroom ritorna true se si è cambiata stanza
        {
            myMap.rooms->currentRoom.drawLook();
            printRoomKey(myMap.rooms->currentRoom.getKey());
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
            printRoomKey(myMap.rooms->currentRoom.getKey());
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

    p_bulletlist headB = NULL;

    // creation of the protagonist (player)
    Protagonist P(0, headB, 10, 10, 1, 1, 1, ACS_PI);

    Map myMap = Map(myWin); // Map initialize
    door emptyDoor;         // empty door
    // Now game draws first room, where the player spawns safely
    myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor);

    // spawns protagonist info
    printInfo(P.getLife(), P.getScore());

    // spawns protagonist
    myMap.rooms->currentRoom.placeObject(P.position, P.tag);

    myMap.rooms->currentRoom.drawLook();
    printRoomKey(myMap.rooms->currentRoom.getKey());
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
    int move;
    bool flag = false;

    // KEYBOARD EVENT LISTENER

    while ((ch = getch()))
    {
        if (flag == false && myMap.rooms->currentRoom.getObjectList().enemies == NULL)
        {
            myMap.rooms->currentRoom.placePower(true);
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
            flag = true;
        }
        myMap.rooms->currentRoom.allEnemyMov(P);
        myMap.rooms->currentRoom.spawnEnBull();
        myMap.rooms->currentRoom.allEnBullet_move(P);

        //printInfo(P.getLife(), P.getScore());

        myMap.rooms->currentRoom.drawLook();
        refresh();
        wrefresh(myMap.rooms->currentRoom.getWindow());

        switch (ch)
        {
        case 'a':
        case 'A':

            // player enters left door
            if (P.position.x == 0)
            {
                if (P.position.y - 1 == 14 && P.position.y + 1 == 16)
                {
                    myMap.rooms->currentRoom.placeObject(P.position, ' ');
                    P.position.x = 98;
                    myMap = crossRoom(1, myMap);
                    myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                    flag = false;
                }
            }

            // player's movement
            move = myMap.rooms->currentRoom.ProtagonistMovement(P, 1);
            //printInfo(P.getLife(), P.getScore());
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());

            break;

        case 'd':
        case 'D':

            // player enters right door
            if (P.position.x == 99)
            {
                if (P.position.y - 1 == 14 && P.position.y + 1 == 16)
                {
                    myMap.rooms->currentRoom.placeObject(P.position, ' ');
                    P.position.x = 1;
                    myMap = crossRoom(3, myMap);
                    myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                    flag = false;
                }
            }

            // player's movement
            move = myMap.rooms->currentRoom.ProtagonistMovement(P, 3);
            //printInfo(P.getLife(), P.getScore());

            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());

            break;

        case 'w':
        case 'W':

            // player enters front door
            if (P.position.y == 0)
            {
                if (P.position.x - 1 == 49 && P.position.x + 1 == 51)
                {
                    myMap.rooms->currentRoom.placeObject(P.position, ' ');
                    P.position.y = 28;
                    myMap = crossRoom(2, myMap);
                    myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                    flag = false;
                }
            }

            // player's movement
            move = myMap.rooms->currentRoom.ProtagonistMovement(P, 2);
            //printInfo(P.getLife(), P.getScore());
            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());

            break;

        case 's':
        case 'S':

            // player enters back door
            if (P.position.y == 29)
            {
                if (P.position.x - 1 == 49 && P.position.x + 1 == 51)
                {
                    myMap.rooms->currentRoom.placeObject(P.position, ' ');
                    P.position.y = 1;
                    myMap = crossRoom(0, myMap);
                    myMap.rooms->currentRoom.placeObject(P.position, P.tag);
                    flag = false;
                }
            }

            // player's movement
            move = myMap.rooms->currentRoom.ProtagonistMovement(P, 0);

            //printInfo(P.getLife(), P.getScore());

            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());

            break;

        case KEY_LEFT:

            myMap.rooms->currentRoom.spawnAllyBullet(P, 1);
            break;

        case KEY_RIGHT:

            myMap.rooms->currentRoom.spawnAllyBullet(P, 3);
            break;

        case KEY_UP:

            myMap.rooms->currentRoom.spawnAllyBullet(P, 2);
            break;

        case KEY_DOWN:
            myMap.rooms->currentRoom.spawnAllyBullet(P, 0);
            break;

        case 'i':
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
        myMap.rooms->currentRoom.allABullMov(P);
        printInfo(P.getLife(), P.getScore());

        str.reset();
    }
}
