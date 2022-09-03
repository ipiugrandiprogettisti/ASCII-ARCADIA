#include "header/Enemy.hpp"

//constructor
Enemy::Enemy()
{
    score = 0;
    key = 0;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

//constructor
Enemy::Enemy(int score, int key, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, score, y, x, tag)
{
    this->score = score;
    this->key = key;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

