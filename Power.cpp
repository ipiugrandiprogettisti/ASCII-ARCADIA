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

void Power::setPower(Power p)
{
    switch (p.type)
    {
    case 1:
        p.tag = 230;
    case 2:
        p.tag = 187;
    }
}
int Power::getType(Power p)
{
    return p.type;
};

void Power ::printPower(Power p, WINDOW *w)
{
    int py = p.position.y;
    int px = p.position.x;
    mvwaddch(w, py, px, p.tag);
};