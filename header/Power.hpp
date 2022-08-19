#include "Entity.hpp"

// classe potere 1-> sblocca passaggi
// potere-> apre porta

class Power : public Entity
{
public:
    int type;

public:
    Power();
    // power constructor with type, pos y, posx, tag (set it 111 by default)
    // after creating a power you need to set his tag with funct setPower()
    Power(int y, int x, chtype tag);

    void printPower(Power p, WINDOW *w);
};