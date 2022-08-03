#include <iostream>
#include <cstring>
#include "Entity.hpp"

#define L 30
class Character : public Entity
{
public:
    char name[L];
    int current_life;
    int max_life;
    int atk_damage; // danno che produce in attacco

public:
    // constructor
    Character();

    // constructor
    Character(char name[], int current_life, int max_life, int atk_damage);

    // ritorna la vita corrente
    int getLife();

    // prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
    void takeDamage(int);

    // aumenta la vita in base agli artefatti
    // ho già fatto io la funzione nella classe artefatto, (Artifact -> gainlife) -annalisa
    void increaseLife(int);
};