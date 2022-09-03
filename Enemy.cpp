#include "header/Enemy.hpp"

// constructor
Enemy::Enemy()
{
    key = 0;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    score = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

// constructor
Enemy::Enemy(int key, int current_life, int max_life, int atk_damage, int score, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, score, y, x, tag)
{

    this->key = key;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->score = score;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

void Enemy::set_score(int c)
{
    this->score = c;
}
