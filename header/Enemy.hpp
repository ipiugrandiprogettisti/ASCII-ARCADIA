#include "Character.hpp"
//#include "Map.hpp"
class Enemy : public Character{

    protected:

    int key;
    int bullets_dmg;
    int bullets_range;
    int range_move;  //di quanto si può spostare

    public:
    // constructor
    Enemy();

    // constructor
    Enemy(int key, int bullets_dmg, int bullets_range, int range_move, int current_life, int max_life, int atk_damage, int y, int x, chtype tag);


    //generate random position
    void random_position(int random_y, int random_x);

    //place enemy
    void place_enemy(Enemy e);


    void set_enemy(Enemy e, int k);

    
    bool enemy_alive();

    void death_enemy(Enemy e);

    bool unlock_door();


};