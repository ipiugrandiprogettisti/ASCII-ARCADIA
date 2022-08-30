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
int Artifact ::getArtLifepoints()
{
    int lifep = 0;
    switch (tag)
    {
    case 'C':
        lifep = 1;
    case 'R':
        lifep = 3;
    case '$':
        lifep = 5;
    case 'ACS_DIAMOND':
        lifep = 7;
    };

    return lifep;
}

chtype Artifact ::getArtTile()
{
    chtype r = ' ';
    switch (rarity)
    {
    case '1':
        r = 'C';
    case '2':
        r = 'R';
    case '3':
        r = '$';
    case '4':
        r = ACS_DIAMOND;
    }
    return r;
}

// sets artifact lifepoints and tag based on rarity
/*
void Artifact ::setArtifact(int r)
{
    switch (r)
    {
    case '1':
        lifepoints = 1;
        tag = ACS_DARROW;
    case '2':
        lifepoints = 3;
        tag = ACS_LANTERN;
    case '3':
        lifepoints = 5;
        tag = '$';
    case '4':
        lifepoints = 7;
        tag = ACS_DIAMOND;
    }
    rarity = r;
}
*/
