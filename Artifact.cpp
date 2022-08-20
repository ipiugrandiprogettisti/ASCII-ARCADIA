#include "header/Artifact.hpp"

int key; // identifier
int rarity;
int lifepoints; // amount of lifepoints given

//constructor
Artifact ::Artifact()
{
    key = 0;
    rarity = 0;
    lifepoints = 0;
    tag = 111;
    position.y = 0;
    position.x = 0;
}

//constructor
Artifact ::Artifact(int key, int rarity, int posy, int posx, chtype tag) : Entity(position.y, position.x, tag)
{
    this->key = key;
    this->rarity = rarity;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = 111;
}

//returns lifepoints
int Artifact ::getArtLifepoints(Artifact p)
{
    return p.lifepoints;
}

//returns rarity
int Artifact ::getArtRarity(Artifact p)
{
    return p.rarity;
}


chtype Artifact ::getArtTile(int a)
{
    switch (a)
    {
    case '1':
        return 169;
    case '2':
        return 174;
    case '3':
        return 167;
    case '4':
        return 163;
    }

    return -1;
}

// sets artifact lifepoints and tag based on rarity
void Artifact ::setArtifact(Artifact p)
{
    int prarity = p.rarity;
    switch (prarity)
    {
    case '1':
        p.lifepoints = 1;
        p.tag = 169;
    case '2':
        p.lifepoints = 3;
        p.tag = 174;
    case '3':
        p.lifepoints = 7;
        p.tag = 167;
    case '4':
        p.lifepoints = 10;
        p.tag = 163;
    }
}

void Artifact ::printArtifact(Artifact p, WINDOW *w)
{
    int py = p.position.y;
    int px = p.position.x;
    mvwaddch(w, py, px, p.tag);
}