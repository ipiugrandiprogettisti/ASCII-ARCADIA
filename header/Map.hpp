#pragma once
// Map class file
#include <ncurses.h>
#include "Room.hpp"

// list of the rooms
struct listRooms
{
    Room currentRoom;
    listRooms *door1, *door2, *door3;
    listRooms *previousRoom;
};

// pointer to list of the rooms
typedef listRooms *pListRooms;

const int MAX_ROOMS = 100;

class Map
{
private:
    int freeKey; // this is the next free key. each room has a unique key

protected:
    WINDOW *mainWin; // main window (terminal)
    int totalRooms;  // number of total rooms

public:
    pListRooms rooms; // list of rooms

    // Constructor
    Map(WINDOW *win);

    // returns a new unique key
    int newKey();

    // returns the main window
    WINDOW *getMainWindow();

    // returns the room window
    WINDOW *getRoomWindow(int currentRoom);
};
