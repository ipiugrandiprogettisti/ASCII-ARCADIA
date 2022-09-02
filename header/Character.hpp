
#include "Entity.hpp"
#pragma once

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

public:
    int current_life; // in termini di cuori posseduti al momento
    int max_life;     // cuori  massimi=10
    int atk_damage;   // danno che produce in attacco
    // constructor
    Character();

    // constructor
    Character(int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // ritorna la vita corrente
    int getLife();

    // prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
    bool takeDamage(int);
};