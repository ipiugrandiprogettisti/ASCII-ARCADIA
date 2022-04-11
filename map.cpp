#include "header/map.hpp"
#include "header/utils.hpp"
#include "header/MyString.hpp"

/*
Map::Map()
{
}*/

Map::Map(WINDOW *win, int totalRooms)
{
    mainWin = win;
    this->totalRooms = totalRooms;
    currentRoom = 0; // starting room is the first one: rooms[0]
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
    return rooms[key].getWindow();
}
