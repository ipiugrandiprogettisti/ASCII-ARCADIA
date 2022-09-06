#include "header/Map.hpp"
#include "header/utils.hpp"

// Constructor
Map::Map(WINDOW *win)
{
    mainWin = win;
    this->freeKey = 0;

    rooms = new listRooms;
    rooms->currentRoom = Room(newKey());

    // sets next room to NULL (it has to be created)
    rooms->nextRoom = NULL;
    // sets previous room to NULL
    rooms->previousRoom = NULL;
}

// returns and create a new unique key
int Map::newKey()
{
    freeKey += 1;
    return freeKey - 1;
}

// returns the main window
WINDOW *Map::getMainWindow()
{
    return mainWin;
}

// returns the room window
WINDOW *Map::getRoomWindow(int key)
{
    return rooms->currentRoom.getWindow();
}


// tail insert
pListRooms insertTail(pListRooms myListRoom, Room roomInfo, door previousDoor)
{
    previousDoor.isOpen = false;

    pListRooms newListRooms;
    pListRooms tmpOriginalList = myListRoom;

    if (myListRoom == NULL)
    {
        myListRoom = new listRooms;
        myListRoom->currentRoom = roomInfo;
        myListRoom->nextRoom = NULL;
        myListRoom->previousRoom = tmpOriginalList;
        myListRoom->currentRoom.setUp(COLS, LINES, previousDoor);
    }
    else
    {

        for (newListRooms = myListRoom; newListRooms->nextRoom != NULL; newListRooms = newListRooms->nextRoom)
        {
        }

        newListRooms->nextRoom = new listRooms;
        newListRooms->nextRoom->currentRoom = roomInfo;
        newListRooms->nextRoom->nextRoom = NULL;
        newListRooms->nextRoom->previousRoom = tmpOriginalList;
        newListRooms->nextRoom->currentRoom.setUp(COLS, LINES, previousDoor);

        myListRoom = newListRooms;
    }

    return myListRoom;
}

// go to next node
pListRooms goNextRoom(pListRooms myListRooms, WINDOW *win)
{
    if (myListRooms->nextRoom != NULL)
    {
        myListRooms = myListRooms->nextRoom;
    }

    return myListRooms;
}

// go to previous node
pListRooms goPreviousRoom(pListRooms myListRooms)
{
    
    pListRooms tmpList = myListRooms;

    if (myListRooms->previousRoom != NULL)
    {
        tmpList = tmpList->previousRoom;
    }
    myListRooms = tmpList;

    return myListRooms;
}

// changes room, 1 = next room, 0 = previous room. returns true if succeeds
bool Map::changeRoom(int isNextRoom)
{
    bool success = false;

    switch (isNextRoom)
    {
    case 0: // PREVIOUS ROOM
        rooms = goPreviousRoom(rooms);
        success = true;
        break;
    case 1: // NEXT ROOM
        rooms = goNextRoom(rooms, rooms->currentRoom.getWindow());
        success = true;
        break;

    default:
        break;
    }

    return success;
}

// Creates next room. If already exists next room returns false
bool Map::createRoom(door previousDoor)
{
    bool success = false;

    if (rooms->nextRoom == NULL)
    {
        int key = newKey();

        rooms = insertTail(rooms, Room(key), previousDoor);

        success = true;
    }

    return success;
}