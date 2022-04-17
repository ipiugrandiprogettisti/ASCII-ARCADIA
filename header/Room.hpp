// Room class file

#include <ncurses.h>

// if any of the values is -1 then it is not been defined yet; meaning that door does not exist on map/room
struct door
{
    int y = -1, x = -1;  // position
    int side = -1;       /*- 0: bottom side
                        - 1: left side
                        - 2: top side
                        - 3: right side*/
    bool isOpen = false; // if door is closed; player can't cross it
};

// enemies list
struct listEnemies
{
    // current enemy
    // enemy key
    listEnemies *next;
    listEnemies *previous;
};

// pointer to list of the enemies
typedef listEnemies *pListEnemies;

// artifacts list
struct listArtifacts
{
    // current artifact
    // artifact key
    listArtifacts *next;
    listArtifacts *previous;
};

// pointer to list of the enemies
typedef listArtifacts *pListArtifacts;

// struct that contains all of the dynamic structures that are in the room
struct objContainer
{
    pListEnemies enemies;
    pListArtifacts artifacts;
};

// place a door. y and x are position, i is the side where the door is located
void placeDoor(WINDOW *win, door doorInfo);

// Room class
class Room
{
protected:
    int key; // unique
    WINDOW *win;
    objContainer objects;

public:
    // Constructort
    Room();

    // Constructor
    Room(int key);

    // returns the key of the room
    int getKey();

    // returns the WINDOW of the room
    WINDOW *getWindow();

    // returns the given door (struct door) information
    struct door getDoor(int side);

    // funzione bozza per disegnare una stanza; prima stanza
    void draw(int maxCols, int maxLines);

    // funzione bozza per disegnare una stanza; seconda + stanza
    void draw(int maxCols, int maxLines, struct door doorInfo);
};
