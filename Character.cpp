#include "header/Character.hpp"

// constructor
Character::Character(char name[], int current_life, int max_life, int atk_damage)
{
    strcpy(this->name, name);
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
}

// ritorna la vita corrente
int Character::getLife()
{
    return current_life;
}

// prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
void Character::takeDamage(int damage_received)
{
    int curr_life = getLife();
    if ((curr_life - damage_received) >= 0)
    {
        this->current_life = (curr_life - damage_received);
    }
    else
    {
        this->current_life = 0;
    }
}

// ho già fatto io la funzione nella classe artefatto, (Artifact -> gainlife) -annalisa

void Character::increaseLife(int healing)
{
    int curr_life = getLife();
    if (curr_life + healing <= this->max_life)
    {
        this->current_life = (curr_life + healing); // su questa riga usate la mia funzione pls (Artifact -> gainlife)
    }
    else
    {
        this->current_life = this->max_life;
    }
}
//commento di prova