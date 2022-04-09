#include <ncurses.h>

class Map
{
protected:
    WINDOW *myWin;

public:
    //Constructor
    Map(WINDOW *myWin);

    //funzione bozza per creare una stanza
   void drawRoom();
};