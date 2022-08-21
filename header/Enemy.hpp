#include "Character.hpp"
//#include "Map.hpp"

class Enemy : public Character
{


public:
    int key;
    // constructor
    Enemy();

    // constructor
    Enemy(int key, int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // generate random position
    void random_position(int random_y, int random_x);

};