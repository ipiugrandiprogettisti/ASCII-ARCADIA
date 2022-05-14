#include "header/Artifact.hpp"

char name[NMAX];
int lifepoints; // quanti punti vita dà
int rarity;

Artifact ::Artifact()
{
    rarity = 0;
    lifepoints = 0;
    tag = 111;
    position.y = 0;
    position.x = 0;
};

Artifact ::Artifact(char name[NMAX], int rarity, int posy, int posx, chtype tagg) : Entity(position.y, position.x, tag)
{
    strcpy(this->name, name);
    this->rarity = rarity;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = tagg;
    this->lifepoints = 0;
};

int Artifact ::getlifep(Artifact p)
{
    return p.lifepoints;
}

int Artifact ::getrarity(Artifact p)
{
    return p.rarity;
}

void Artifact ::set_lifep(Artifact p, int prarity)
{
    prarity = p.rarity;
    switch (prarity)
    {
    case 1:
        p.lifepoints = 1;
    case 2:
        p.lifepoints = 3;
    case 3:
        p.lifepoints = 5;
    case 4:
        p.lifepoints = 7;
    case 5:
        p.lifepoints = 10;
    case 6:
        p.lifepoints = 15;
    case 7:
        p.lifepoints = 20;
    }
}

void Artifact ::gainlife(Character a, Artifact p)
{
    int actual = a.current_life;
    int heal = p.lifepoints;
    a.current_life = actual + heal;
};