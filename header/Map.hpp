
// Map class file
#include <ncurses.h>
#include "Room.hpp"

// list of the rooms
struct listRooms
{
    Room currentRoom;
    listRooms *door[MAXDOORS]; // door pointer. e.g.: door[0] is the bottom side door
};

// pointer to list of the rooms
typedef listRooms *pListRooms;

// listRooms functions
// head insert
pListRooms insertHead(pListRooms, int val);

// tail insert
pListRooms insertTail(pListRooms rooms, int doorNumber, int newRoomKey);

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

    // returns win of the given room
    WINDOW *getRoomWindow(int key);

    // creates new room
    void createRoom(struct door doorInfo);

    // enters new room: makes it currentRoom. return true if succeed
    bool enterRoom(int key);

    // Create the rooms for the n doors that are on the screen
    void createRooms(int side, pListRooms previousRoom);

    int getKeyByDoor(int side);
};
