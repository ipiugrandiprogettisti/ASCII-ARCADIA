#include "header/Character.hpp"

// constructor
Character::Character()
{
    score = 0;
    position.y = 0;
    position.x = 0;
    tag = ' ';
}

// constructor
Character::Character(int score, int y, int x, chtype tag) : Entity(y, x, tag)
{
    this->score = score;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}


//returns the score
int Character::get_score()
{
    return this->score;
}



