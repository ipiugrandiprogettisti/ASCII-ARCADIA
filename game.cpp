#include "header/game.hpp"

// prints ascii art
void printAscii()
{
    int halfY = LINES / 2 - 2;
    int halfX = COLS / 2 - 2;
    FILE *asciiArt = fopen("asciiArt.txt", "r");
    char c;
    int i = 0, j = 0;

    // read and print ascii art
    while ((c = fgetc(asciiArt)) != EOF)
    {
        if (c != '\n')
        {
            mvaddch(i + 7, halfX - 33 + j, c);
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

void printDeathAscii()
{
    int halfY = LINES / 2 - 2;
    int halfX = COLS / 2 - 2;
    FILE *asciiDeathArt = fopen("asciiDeathArt.txt", "r");
    char c;
    int i = 0, j = 0;

    // read and print ascii art
    while ((c = fgetc(asciiDeathArt)) != EOF)
    {
        if (c != '\n')
        {
            mvaddch(i + 7, halfX - 22 + j, c);
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }

    fclose(asciiDeathArt);
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
- 1: Exit
*/
int getMenu(WINDOW *myWin)
{
    const int MAX_ITEMS = 2,
              MIN_ITEMS = 0;
    int width, height, halfX, halfY;
    char menuItems[MAX_ITEMS][MAX_LENGTH_ITEM] = {"Play", "Exit"};
    int selectedItem = 0; // could only be -1, 0 or 1. 0 is default

    // WINDOW *myWin = newwin(maxY, maxX, offY, offX);
    wrefresh(myWin);

    start_color();                         /* Start color 			*/
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // first color is font color, second is background color
    init_pair(2, COLOR_BLACK, COLOR_CYAN); // color for selected item
    wbkgd(myWin, COLOR_PAIR(1));           // sets all window attribute
    wrefresh(myWin);

    printAscii();

    printMenu(selectedItem, MAX_ITEMS, menuItems);

    // prints credits at the bottom of the screen
    attron(COLOR_PAIR(1));
    mvaddstr(LINES - 5, COLS / 2 - 77 / 2, "Annalisa Poluzzi, Enrico Ferraiolo, Francesco Menarini, Nicole Sabrina Marro");
    attroff(COLOR_PAIR(1));

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

int deathMenu(WINDOW *myWin)
{
    const int MAX_ITEMS = 2,
              MIN_ITEMS = 0;
    int width, height, halfX, halfY;
    char menuItems[MAX_ITEMS][MAX_LENGTH_ITEM] = {"Try again", "Exit"};
    int selectedItem = 0;

    wrefresh(myWin);

    start_color();                         /* Start color 			*/
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // first color is font color, second is background color
    init_pair(2, COLOR_BLACK, COLOR_CYAN); // color for selected item
    wbkgd(myWin, COLOR_PAIR(1));           // sets all window attribute
    wrefresh(myWin);

    printDeathAscii();

    printMenu(selectedItem, MAX_ITEMS, menuItems);

    int ch; // pressed key
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 10:
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

void printInfo(int life, int score, int key)
{
    clearScreen(3, COLS / 2 - 32, 204, stdscr, 0);
    attron(COLOR_PAIR(1));
    mvprintw(3, COLS / 2 - 32, "ROOM: %d       HEARTS: %d     LIFEPOINTS: %d      SCORE: %d", key, life, 10 * life, score);
    attroff(COLOR_PAIR(1));
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

            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());
        }
        else
        {
            mvprintw(0, 56, "Impossibile entrare");
            clearScreen(0, 56, 20, myMap.rooms->currentRoom.getWindow(), 1);
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

    return myMap;
}

// starts the game
void startGame(WINDOW *myWin)
{

    clear();

    p_bulletlist headB = NULL;

    // creation of the protagonist (player)
    Protagonist P(TRUE, headB, 10, 0, 1, 1, ACS_PI);

    Map myMap = Map(myWin); // Map initialize
    door emptyDoor;         // empty door
    // Now game draws first room
    myMap.rooms->currentRoom.setUp(COLS, LINES, emptyDoor);

    // spawns protagonist info
    printInfo(P.getLife(), P.get_score(), myMap.rooms->currentRoom.getKey());

    // spawns protagonist
    myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());

    myMap.rooms->currentRoom.drawLook();

    refresh();
    wrefresh(myMap.rooms->currentRoom.getWindow());

    
    int ch; // pressed key
    bool flag = false;
    int count = 0;
    p_bulletlist tmplist = NULL;
    int maxY, maxX, offY = 0, offX = 0;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *deathwin = newwin(maxY, maxX, offY, offX);

    // KEYBOARD EVENT LISTENER
    while (ch = getch())
    {
        if (P.getisAlive() == FALSE)
        {
            int choice = deathMenu(deathwin); // draw main menu and get user choice: 0: Play, 1: Exit
            wclear(deathwin);
            wrefresh(deathwin);

            switch (choice) // handle choice
            {
            case 1: // EXIT
                endwin();
                exit(1);
                break;
            case 0: // TRY AGAIN
                startGame(deathwin);

                break;
            default:
                endwin();
                exit(1);
                break;
            }
        }

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
            printInfo(P.getLife(), P.get_score(), myMap.rooms->currentRoom.getKey());

            myMap.rooms->currentRoom.drawLook();
            refresh();
            wrefresh(myMap.rooms->currentRoom.getWindow());

            switch (ch)
            {
            case 'a':
            case 'A':

                // player enters left door
                if (P.getPosition().x == 0)
                {
                    if (P.getPosition().y - 1 == 14 && P.getPosition().y + 1 == 16)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(P.getPosition().y, 98);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(1, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 1);
                
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 'd':
            case 'D':

                // player enters right door
                if (P.getPosition().x == 99)
                {
                    if (P.getPosition().y - 1 == 14 && P.getPosition().y + 1 == 16)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(P.getPosition().y, 1);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(3, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 3);
                

                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 'w':
            case 'W':

                // player enters front door
                if (P.getPosition().y == 0)
                {
                    if (P.getPosition().x - 1 == 49 && P.getPosition().x + 1 == 51)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(28, P.getPosition().x);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(2, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 2);
                
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 's':
            case 'S':

                // player enters back door
                if (P.getPosition().y == 29)
                {
                    if (P.getPosition().x - 1 == 49 && P.getPosition().x + 1 == 51)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(1, P.getPosition().x);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(0, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 0);

                

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

            default:
                break;
            }
            count++;
        }
        else
        {
            if (count <= 2)
            {
                myMap.rooms->currentRoom.allABullMov(P);
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());
            }

            switch (ch)
            {
            case 'a':
            case 'A':

                // player enters left door
                if (P.getPosition().x == 0)
                {
                    if (P.getPosition().y - 1 == 14 && P.getPosition().y + 1 == 16)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(P.getPosition().y, 98);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(1, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 1);
                
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 'd':
            case 'D':

                // player enters right door
                if (P.getPosition().x == 99)
                {
                    if (P.getPosition().y - 1 == 14 && P.getPosition().y + 1 == 16)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(P.getPosition().y, 1);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(3, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 3);
                

                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 'w':
            case 'W':

                // player enters front door
                if (P.getPosition().y == 0)
                {
                    if (P.getPosition().x - 1 == 49 && P.getPosition().x + 1 == 51)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(28, P.getPosition().x);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(2, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 2);
                
                myMap.rooms->currentRoom.drawLook();
                refresh();
                wrefresh(myMap.rooms->currentRoom.getWindow());

                break;

            case 's':
            case 'S':

                // player enters back door
                if (P.getPosition().y == 29)
                {
                    if (P.getPosition().x - 1 == 49 && P.getPosition().x + 1 == 51)
                    {
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), ' ');
                        P.setPosition(1, P.getPosition().x);
                        tmplist = P.getHeadB();
                        while (tmplist != NULL)
                        {
                            myMap.rooms->currentRoom.placeObject(tmplist->B.bulletpos, ' ');
                            tmplist = tmplist->next;
                        }
                        P.setHeadB(NULL);
                        myMap = crossRoom(0, myMap);
                        myMap.rooms->currentRoom.placeObject(P.getPosition(), P.get_tag());
                        flag = false;
                    }
                }

                // player's movement
                myMap.rooms->currentRoom.ProtagonistMovement(P, 0);

                

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

            default:
                break;
            }
            count++;
        }
    }
}