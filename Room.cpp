// Room class file

#include "header/Room.hpp"
#include "header/utils.hpp"
#include <ctime>

// place a door. y and x are position, i is the side where the door is located
void Room::placeDoor(WINDOW *win, door doorInfo)
{
    switch (doorInfo.side)
    {
    case 0: // bottom side
    case 2: // top side
        this->look[doorInfo.y][doorInfo.x - 1] = ACS_RTEE;
        this->look[doorInfo.y][doorInfo.x] = ACS_CKBOARD;
        this->look[doorInfo.y][doorInfo.x + 1] = ACS_LTEE;
        break;
    case 1: // left side
    case 3: // rigth side
        this->look[doorInfo.y - 1][doorInfo.x] = ACS_BTEE;
        this->look[doorInfo.y][doorInfo.x] = ACS_CKBOARD;
        this->look[doorInfo.y + 1][doorInfo.x] = ACS_TTEE;
        break;
    default:
        break;
    }
}

// Constructor
Room ::Room()
{
    int key = -1; // a room is always created with a given key. if no set it to -1 (error)
    win = NULL;   // at the time of creating a room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new listArtifacts;
    objects.enemies = new listEnemies;
    objects.artifacts = NULL; // set the amount of artifacts in the room to 0
    objects.enemies = NULL;   // set the amount of artifacts in the room to 0

    // doorInfo are already set when defined, check Room.hpp for more info
}

// Constructor
Room::Room(int key)
{
    this->key = key;  // unique
    this->win = NULL; // at the time of creating a room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new listArtifacts;
    objects.enemies = new listEnemies;
    objects.artifacts = NULL; // set the amount of artifacts in the room to 0
    objects.enemies = NULL;   // set the amount of artifacts in the room to 0

    // doorInfo are already set when defined, check Room.hpp for more info
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

// returns the object list of the room
struct objContainer Room::getObjectList()
{
    return objects;
}

// returns the given room's door information; if door doesn't exist returns -1 door (check struct door)
struct door Room::getDoor(int side)
{
    struct door myDoor;
    // FIXME: cerca tra le stanze

    switch (side)
    {
    case 0:
        myDoor = doorInfo[0];
        break;
    case 1:
        myDoor = doorInfo[1];
        break;
    case 2:
        myDoor = doorInfo[2];
        break;
    case 3:
        myDoor = doorInfo[3];
        break;
    default:
        break;
    }
    return myDoor;
}

// set the given door information
void Room::setDoor(int side, struct door myDoor)
{
    switch (side)
    {
    case 0:
        doorInfo[0] = myDoor;
        break;
    case 1:
        doorInfo[1] = myDoor;
        break;
    case 2:
        doorInfo[2] = myDoor;
        break;
    case 3:
        doorInfo[3] = myDoor;
        break;
    default:
        break;
    }
}

// aux function to draw the look of the room
void Room::drawLook()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int k = 0; k < HEIGTH; k++)
        {
            mvwaddch(this->win, i, k, look[i][k]);
        }
    }
}

// funzione bozza per disegnare una stanza; prima stanza
bool Room::draw(int maxCols, int maxLines)
{
    // if room was already drew there is no need to redraw, so function ends
    if (drawn)
        return false;

    WINDOW *room;

    // this will prints in the room window, which is a smaller window in the terminal
    int winWidth = HEIGTH / 1.5 + 1, winHeigth = WIDTH / 2 + 1; // room dimensions
    int halfY = maxCols / 2, halfX = maxLines / 2;
    int adjWidth = halfX - winWidth / 2;                              // adjusted width
    int adjHeigth = halfY - winHeigth / 2;                            // adjusted heigth
    int offY = (maxLines - WIDTH) / 2, offX = (maxCols - HEIGTH) / 2; // offset; useful to center box

    win = newwin(WIDTH, HEIGTH, offY, offX); // create a CENTERED box

    //  create the ROOM (box)
    /*
    int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);
    The argument ls is a character and attributes used for the left side of the border, rs right side, ts - top side,
    bs - bottom side, tl - top left-hand corner, tr - top right-hand corner, bl - bottom left-hand corner,
    and br - bottom right-hand corner.
    If arguments is 0, then is showed default ACS
    */
    // wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);

    // PLACING DOORS
    // now we have to draw 1-4 doors
    srand(time(0));                       // seed is 0
    int nDoors = (rand() % MAXDOORS) + 1; // random number of door from 1 to 4 for first room
    int placedDoors[nDoors];              // placedDoor[0]=0 means that first door is located at bottom side; placedDoor[1]=2 top side. =-1 not placed
    for (int i = 0; i < nDoors; i++)      // init array to not placed
    {
        placedDoors[i] = -1;
    }

    int i = 0;
    while (i < nDoors)
    {
        int side = rand() % 4; // picking a casual side to place the door
        bool isOccupied = false;
        for (int k = 0; k < nDoors; k++)
        {
            if (placedDoors[k] == side) // check if side is already occupied by other doors
                isOccupied = true;
        }

        if (isOccupied == false) // if side is free then place door
        {
            struct door myDoorTmp;
            myDoorTmp.side = side;
            switch (myDoorTmp.side) // match/adjust side to coords
            {
            case 0: // bottom side
                myDoorTmp.y = WIDTH - 1;
                myDoorTmp.x = HEIGTH / 2;
                placeDoor(win, myDoorTmp);
                setDoor(0, myDoorTmp);
                break;
            case 1: // left side
                myDoorTmp.y = WIDTH / 2;
                myDoorTmp.x = 0;
                placeDoor(win, myDoorTmp);
                setDoor(1, myDoorTmp);
                break;
            case 2: // top side
                myDoorTmp.y = 0;
                myDoorTmp.x = HEIGTH / 2;
                placeDoor(win, myDoorTmp);
                setDoor(2, myDoorTmp);
                break;
            case 3: // right side
                myDoorTmp.y = WIDTH / 2;
                myDoorTmp.x = HEIGTH - 1;
                placeDoor(win, myDoorTmp);
                setDoor(3, myDoorTmp);
                break;

            default:
                break;
            }
        }
        i++;
    }
    drawLook(); // draw self look

    drawn = true; // we drew the room; so we set it as so
    return true;
}

// funzione bozza per disegnare una stanza; seconda + stanza
bool Room::draw(int maxCols, int maxLines, struct door myDoor)
{
    // if room was already drew there is no need to redraw, so function ends
    if (drawn)
        return false;

    WINDOW *room;

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

    // PLACING DOORS
    // placing previous door; it has to be placed on the opposite side where it was in the previous room
    switch (myDoor.side)
    {
    case 0: // bottom side
        myDoor.y = 0;
        placeDoor(win, myDoor);
        break;
    case 1: // left side
        myDoor.x = 0;
        placeDoor(win, myDoor);
        break;
    case 2: // top side
        myDoor.y = roomHeigth - 1;
        placeDoor(win, myDoor);
        break;
    case 3: // right side
        myDoor.x = roomWidth - 1;
        placeDoor(win, myDoor);
        break;

    default:
        break;
    }

    // now we have to draw 1 to 4-1 doors (previous one is already placed)
    srand(time(0));                           // seed is 0
    int nDoors = (rand() % MAXDOORS - 1) + 1; // random number of door from 1 to 4-1 because we already have the previous one

    int placedDoors[nDoors];         // placedDoor[0]=0 means that first door is located at bottom side; placedDoor[1]=2 top side. =-1 not placed
    for (int i = 0; i < nDoors; i++) // init array to not placed
    {
        placedDoors[i] = -1;
    }

    int i = 0;
    while (i < nDoors)
    {
        int side = rand() % 4; // picking a casual side to place the door
        bool isOccupied = false;
        for (int k = 0; k < nDoors; k++)
        {
            if (placedDoors[k] == side || myDoor.side == side) // check if side is already occupied by other doors
                isOccupied = true;
        }

        if (isOccupied == false) // if side is free place door
        {
            struct door myDoorTmp;
            myDoorTmp.side = side;
            switch (myDoorTmp.side) // match/adjust side to coords
            {
            case 0: // bottom side
                myDoorTmp.y = roomHeigth - 1;
                myDoorTmp.x = roomWidth / 2;
                placeDoor(win, myDoorTmp);
                setDoor(0, myDoorTmp);
                break;
            case 1: // left side
                myDoorTmp.y = roomHeigth / 2;
                myDoorTmp.x = 0;
                placeDoor(win, myDoorTmp);
                setDoor(1, myDoorTmp);
                break;
            case 2: // top side
                myDoorTmp.y = 0;
                myDoorTmp.x = roomWidth / 2;
                placeDoor(win, myDoorTmp);
                setDoor(2, myDoorTmp);
                break;
            case 3: // right side
                myDoorTmp.y = roomHeigth / 2;
                myDoorTmp.x = roomWidth - 1;
                placeDoor(win, myDoorTmp);
                setDoor(3, myDoorTmp);
                break;

            default:
                break;
            }
        }
        i++;
    }

    drawn = true;
    return true;
}
