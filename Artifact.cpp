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
Artifact ::Artifact(int rarity, int posy, int posx, chtype tag) : Entity(position.y, position.x, tag)
{
    this->rarity = rarity;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = ' ';
}

// returns lifepoints
int Artifact ::getArtLifepoints()
{
    switch (tag)
    {
    case 'C':
        return 1;
    case 'R':
        return 3;
    case '$':
        return 5;
    case 'ACS_STERLING':
        return 7;
    };
}

chtype Artifact ::getArtTile()
{
    switch (rarity)
    {
    case '1':
        return 'C';
    case '2':
        return 'R';
    case '3':
        return '$';
    case '4':
        return ACS_STERLING;
    }
}

// sets artifact lifepoints and tag based on rarity
void Artifact ::setArtifact(int r)
{
    rarity = r;
    switch (r)
    {
    case '1':
        lifepoints = 1;
        tag = 'C';
    case '2':
        lifepoints = 3;
        tag = 'R';
    case '3':
        lifepoints = 5;
        tag = '$';
    case '4':
        lifepoints = 7;
        tag = ACS_STERLING;
    }
}
