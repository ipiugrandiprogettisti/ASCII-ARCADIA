// Room class file

#include <ncurses.h>

struct door
{
    int y, x; // position
    int side; /*- 0: bottom side
                - 1: left side
                - 2: top side
                - 3: right side*/
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

    // funzione bozza per disegnare una stanza
    void draw(int maxCols, int maxLines);
};
