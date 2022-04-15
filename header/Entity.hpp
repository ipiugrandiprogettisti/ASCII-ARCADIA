#pragma once
#include <ncurses.h>
typedef struct pos
{
    int y;
    int x;
} pos;

class Entity
{
protected:
    pos position;
    chtype tag; // entity's character's type

public:
    // constructor
    Entity();

    // constructor
    Entity(int y, int x, chtype tag);

    // returns entity's current position
    pos getPosition();

    // sets new entity's position (if it moves)
    void setPosition(int newy, int newx);
};