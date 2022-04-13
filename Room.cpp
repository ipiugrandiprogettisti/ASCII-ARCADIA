// Room class file

#include "header/Room.hpp"
#include "header/MyString.hpp"
#include "header/utils.hpp"

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
    //just debug information
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
    int roomWidth = maxCols / 1.5 + 1, roomHeigth = maxLines / 2 + 1;
    int halfY = maxCols / 2, halfX = maxLines / 2;
    int adjWidth = halfX - roomWidth / 2;   // adjusted width
    int adjHeigth = halfY - roomHeigth / 2; // adjusted heigth

    win = newwin(roomHeigth, roomWidth, roomHeigth / 2, roomWidth / 4); // create a CENTERED box

    // create the ROOM (box)
    box(win, 0, 0);
}

/*
//funzione prova
//customBox(roomWin, heigth, width, ACS_HLINE, ACS_VLINE, ACS_UARROW, ACS_RARROW, ACS_DARROW, ACS_LARROW);
FIXME TO FIX!
// draws a box with custom corners, SX / RX are the north corners, sx / rx are the south corners.
void customBox(WINDOW *win, int heigth, int width, chtype hLine, chtype vLine, chtype SXCorner, chtype RXCorner, chtype sxCorner, chtype rxCorner)
{
    int halfY = width / 2;
    int halfX = heigth / 2;
    int adjWidth = halfX - width / 2;   // adjusted width
    int adjHeigth = halfY - heigth / 2; // adjusted heigth
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width)
            mvwaddch(win, halfY - heigth / 2, adjWidth + i, SXCorner);
        else
            mvwaddch(win, halfY - heigth / 2, adjWidth + i, hLine);
    }
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width)
            mvwaddch(win, halfY + heigth / 2, adjWidth + i, RXCorner);

        else
            mvwaddch(win, halfY + heigth / 2, adjWidth + i, hLine);
    }

    for (int i = 0; i < heigth; i++)
    {
        if (i == 0 || i == heigth - 1)
            mvwaddch(win, adjHeigth + i, adjWidth + width, sxCorner);
        else
            mvwaddch(win, adjHeigth + i, adjWidth + width, vLine);
    }
    for (int i = 0; i < heigth; i++)
    {
        if (i == 0 || i == heigth - 1)
            mvwaddch(win, adjHeigth + i, adjWidth, rxCorner);
        else
            mvwaddch(win, adjHeigth + i, adjWidth, vLine);
    }
}
*/
