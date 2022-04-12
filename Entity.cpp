#include "header/Entity.hpp"

// constructor
Entity::Entity()
{
    tag = 111;
    position.x = 0;
    position.y = 0;
}

// constructor
Entity::Entity(int x, int y, chtype tag)
{
    this->tag = tag;
    position.x = x;
    position.y = y;
}

// returns entity's current position
pos Entity::getPosition()
{
    return position;
}