#include "Entity.hpp"

// classe potere -> sblocca passaggi
// potere 1 -> apre porta
// potere 2 -> aumenta i proiettili di uno
class Power : public Entity
{
protected:
    int type;

public:
    Power();

    Power(int type, int y, int x, chtype tag);

    int getType(Power p);

    void printPower(Power p, WINDOW *w);
};