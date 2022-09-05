#include "header/Artifact.hpp"

int rarity;
int lifepoints; // amount of lifepoints given

// constructor
Artifact ::Artifact()
{

    rarity = 0;
    lifepoints = 0;
    tag = 111;
    position.y = 0;
    position.x = 0;
}

// constructor
Artifact ::Artifact(int rarity, int lifepoints, int posy, int posx, chtype tag) : Entity(position.y, position.x, tag)
{
    this->lifepoints = lifepoints;
    this->rarity = rarity;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = ' ';
}


// returns lifepoints
int Artifact ::getLifepoints()
{
    return this->lifepoints;
}
int Artifact::getRarity(){
    return this->rarity;
}

void Artifact::setLifepoints(int life){
    this->lifepoints=life;
}


    void Artifact::setRarity(int rar){
        this->rarity=rar;
    }

