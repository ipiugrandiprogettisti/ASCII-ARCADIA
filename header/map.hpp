// Map class file

#include <ncurses.h>
#include "Room.hpp"

const int MAX_ROOMS = 100;

class Map
{
protected:
    WINDOW *mainWin; // main window (terminal)
    Room rooms[MAX_ROOMS];
    int currentRoom; // key of the current room
    int totalRooms;  // number of total rooms
public:
    // Constructor
    Map(WINDOW *win,int totalRooms);

    // returns the main window
    WINDOW *getMainWindow();

    // returns the room window
    WINDOW *getRoomWindow(int currentRoom);

};

