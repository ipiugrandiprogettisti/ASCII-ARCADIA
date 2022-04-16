// Room class file

#include "header/Room.hpp"
#include "header/MyString.hpp"
#include "header/utils.hpp"

//  draws a box with custom corners, SX / RX are the north corners, sx / rx are the south corners.
/*void customBox(WINDOW *win, int roomHeigth, int roomWidth, int winHeigth, int winWidth, chtype hLine, chtype vLine)
{
    int halfY = winWidth / 2;
    int halfX = winHeigth / 2;
    int adjWidth = (winWidth - roomWidth) / 2;    // adjusted width
    int adjHeigth = (winHeigth - roomHeigth) / 2; // adjusted heigth

    for (int i = 0; i < roomWidth; i++)
    {
        if (i == 0 || i == roomWidth)
            mvwaddch(win, halfY - roomHeigth / 2, adjWidth + i, ACS_PLUS);
        else
            mvwaddch(win, 20, adjWidth + i, ACS_HLINE);
    }
    for (int i = 0; i < roomWidth; i++)
    {
        if (i == 0 || i == roomWidth)
            mvwaddch(win, halfY + roomHeigth / 2, adjWidth + i, ACS_PLUS);

        else
            mvwaddch(win, halfY + roomHeigth / 2, adjWidth + i, ACS_HLINE);
    }

    // est side
    /*for (int i = 0; i < roomHeigth; i++)
    {
        if (i == 0 || i == roomHeigth - 1)
            mvwaddch(win, adjHeigth + i, adjWidth + width, ACS_PLUS);
        else
            mvwaddch(win, adjHeigth + i, adjWidth + width, ACS_VLINE);
    }
    // ovest side
    for (int i = 0; i < roomHeigth; i++)
    {
        if (i == 0 || i == roomHeigth - 1)
            mvwaddch(win, adjHeigth + i, adjWidth, ACS_PLUS);
        else
            mvwaddch(win, adjHeigth + i, adjWidth, ACS_VLINE);
    }
}*/

// Constructor
Room ::Room()
{
    int key = -1;  // a room is always created with a given key. if no set it to -1 (error)
    win = nullptr; // at the time of creating a room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new listArtifacts;
    objects.enemies = new listEnemies;
    objects.artifacts = nullptr; // set the amount of artifacts in the room to 0
    objects.enemies = nullptr;   // set the amount of artifacts in the room to 0
}

// Constructor
Room::Room(int key)
{
    this->key = key;     // unique
    this->win = nullptr; // at the time of creating a room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new listArtifacts;
    objects.enemies = new listEnemies;
    objects.artifacts = nullptr; // set the amount of artifacts in the room to 0
    objects.enemies = nullptr;   // set the amount of artifacts in the room to 0
}

// returns the key of the room
int Room::getKey()
{
    return key;
}

// returns the WINDOW of the room
WINDOW *Room::getWindow()
{
    return win;
}

void Room::draw(int maxCols, int maxLines)
{
    WINDOW *room;

    // this prints in the main window
    MyString str = MyString();
    // just debug information
    str.append("Room key: ");
    str.append(itoa(this->key));
    mvaddstr(0, 0, str.get());
    str.reset();
    str.append("Colonne: ");
    str.append(itoa(maxCols));
    mvaddstr(1, 0, str.get());
    str.reset();
    str.append("Righe: ");
    str.append(itoa(maxLines));
    mvaddstr(2, 0, str.get());

    // this will prints in the room window, which is a smaller window in the terminal
    int roomWidth = maxCols / 1.5 + 1, roomHeigth = maxLines / 2 + 1; // room dimensions
    int halfY = maxCols / 2, halfX = maxLines / 2;
    int adjWidth = halfX - roomWidth / 2;            // adjusted width
    int adjHeigth = halfY - roomHeigth / 2;          // adjusted heigth
    int offY = roomHeigth / 2, offX = roomWidth / 4; // offset; useful to center box
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_YELLOW);

    win = newwin(roomHeigth, roomWidth, offY, offX); // create a CENTERED box
    
    wbkgd(stdscr, COLOR_PAIR(1));

    //  create the ROOM (box)
    //wborder(win,);

    //customBox(win, roomHeigth - 2, roomWidth - 2, maxLines, maxCols, ACS_HLINE, ACS_VLINE);
    // wbkgd(win, COLOR_PAIR(1));
}

// funzione prova
// customBox(roomWin, heigth, width, ACS_HLINE, ACS_VLINE, ACS_UARROW, ACS_RARROW, ACS_DARROW, ACS_LARROW);
