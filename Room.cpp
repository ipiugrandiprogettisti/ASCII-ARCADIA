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

// place object in room
void Room::placeObject(pos position, chtype tag)
{
    this->look[position.y][position.x] = tag;
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
            placeObject(position, ACS_CKBOARD);
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

// sets up the room if myDoor doesnt exist (-1), then it is the first room being set up
bool Room::setUp(int maxCols, int maxLines, struct door myDoor)
{
    // if room was already drew there is no need to redraw, so function ends
    if (drawn)
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
    int previousDoorSide = -1;
    if (previousRoomExists)
    {
        // placing previous door; it has to be placed on the opposite side where it was in the previous room
        switch (myDoor.side)
        {
        case 0: // bottom side
            myDoor.y = 0;
            placeDoor(myDoor);
            previousDoorSide = 2;
            break;
        case 1: // left side
            myDoor.x = HEIGTH - 1;
            placeDoor(myDoor);
            previousDoorSide = 3;
            break;
        case 2: // top side
            myDoor.y = WIDTH - 1;
            placeDoor(myDoor);
            previousDoorSide = 0;
            break;
        case 3: // right side
            myDoor.x = 0;
            placeDoor(myDoor);
            previousDoorSide = 1;
            break;

        default:
            break;
        }

        doorInfo[previousDoorSide] = myDoor;
    }

    // now we have to draw 1 to (4-1) doors (previous one is already placed)
    // srand(time(0));                           // seed is 0
    int prevDoorsNumber = 0;
    if (previousRoomExists)
        prevDoorsNumber = 1;

    srand(seed);                                            // FIXME: seed casuale
    int nDoors = (rand() % MAXDOORS - prevDoorsNumber) + 1; // random number of door from 1 to 4-1 because we already have the previous one

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

        if (isOccupied == false) // if side is free, then place door
        {
            struct door myDoorTmp;
            myDoorTmp.side = side;
            switch (myDoorTmp.side) // match/adjust side to coords
            {
            case 0: // bottom side
                myDoorTmp.y = WIDTH - 1;
                myDoorTmp.x = HEIGTH / 2;
                placeDoor(myDoorTmp);
                setDoor(0, myDoorTmp);
                break;
            case 1: // left side
                myDoorTmp.y = WIDTH / 2;
                myDoorTmp.x = 0;
                placeDoor(myDoorTmp);
                setDoor(1, myDoorTmp);
                break;
            case 2: // top side
                myDoorTmp.y = 0;
                myDoorTmp.x = HEIGTH / 2;
                placeDoor(myDoorTmp);
                setDoor(2, myDoorTmp);
                break;
            case 3: // right side
                myDoorTmp.y = WIDTH / 2;
                myDoorTmp.x = HEIGTH - 1;
                placeDoor(myDoorTmp);
                setDoor(3, myDoorTmp);
                break;

            default:
                break;
            }
        }
        i++;
    }

    // PLACING OBJECTS
    // place wall
    const int MAXWALLS = 5;
    for (int i = 0; i < MAXWALLS; i++) // number of walls
    {
        int posY = (rand() % (WIDTH - 5));   // y offset max=WIDTH-5
        int posX = (rand() % (HEIGTH - 5));  // x offset max=HEIGTH-5
        int h = (rand() % (WIDTH - 25));   // random number of walls from 1 to 5
        int w = (rand() % (HEIGTH - 70)); // random number of walls from 1 to 50
        // int posY = 20, posX = 10, h = 5, w = 50;
        createWall(w, h, posY, posX);
    }

    // place player

    // place enemies
    // place etc

    drawn = true;
    return true;
}
