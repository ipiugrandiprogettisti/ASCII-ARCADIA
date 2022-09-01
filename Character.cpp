#include "header/Character.hpp"

int current_life;
int max_life;
int atk_damage;

Character::Character()
{
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}
// constructor
Character::Character(int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Entity(y, x, tag)
{

    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = 111;
}

// returns current life
int Character::getLife()
{
    return this->current_life;
}

// updates life according to the damage received
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
