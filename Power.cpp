#include "header/Power.hpp"
Power ::Power()
{
};

Power ::Power(int y, int x, chtype tag) : Entity(position.y, position.x, tag)
{
    this->position.y = y;
    this->position.x = x;
    this->tag = 'P';
};
