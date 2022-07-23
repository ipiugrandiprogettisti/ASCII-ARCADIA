#include "header/Map.hpp"
#include "header/utils.hpp"

/*
Map::Map()
{
}*/

// Constructor
Map::Map(WINDOW *win)
{
    mainWin = win;
    // totalRooms = 1; // game starts with only 1 room
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
    // TODO
    // search in rooms for current room; then returns the room's window
    return rooms->currentRoom.getWindow();
}

// head insert
pListRooms insertHead(pListRooms myListRoom, Room roomInfo)
{
    /*pListRooms list = new listRooms;
    switch (previousDoorInfo.side)
    {
    case 0:
        list->currentRoom = roomInfo;
        list->currentRoom.setDoor(2, previousDoorInfo); // if player enters room from bottom side; previous room is located top side
        list->door[2] = rooms;                          // if player enters room from bottom side; previous room is located top side
        break;
    case 1:
        // copia list->currentRoom=room ecc
        // list->door1 = rooms;
        break;
    case 2:
        // copia list->currentRoom=room ecc
        // list->door2 = rooms;
        break;
    case 3:
        // copia list->currentRoom=room ecc
        // list->door3 = rooms;
        break;

    default:
        return NULL;
        break;
    }

    return list;*/

    pListRooms newListRooms = new listRooms;
    newListRooms->currentRoom = roomInfo;
    newListRooms->nextRoom = myListRoom;

    return newListRooms;
}

// tail insert
pListRooms insertTail(pListRooms myListRoom, Room roomInfo)
{
    /*pListRooms list;
    if (rooms == NULL)
    {
        rooms = new listRooms;
        rooms->currentRoom = Room(newRoomKey);
        for (int i = 0; i < MAXDOORS; i++)
            rooms->door[i] = NULL;
    }
    else
    {
        for (list = rooms; list->door[0] != NULL; list = list->door[0])
        {
        }
        list = new listRooms;
        list->currentRoom = Room(newRoomKey);
        for (int i = 0; i < MAXDOORS; i++)
            rooms->door[i] = NULL;
    }
    return rooms;*/

    pListRooms newListRooms;
    pListRooms tmpOriginalList = myListRoom;

    if (myListRoom == NULL)
    {
        myListRoom = new listRooms;
        myListRoom->currentRoom = roomInfo;
        myListRoom->nextRoom = NULL;
    }
    else
    {
        for (myListRoom = newListRooms; myListRoom->nextRoom != NULL; myListRoom = myListRoom->nextRoom)
        {
        }
        myListRoom->nextRoom = new listRooms;
        myListRoom->nextRoom->currentRoom = roomInfo;
        myListRoom->nextRoom->nextRoom = NULL;
        myListRoom->previousRoom = tmpOriginalList;
    }

    return myListRoom;
}

// funzione che va avanti di un nodo
pListRooms goNextRoom(pListRooms myListRooms, WINDOW *win)
{
    if (myListRooms->nextRoom != NULL)
    {
        myListRooms = myListRooms->nextRoom;
    }
    /*else
    {
        // cout << "Sei arrivato alla fine della lista";
        //???myListRooms = NULL;????
    }*/

    return myListRooms;
}

// funzione che va indietro di un nodo
pListRooms goPreviousRoom(pListRooms myListRooms)
{
    /* pListRooms tmpList;

     if (previousListRooms != myListRooms)
     {
         for (tmpList = previousListRooms; tmpList->nextRoom != myListRooms; tmpList = tmpList->nextRoom)
         {
         }
     }
     else
     {
         // cout << "Non esiste precedente alla testa";
         tmpList = NULL;
     }

     return tmpList;*/

    /*bool found = false;
    int i = 0;

    pListRooms tmpList = originalList;

    while (myListRooms != NULL && !found)
    {
        if (myListRooms->nextRoom == originalList->nextRoom)
            found = true;
        else
            tmpList = tmpList->nextRoom;
        i++;
    }

    if (found)
        return tmpList;
    else
        return myListRooms;*/

    if (myListRooms->previousRoom != NULL)
    {
        myListRooms = myListRooms->previousRoom;
    }
    /*else
    {
        // cout << "Sei in cima alla lista";
    }*/

    return myListRooms;
}

// changes room, 1 = next room, 0 = previous room
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
        mvaddstr(0, 57, "aasdasdasdasda");
        refresh();
        wrefresh(rooms->currentRoom.getWindow());
        rooms = goNextRoom(rooms, rooms->currentRoom.getWindow());
        success = true;
        break;

    default:
        break;
    }

    return success;
}

/*
// search and return specific room. returns NULL if not found
pListRooms getRoomByKey(pListRooms rooms, int key)
{
    if (rooms == NULL)
        return rooms;
    else if (rooms->door[0]->currentRoom.getKey() == key)
    {
        return rooms->door[0];
    }
    else
    {
        pListRooms tmp = rooms;
        pListRooms tmpAfter = rooms->door[0];
        bool found = false;
        while (!found && tmpAfter != NULL)
        {
            if (tmpAfter->currentRoom.getKey() == key)
            {
                tmp->door[0] = tmpAfter->door[0];
                found = true;
            }
            else
            {
                tmp = tmpAfter;
                tmpAfter = tmpAfter->door[0];
            }
        }
    }
    return rooms;
}
*/

// Create next room. If already exists next room returns false
bool Map::createRoom(door previousDoor)
{
    bool success = false;

    if (rooms->nextRoom != NULL)
    {
        int key = newKey();

        // rooms->door0->currentRoom = Room(key);
        // rooms->door0->door2Info = doorInfo; // if player enters room from bottom side; previous room is located top side
        // rooms->door0->door2 = rooms;

        rooms = insertTail(rooms, Room(key));
        rooms->nextRoom->currentRoom.setUp(COLS, LINES, previousDoor);

        success = true;
    }

    return success;
}

// enters new room. return true if succeeds. isNextRoom = 0 previous room, = 1 next room
bool Map::enterRoom(int isNextRoom)
{
    // rooms = getRoomByKey(rooms, key);

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

/*
// Create the rooms for the  doors that are on the screen
void Map::createRooms(int side, pListRooms previousRoom)
{
    int previousDoorSide = -1;
    switch (side)
    {
    case 0: // bottom side
        previousDoorSide = 2;
        break;
    case 1: // left side
        previousDoorSide = 3;
        break;
    case 2: // top side
        previousDoorSide = 0;
        break;
    case 3: // right side
        previousDoorSide = 1;
        break;
    default:
        previousDoorSide = -1;
        break;
    }

    MyString debug;
    for (int i = 0; i < 4; i++)
    {
        if (i == previousDoorSide)
        {
            // std::cout << "Stanza precedente" << std::endl;
            rooms->door[i] = previousRoom;
        }
        else
        {
            rooms->door[i] = new listRooms;
            door myDoor = rooms->currentRoom.getDoor(i);
            if (myDoor.x >= 0 && myDoor.y >= 0) // if door exists creates room
            {
                rooms->door[i]->currentRoom = Room(newKey());
                debug += "door[";
                debug += itoa(i);
                debug += "]";
                debug += " -> ";
                debug += itoa(rooms->door[i]->currentRoom.getKey());
                debug += ", ";
                for (int j = 0; j < MAXDOORS; j++) // sets to NULL the doors of the new room
                {
                    rooms->door[i]->door[j] = NULL;
                }
            }
            else
                rooms->door[i] = NULL;
        }
    }


    mvaddstr(3, 70, debug.get());
}
*/

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