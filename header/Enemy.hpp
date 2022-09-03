#include "Character.hpp"
//#include "Map.hpp"

class Enemy : public Character
{


public:
    int key;
    // constructor
    Enemy();

    // constructor
    Enemy(int key, int current_life, int max_life, int atk_damage, int score, int y, int x, chtype tag);


};