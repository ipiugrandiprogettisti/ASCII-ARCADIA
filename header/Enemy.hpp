#include "Character.hpp"
//#include "Map.hpp"

class Enemy : public Character
{

protected:
int key; //identifica il tipo di nemico


public:
    // constructor
    Enemy();

    // constructor
    Enemy(int key, int current_life, int max_life, int score, int y, int x, chtype tag);

    //sets enemy's score
    void set_score(int c);

    //return the enemy key
    int get_enemyKey();

    void set_enemyKey(int key);

};