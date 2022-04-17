
// Map class file
#include <ncurses.h>
#include "Room.hpp"

// list of the rooms
struct listRooms
{
    Room currentRoom;
    listRooms *door0, *door1, *door2, *door3;
    struct door door0Info, door1Info, door2Info, door3Info;
};

// pointer to list of the rooms
typedef listRooms *pListRooms;

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

    // creates new room in the specified door
    void enterRoom(int prevRoomKey, door doorInfo);
};
