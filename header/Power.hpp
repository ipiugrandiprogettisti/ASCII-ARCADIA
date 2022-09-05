#include "Entity.hpp"

// classe potere->apre porte/passaggi
//non ha bisogno di ulteriori attributi rispetto a entity, creata classe per il costruttore
// character corrispondente 'P
class Power : public Entity
{
public:
//null constructor
    Power();
    //power constructor
    Power(int y, int x, chtype tag);
    
};