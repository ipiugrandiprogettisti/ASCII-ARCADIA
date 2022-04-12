#include <ncurses.h>
typedef struct pos
{
    int x;
    int y;
} pos;

class Entity
{
protected:
    pos position;
    chtype tag; //entity's character's type

public:
    // constructor
    Entity();

    // constructor
    Entity(int x, int y, chtype tag);

    // returns entity's current position
    pos getPosition();
};