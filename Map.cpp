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
    rooms->door1 = nullptr;
    rooms->door2 = nullptr;
    rooms->door3 = nullptr;
    rooms->previousRoom = nullptr; // this is nullptr because there is no previous room in the first one
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
    rooms->door1->currentRoom = Room(key);
}
