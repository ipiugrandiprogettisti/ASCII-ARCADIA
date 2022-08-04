
#include "Entity.hpp"

// classe personaggio generale
class Character : public Entity
{
protected:
    int current_life;
    int max_life;
    int atk_damage; // danno che produce in attacco

public:
    // constructor
    Character();

    // constructor
    Character(int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // ritorna la vita corrente
    int getLife();

    // prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
    void takeDamage(int);
};