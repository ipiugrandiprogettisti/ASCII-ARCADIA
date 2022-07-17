#include "header/Power.hpp"
int type;
Power ::Power()
{
    type = 0;
};

Power ::Power(int type, int y, int x, chtype tag) : Entity(position.y, position.x, tag)
{
    this->type = type;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
};