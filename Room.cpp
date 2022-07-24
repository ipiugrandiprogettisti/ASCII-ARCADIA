// Room class file

#include "header/Room.hpp"
#include "header/utils.hpp"
#include <ctime>

// place a door. y and x are position, i is the side where the door is located
void Room::placeDoor(door doorInfo)
{
    switch (doorInfo.side)
    {
    case 0: // bottom side
    case 2: // top side
        this->look[doorInfo.y][doorInfo.x - 1] = ACS_RTEE;
        this->look[doorInfo.y][doorInfo.x + 1] = ACS_LTEE;
        break;
    case 1: // left side
    case 3: // rigth side
        this->look[doorInfo.y - 1][doorInfo.x] = ACS_BTEE;
        this->look[doorInfo.y + 1][doorInfo.x] = ACS_TTEE;
        break;
    default:
        break;
    }

    if (doorInfo.isOpen == false)
        this->look[doorInfo.y][doorInfo.x] = doorInfo.tile.close;
    else
        this->look[doorInfo.y][doorInfo.x] = doorInfo.tile.open;
}

// place object in room
void Room::placeObject(pos position, chtype tag)
{
    this->look[position.y][position.x] = tag;
}

// aux function to prevent non-free wall
bool Room::tileIsFree(pos position)
{
    bool free = false;
    int sidesNotFree = 0;

    if (this->look[position.y + 1][position.x] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y - 1][position.x] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y][position.x + 1] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y][position.x - 1] != ' ')
        sidesNotFree += 1;

    if (sidesNotFree < 4)
        free = true;

    return free;
}

// aux function to free row and col
void Room::freeRowCol(pos position)
{
    bool row = true;
    pos tmp = position;
    while (this->look[tmp.y][tmp.x] != ' ')
    {

        this->look[tmp.y + 1][tmp.x] = ' ';
        tmp.y += 1;
    }
}

// aux function to place walls
void Room::createWall(int width, int heigth, int posY, int posX)
{
    for (int i = 0; i < heigth; i++)
    {
        for (int k = 0; k < width; k++)
        {
            pos position;
            position.y = i + posY, position.x = k + posX;

            if (tileIsFree(position))
            {
                placeObject(position, ACS_CKBOARD);
            }
            /*else FIXME finire freeRowCol
            {
                freeRowCol(position);
            }*/

            /*if ((i == 0 || k == 0 || i == heigth - 1 || k == width - 1) || tileIsFree(position))
            {
                placeObject(position, ACS_CKBOARD);
            }*/
        }
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
    this->win = NULL; // at the time of creating a new room its window will be null. the first time that it will be drawed it also will be assigned
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

// returns the given room's door information; if door doesn't exist returns a "-1" door (check struct door)
struct door Room::getDoor(int isNextRoom)
{
    struct door myDoor;
    myDoor = doorInfo[isNextRoom];

    /*if (doorInfo[isNextRoom].x > -1 || doorInfo[isNextRoom].y > -1)
        myDoor = doorInfo[isNextRoom];*/

    return myDoor;
}

// set the given door information
void Room::setDoor(int isNextRoom, struct door myDoor)
{
    /*switch (side)
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
    }*/

    doorInfo[isNextRoom] = myDoor;
}

// draws the room
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

// sets up the room if myDoor doesnt exist (-1), then it is the first room being set up. myDoor is previous door of the new room, empty if first room
bool Room::setUp(int maxCols, int maxLines, struct door myDoor)
{
    // if room was already drew there is no need to redraw, so function ends
    if (drawn == true)
        return false;

    // if myDoor is a real door, then it isnt the first room that is being set up
    bool previousRoomExists = false;
    if (myDoor.x >= 0 || myDoor.y >= 0)
    {
        previousRoomExists = true;
    }

    WINDOW *room;

    // this will prints in the room window, which is a smaller window in the terminal
    int winWidth = HEIGTH / 1.5 + 1, winHeigth = WIDTH / 2 + 1; // room dimensions
    int halfY = maxCols / 2, halfX = maxLines / 2;
    int adjWidth = halfX - winWidth / 2;                              // adjusted width
    int adjHeigth = halfY - winHeigth / 2;                            // adjusted heigth
    int offY = (maxLines - WIDTH) / 2, offX = (maxCols - HEIGTH) / 2; // offset; useful to center box

    win = newwin(WIDTH, HEIGTH, offY, offX); // create a CENTERED box
    this->look[2][2] = (char)key + 48;

    // PLACING DOORS
    if (previousRoomExists) // checking where the previous door was in order to place it on the opposite side after
    {
        door tmpDoor = myDoor;
        // placing previous door; it has to be placed on the opposite side where it was in the previous room
        switch (tmpDoor.side)
        {
        case 0: // bottom side
            tmpDoor.y = 0;
            tmpDoor.side = 2;
            placeDoor(tmpDoor);
            break;
        case 1: // left side
            tmpDoor.x = HEIGTH - 1;
            tmpDoor.side = 3;
            placeDoor(tmpDoor);
            break;
        case 2: // top side
            tmpDoor.y = WIDTH - 1;
            tmpDoor.side = 0;
            placeDoor(tmpDoor);
            break;
        case 3: // right side
            tmpDoor.x = 0;
            tmpDoor.side = 1;
            placeDoor(tmpDoor);
            break;

        default:
            break;
        }
        tmpDoor.isNextRoom = 0;
        doorInfo[0] = tmpDoor;
    }

    // now we have to draw 1 to (4-1) doors (previous one is already placed)

    int prevDoorsNumber = 0;
    if (previousRoomExists)
        prevDoorsNumber = 1;

    // srand(4); // FIXME: seed casuale
    srand(time(0)); // seed is 0

    int i = 0;

    int side;
    bool isOccupied = true;

    while (isOccupied == true)
    {
        side = rand() % 4; // picking a casual side to place the door
        if (doorInfo[0].side == side)
            isOccupied = true;
        else
            isOccupied = false;
    }

    if (isOccupied == false) // if side is free, then place door
    {
        struct door myDoorTmp;
        myDoorTmp.side = side;
        myDoorTmp.isNextRoom = 1;
        switch (myDoorTmp.side) // match/adjust side to coords
        {
        case 0: // bottom side
            myDoorTmp.y = WIDTH - 1;
            myDoorTmp.x = HEIGTH / 2;
            placeDoor(myDoorTmp);
            break;
        case 1: // left side
            myDoorTmp.y = WIDTH / 2;
            myDoorTmp.x = 0;
            placeDoor(myDoorTmp);
            break;
        case 2: // top side
            myDoorTmp.y = 0;
            myDoorTmp.x = HEIGTH / 2;
            placeDoor(myDoorTmp);
            break;
        case 3: // right side
            myDoorTmp.y = WIDTH / 2;
            myDoorTmp.x = HEIGTH - 1;
            placeDoor(myDoorTmp);
            break;

        default:
            break;
        }

        doorInfo[1] = myDoorTmp;
    }

    // PLACING OBJECTS

    // place wall
    const int MAXWALLS = 15;
    for (int i = 0; i < MAXWALLS; i++) // number of walls
    {
        const int offsetSXDX = 6, offsetUPLOW = 6;
        int posY = (rand() % (WIDTH - (offsetUPLOW * 2))) + offsetUPLOW; // 6-23
        int posX = (rand() % (HEIGTH - (offsetSXDX * 2))) + offsetSXDX;  // 6-93
        const int MAXWALLHEIGTH = (((WIDTH - (offsetUPLOW)) - posY) / 1.5) + 1;
        const int MAXWALLWIDTH = (((HEIGTH - (offsetSXDX)) - posX) / 1.5) + 1;
        int h = (rand() % (MAXWALLHEIGTH)) + 1; // random number of walls
        int w = (rand() % (MAXWALLWIDTH)) + 1;  // random number of walls

        createWall(w, h, posY, posX);
    }

    // TODO: place player
    // TODO: place enemies

    // TODO:  place etc

    drawn = true;

    return drawn;
}

// true open doors, false close doors
void Room::openDoors(bool open)
{
    doorInfo[0].isOpen = open;
    doorInfo[1].isOpen = open;

    placeDoor(doorInfo[0]);
    placeDoor(doorInfo[1]);

    this->drawLook();
    refresh();
    wrefresh(this->getWindow());
}