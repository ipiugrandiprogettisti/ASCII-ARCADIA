#include "header/Character.hpp"

int current_life;
int max_life;
int atk_damage;
int score;

Character::Character()
{
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    score = 0;
    position.y = 0;
    position.x = 0;
    tag = ' ';
}
// constructor
Character::Character(int current_life, int max_life, int atk_damage, int score, int y, int x, chtype tag) : Entity(y, x, tag)
{

    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->score = score;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

// returns current life
int Character::getLife()
{
    return this->current_life;
}

// updates life according to the damage received
bool Character::takeDamage(int damage_received)
{
    bool dead = false;
    int curr_life = Character::getLife();
    if ((curr_life - damage_received) > 0)
    {
        this->current_life = (curr_life - damage_received);
    }
    else
    {
        this->current_life = 0;
        dead = true;
    }
    return dead;
}

int Character::get_score()
{
    return this->score;
}


