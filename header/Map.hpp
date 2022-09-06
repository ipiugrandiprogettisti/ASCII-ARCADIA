
// Map class file
#include <ncurses.h>
#include "Room.hpp"

// list of the rooms
struct listRooms
{
    Room currentRoom;
    listRooms *nextRoom;     // next room pointer
    listRooms *previousRoom; // previous room pointer
};

// pointer to list of the rooms
typedef listRooms *pListRooms;

// listRooms functions
// tail insert
pListRooms insertTail(pListRooms myListRoom, Room roomInfo, door previousDoor);

class Map
{
private:
    int freeKey; // this is the next free key. each room has a unique key

protected:
    WINDOW *mainWin; // main window (terminal)

public:
    pListRooms rooms; // list of rooms

    // Constructor
    Map(WINDOW *win);

    // returns a new unique key
    int newKey();

    // returns the main window
    WINDOW *getMainWindow();

    // returns win of the given room
    WINDOW *getRoomWindow(int key);

    // Creates next room. If already exists next room returns false
    bool createRoom(door previousDoor);

    // changes room, 1 = next room, 0 = previous room. returns true if succeeds
    bool changeRoom(int isNextRoom);
};