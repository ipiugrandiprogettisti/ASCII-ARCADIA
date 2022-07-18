#include "Entity.hpp"

// classe potere 1-> sblocca passaggi
// potere 1 -> apre porta                       chtype 230 : æ
// potere 2 -> aumenta num proiettili di uno    chtype 187 : »
class Power : public Entity
{
protected:
    int type;

public:
    Power();

    Power(int type, int y, int x, chtype tag);

    void setPower(Power p);
    int getType(Power p);

    void printPower(Power p, WINDOW *w);
};