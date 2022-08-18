
#include "Entity.hpp"

// struttura proiettile
typedef struct bullet
{
    chtype bullet_tag = ACS_BULLET;
    int bullet_damage;
    pos bulletpos;
    int direction;   //0 indica che va verso il basso, 1 che va verso sinistra, 2 verso l'alto e 3 verso destra

} bullet;

// classe personaggio generale
class Character : public Entity
{
protected:
    int current_life; // in termini di cuori posseduti al momento
    int max_life;     // cuori  massimi=10
    int atk_damage;   // danno che produce in attacco

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