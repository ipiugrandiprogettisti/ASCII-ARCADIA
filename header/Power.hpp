#include "Entity.hpp"

// classe potere 1-> sblocca passaggi
// potere 1 -> apre porta                       chtype 230 : æ
// potere 2 -> aumenta num proiettili di uno    chtype 187 : »

#define DOORUNLOCK 1
#define BOOSTBULLET 2
class Power : public Entity
{
public:
    int type;

public:
    Power();
    // power constructor with type, pos y, posx, tag (set it 111 by default)
    // after creating a power you need to set his tag with funct setPower()
    Power(int type, int y, int x, chtype tag);

    void setPower(Power p);
    int getType(Power p);

    void printPower(Power p, WINDOW *w);
};