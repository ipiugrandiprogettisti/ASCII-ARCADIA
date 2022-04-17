#include "header/Map.hpp"
#include "header/utils.hpp"
#include "header/MyString.hpp"

/*
Map::Map()
{
}*/

// Constructor
Map::Map(WINDOW *win)
{
    mainWin = win;
    totalRooms = 1; // game starts with only 1 room. next rooms are one at a time
    this->freeKey = 0;

    rooms = new listRooms;
    rooms->currentRoom = Room(newKey());

    // sets all next rooms to nullptr; a pointer will be assigned to its room when one is created
    // FIXME: nella funzione tailInsert di listRooms ho usato NULL per le stanze vuote non nullptr
    rooms->door0 = nullptr;
    rooms->door1 = nullptr;
    rooms->door2 = nullptr;
    rooms->door3 = nullptr;

    // doorInfo are already set when defined check Room.hpp for more info
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
    // TODO
    // search in rooms for current room; then returns the room's window
    return rooms->currentRoom.getWindow();
}

// head insert
pListRooms insertHead(pListRooms rooms, int doorNumber, Room roomInfo, struct door previousDoorInfo)
{
    pListRooms list = new listRooms;
    switch (doorNumber)
    {
    case 0:
        list->currentRoom = roomInfo;
        list->door2Info = previousDoorInfo; // if player enters room from bottom side; previous room is located top side
        list->door2 = rooms;                // if player enters room from bottom side; previous room is located top side
        break;
    case 1:
        // copia list->currentRoom=room ecc
        list->door1 = rooms;
        break;
    case 2:
        // copia list->currentRoom=room ecc
        list->door2 = rooms;
        break;
    case 3:
        // copia list->currentRoom=room ecc
        list->door3 = rooms;
        break;

    default:
        break;
    }

    return list;
}

// tail insert
pListRooms tailInsert(pListRooms rooms, int doorNumber, int newRoomKey)
{
    pListRooms list;
    if (rooms == NULL)
    {
        rooms = new listRooms;
        rooms->currentRoom = Room(newRoomKey);
        rooms->door0 = NULL;
        rooms->door1 = NULL;
        rooms->door2 = NULL;
        rooms->door3 = NULL;
    }
    else
    {
        for (list = rooms; list->door0 != NULL; list = list->door0)
        {
        }
        list = new listRooms;
        list->currentRoom = Room(newRoomKey);
        list->door0 = NULL;
        list->door1 = NULL;
        list->door2 = NULL;
        list->door3 = NULL;
    }
    return rooms;
}

// creates new room in the specified door
void Map::enterRoom(int prevRoomKey, door doorInfo)
{
    int key = newKey();

    switch (doorInfo.side)
    {
    case 0: // bottom side
        /*
        rooms->door0->currentRoom = Room(key);
        rooms->door0->door2Info = doorInfo; // if player enters room from bottom side; previous room is located top side
        rooms->door0->door2 = rooms;
        */
        rooms = insertHead(rooms, doorInfo.side, Room(key), rooms->currentRoom.getDoor(doorInfo.side));
        break;
    case 1: // left side
        break;
    case 2: // top side
        break;
    case 3: // right side
        break;
    default:
        break;
    }
}
