#ifndef _CHARACTER
#define _CHARACTER
#include "Entity.hpp"


// struct bullet
typedef struct bullet
{
    chtype bullet_tag;
    int bullet_damage;
    pos bulletpos;
    int direction; // 0 indica che va verso il basso, 1 che va verso sinistra, 2 verso l'alto e 3 verso destra

} bullet;

// class character
class Character : public Entity
{
protected:
    int score;

public:

    // constructor
    Character();

    // constructor
    Character(int score, int y, int x, chtype tag);

    
    //returns the score
    int get_score();

    

};

#endif