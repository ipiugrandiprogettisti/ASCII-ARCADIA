#ifndef _ENTITY
#define _ENTITY
#include <iostream>
#include <ncurses.h>
typedef struct pos
{
    int y;
    int x;
} pos;

class Entity
{
public:
    pos position;
    chtype tag; // entity's character's type
    
    // constructor
    Entity();

    // constructor
    Entity(int y, int x, chtype tag);

    // returns entity's current position
    pos getPosition();

    // sets new entity's position (if it moves)
    void setPosition(int newy, int newx);
};


#endif