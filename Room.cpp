// Room class file

#include "header/Room.hpp"
#include "header/MyString.hpp"
#include "header/utils.hpp"
#include <ctime>

// place a door. y and x are position, i is the side where the door is located
void placeDoor(WINDOW *win, door doorInfo)
{
    switch (doorInfo.side)
    {
    case 0: // bottom side
    case 2: // top side
        mvwaddch(win, doorInfo.y, doorInfo.x - 1, ACS_RTEE);
        mvwaddch(win, doorInfo.y, doorInfo.x, ACS_CKBOARD);
        mvwaddch(win, doorInfo.y, doorInfo.x + 1, ACS_LTEE);
        break;
    case 1: // left side
    case 3: // rigth side
        mvwaddch(win, doorInfo.y - 1, doorInfo.x, ACS_BTEE);
        mvwaddch(win, doorInfo.y, doorInfo.x, ACS_CKBOARD);
        mvwaddch(win, doorInfo.y + 1, doorInfo.x, ACS_TTEE);
        break;
    default:
        break;
    }
}

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

    win = newwin(roomHeigth, roomWidth, offY, offX); // create a CENTERED box

    //  create the ROOM (box)
    /*
    int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);
    The argument ls is a character and attributes used for the left side of the border, rs right side, ts - top side,
    bs - bottom side, tl - top left-hand corner, tr - top right-hand corner, bl - bottom left-hand corner,
    and br - bottom right-hand corner.
    If arguments is 0, then is showed default ACS
    */
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    // mvwhline(win, 0, 0, ACS_BLOCK, 5);
    // mvwvline(win, 0, 0, ACS_CKBOARD, 5);

    // now we have to draw 1-4 doors
    srand(time(0));                // seed is 0
    int nDoors = (rand() % 4) + 1; // random number of door from 1 to 4 for first room
    // placing doors
    for (int i = 0; i < nDoors; i++)
    {
        struct door doorInfo;
        doorInfo.side = i;
        switch (doorInfo.side) // match/adjust side to coords
        {
        case 0: // bottom side
            doorInfo.y = roomHeigth - 1;
            doorInfo.x = roomWidth / 2;
            placeDoor(win, doorInfo);
            break;
        case 1: // left side
            doorInfo.y = roomHeigth / 2;
            doorInfo.x = 0;
            placeDoor(win, doorInfo);
            break;
        case 2: // top side
            doorInfo.y = 0;
            doorInfo.x = roomWidth / 2;
            placeDoor(win, doorInfo);
            break;
        case 3: // right side
            doorInfo.y = roomHeigth / 2;
            doorInfo.x = roomWidth - 1;
            placeDoor(win, doorInfo);
            break;

        default:
            break;
        }
    }
}

// returns the given door (struct door) information
struct door Room::getDoor(int side)
{
    struct door porta;
    // FIXME: restituire veri parametri porta  e cambiare nome della variabile
    porta.side = 0;
    porta.y = 0;
    porta.x = 0;
    return porta;
}
