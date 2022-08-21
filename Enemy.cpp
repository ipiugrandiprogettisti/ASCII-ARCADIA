#include "header/Enemy.hpp"

//constructor
Enemy::Enemy()
{
    range_move = 0;
    bullets_dmg = 0;
    key = 0;
    bullets_range = 0;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

//constructor
Enemy::Enemy(int key, int bullets_dmg, int bullets_range, int range_move, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, y, x, tag)
{
    this->bullets_dmg = bullets_dmg;
    this->key = key;
    this->bullets_range = bullets_range;
    this->range_move = range_move;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

/*
void Enemy::printEnemy(Enemy en, WINDOW *w)
{
    int enemy_y = en.position.y;
    int enemy_x = en.position.x;

    mvwaddch(w, enemy_y, enemy_x, en.tag);
}
*/

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
/*
void place_enemy(Enemy e){
    bool flag =true;
    pos position;
    int y, x;

    while(flag = true){

        random_position(y, x);
        position.y= y;
        position.x= x;
        if(myMap.rooms->currentRoom.getTile(position) == ' '){
            myMap.rooms->currentRoom.placeObject(position, e.tag);
            flag = false;
        }           
}
};
*/

/*
void death_enemy(Enemy e){

    int hp = Character::getLife(e);
    if(hp <= 0){
        myMap.rooms->currentRoom.placeObject(e.position, ' ');    
    }

};
*/