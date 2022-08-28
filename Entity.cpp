#include "header/Entity.hpp"

// constructor
Entity::Entity()
{
    tag = 111;
    position.y = 0;
    position.x = 0;
}

// constructor
Entity::Entity(int x, int y, chtype tag)
{
    this->tag = tag;
    position.y = y;
    position.x = x;
}

// returns entity's current position
pos Entity::getPosition()
{
    return position;
}

// sets Entity's new position
void Entity::setPosition(int newy, int newx)
{
    this->position.y = newy;
    this->position.x = newx;
};