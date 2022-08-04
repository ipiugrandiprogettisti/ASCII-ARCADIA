#include "header/Artifact.hpp"

int rarity;
int lifepoints; // quanti punti vita dà
Artifact ::Artifact()
{
    rarity = 0;
    lifepoints = 0;
    tag = 111;
    position.y = 0;
    position.x = 0;
}

Artifact ::Artifact(int rarity, int posy, int posx, chtype tag) : Entity(position.y, position.x, tag)
{

    this->rarity = rarity;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = 111;
}

int Artifact ::getLifepoints(Artifact p)
{
    return p.lifepoints;
}

int Artifact ::getRarity(Artifact p)
{
    return p.rarity;
}

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