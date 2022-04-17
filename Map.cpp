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

// creates new room in the specified door
void Map::enterRoom(int prevRoomKey, door doorInfo)
{
    int key = newKey();

    switch (doorInfo.side)
    {
    case 0: // bottom side
        rooms->door0->currentRoom = Room(key);
        rooms->door0->door2Info = doorInfo; // if player enters room from bottom side; previous room is located top side
        rooms->door0->door2 = rooms;
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
