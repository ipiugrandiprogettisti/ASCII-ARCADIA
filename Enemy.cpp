#include "header/Enemy.hpp"

//constructor
Enemy::Enemy()
{
    key = 0;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

//constructor
Enemy::Enemy(int key, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, y, x, tag)
{
    this->key = key;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}


// control when the enemy are alive
//door open when enemy are deaths

//window da 0 29  altezza , 0 100 larghezza

// casella vuota ' '

//sets random coordintes
void random_position(int random_y, int random_x){

    srand(time(NULL));
    random_y = rand()%30;
    random_x = rand()%100;
       
};
