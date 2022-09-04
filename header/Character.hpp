#ifndef _CHARACTER
#define _CHARACTER
#include "Entity.hpp"


// struct bullet
typedef struct bullet
{
    chtype bullet_tag;
    int bullet_damage;
    pos bulletpos;
    int direction; // 0 indica che va verso il basso, 1 che va verso sinistra, 2 verso l'alto e 3 verso destra

} bullet;

// class character
class Character : public Entity
{
protected:
    int current_life; // in termini di cuori posseduti al momento
    int max_life;     // cuori  massimi=10
    int score;

public:

    // constructor
    Character();

    // constructor
    Character(int current_life, int max_life, int score, int y, int x, chtype tag);

    // ritorna la vita corrente
    int getLife();

    // prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
    bool takeDamage(int);
    //return the score
    int get_score();

    //set up the score
    void set_score(int c);

    //return max life
    int get_maxLife();
};

#endif