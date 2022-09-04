#include "header/Enemy.hpp"

// constructor
Enemy::Enemy()
{
    key = 0;
    score = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

// constructor
Enemy::Enemy(int key, int score, int y, int x, chtype tag) : Character(score, y, x, tag)
{

    this->key = key;
    this->score = score;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

void Enemy::set_score(int c)
{
    this->score = c;
}

int Enemy::get_enemyKey()
{
    return this->key;
}

void Enemy::set_enemyKey(int key)
{
    this->key = key;
}
