#include "header/game.hpp"


// prints ascii art
void printAscii()
{
    int halfY = LINES / 2 - 2;
    int halfX = COLS / 2 - 2;
    FILE *asciiArt = fopen("asciiArt.txt", "r");
    char c;
    int i = 0, j = 0;
    
    //read and print ascii art
    while ((c = fgetc(asciiArt)) != EOF)
    {
        if (c != '\n')
        {
            mvaddch(i + 7, halfX - 63 + j, c);
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }

    fclose(asciiArt);
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

    printAscii();

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
                selectedItem = MAX_ITEMS - 1; // reset selectedItem to MAX_ITEMS (2)
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
    clearScreen(0, 0, 10, stdscr, 0);
    mvprintw(0, 0, "Room: %d", key);
}

void printInfo(int life, int score)
{
    clearScreen(0, 15, 204, stdscr, 0);

    mvprintw(0, 30, "HEARTS: %d", life);
    mvprintw(0, 80, "LIFEPOINTS: %d", 10*life);
    mvprintw(0, 120, "SCORE: %d", score);
}

// enters new room
Map crossRoom(int enteringSide, Map myMap)
{
    if (myMap.rooms->currentRoom.getDoor(1).side == enteringSide && myMap.rooms->currentRoom.getDoor(1).isOpen == true) // GO TO NEXT ROOM
    {
        myMap.createRoom(myMap.rooms->currentRoom.getDoor(1));

        refresh();
        wrefresh(myMap.rooms->currentRoom.getWindow());

        if (myMap.changeRoom(1)) // changeroom returns true if room has changed
        {
            myMap.rooms->currentRoom.drawLook();
            printRoomKey(myMap.rooms->currentRoom.getKey());
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
        }
        else
        {
            mvprintw(0,56, "Impossibile entrare");
            clearScreen(0, 56, 20, myMap.rooms->currentRoom.getWindow(), 1);
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

    pos position;
    int ch; // pressed key
    bool flag = false;
    int delay = 1;
    bool anna = true;
    int count = 0;

    // KEYBOARD EVENT LISTENER
    while (ch = getch())
    {
        if (count > 10)
        {
            count = 0;
        }

        if ((count == 1))
        {
            if (flag == false && myMap.rooms->currentRoom.getObjectList().enemies == NULL && myMap.rooms->currentRoom.getDrawnPower() == 0)
            {
                myMap.rooms->currentRoom.placePower(true);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
                flag = true;
                myMap.rooms->currentRoom.setDrawnPower(1);
            }
            myMap.rooms->currentRoom.allEnemyMov(P);
            myMap.rooms->currentRoom.spawnEnBull();
            myMap.rooms->currentRoom.allEnBullet_move(P);
            myMap.rooms->currentRoom.allABullMov(P);
            printInfo(P.getLife(), P.getScore());

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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 1);
                // printInfo(P.getLife(), P.getScore());
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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 3);
                // printInfo(P.getLife(), P.getScore());

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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 2);
                // printInfo(P.getLife(), P.getScore());
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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 0);

                // printInfo(P.getLife(), P.getScore());

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

                //debugRoom(myMap);
                //debugDoors(myMap, 0, 40);
                break;
            case 'c':
                clearScreen(0, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(1, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(2, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(3, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                break;

            case 'o': // opens all doors
                myMap.rooms->currentRoom.openDoors(true);
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
            count++;
        }
        else
        {

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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 1);
                // printInfo(P.getLife(), P.getScore());
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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 3);
                // printInfo(P.getLife(), P.getScore());

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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 2);
                // printInfo(P.getLife(), P.getScore());
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
                myMap.rooms->currentRoom.ProtagonistMovement(P, 0);

                // printInfo(P.getLife(), P.getScore());

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

                //debugRoom(myMap);
                //debugDoors(myMap, 0, 40);
                break;
            case 'c':
                clearScreen(0, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(1, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(2, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                clearScreen(3, 0, COLS, myMap.rooms->currentRoom.getWindow(), 0);
                break;

            case 'o': // opens all doors
                myMap.rooms->currentRoom.openDoors(true);
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
            count++;
        }
    }
}