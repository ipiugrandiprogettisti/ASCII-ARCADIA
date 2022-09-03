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

// enters new room. returns true if succeeds. isNextRoom = 0 previous room, = 1 next room
bool Map::enterRoom(int isNextRoom)
{
    bool entered = false;
    switch (isNextRoom)
    {
    case 0:                              // PREVIOUS ROOM
        if (rooms->previousRoom != NULL) // check if previous room exists
        {
            pListRooms previousRoomList = rooms;
            rooms = rooms->previousRoom;        // enter next room
            rooms->nextRoom = previousRoomList; // set previous room as the one the player entered
            entered = true;
        }
        break;
    case 1:                          // NEXT ROOM
        if (rooms->nextRoom != NULL) // check if next room exists
        {
            pListRooms previousRoomList = rooms;
            rooms = rooms->nextRoom;                // enter next room
                                                    // rooms = goNextRoom(rooms);
            rooms->previousRoom = previousRoomList; // set previous room as the one the player entered
            rooms->currentRoom.setUp(COLS, LINES, previousRoomList->currentRoom.getDoor(1));
            if (rooms->currentRoom.setUp(COLS, LINES, previousRoomList->currentRoom.getDoor(1)))
            {
                mvaddstr(0, 56, "stanza non setuppata2");
                refresh();
                wrefresh(rooms->currentRoom.getWindow());
            }
            entered = true;
        }
        break;

    default:
        break;
    }

    return entered;
}
// returns the given door room's key. -1 if not found. parameter room: 0 = previous room; 1 = next room
int Map::getKeyByDoor(int room)
{
    int key = -1;
    switch (room)
    {
    case 0: // previous room
        if (this->rooms->previousRoom != NULL)
            key = this->rooms->previousRoom->currentRoom.getKey();
        break;
    case 1: // previous room
        if (this->rooms->nextRoom != NULL)
            key = this->rooms->nextRoom->currentRoom.getKey();
        break;
    default:
        break;
    }

    return key;
}