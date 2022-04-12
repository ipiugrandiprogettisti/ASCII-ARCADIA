#include "header/Entity.hpp"

// constructor
Entity::Entity()
{
    position.x = 0;
    position.y = 0;
}

//constructor
Entity::Entity(int x, int y)
{
    position.x = x;
    position.y = y;
}

//returns entity's current position
pos Entity::getPosition() {
    return position;
}