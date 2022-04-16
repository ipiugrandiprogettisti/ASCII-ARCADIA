
// Room class file

#include <ncurses.h>

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

    // funzione bozza per disegnare una stanza
    void draw(int maxCols, int maxLines);

    /*
    FIXME TO FIX! forse anche non fare
    // draws a box with custom corners, SX / RX are the north corners, sx / rx are the south corners.
    void customBox(WINDOW *win, int heigth, int width, chtype hLine, chtype vLine, chtype SXCorner, chtype RXCorner, chtype sxCorner, chtype rxCorner);
    */
};
