#include "header/Artifact.hpp"

char name[NMAX];

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

Artifact ::Artifact(char name[NMAX], int rarity, int lifepoints, int posy, int posx, chtype tagg) : Entity(position.y, position.x, tag)
{
    strcpy(this->name, name);
    this->rarity = rarity;
    this->lifepoints = 0;
    this->position.y = posy;
    this->position.x = posx;
    this->tag = tagg;
}

int Artifact ::getlifep(Artifact p)
{
    return p.lifepoints;
}

int Artifact ::getrarity(Artifact p)
{
    return p.rarity;
}

void Artifact ::set_lifep(Artifact p)
{
    int prarity = p.rarity;
    switch (prarity)
    {
    case 1:
        p.lifepoints = 1;
    case 2:
        p.lifepoints = 3;
    case 3:
        p.lifepoints = 7;
    case 4:
        p.lifepoints = 10;
    }
}

void Artifact ::set_symbol(Artifact p)
{
    int prarity = p.rarity;
    switch (prarity)
    {
    case '1':
        p.tag = 169;
    case '2':
        p.tag = 174;
    case '3':
        p.tag = 167;
    case '4':
        p.tag = 163;
    }
}

void Artifact ::gainlife(Character a, Artifact p)
{
    int actual = a.current_life;
    int heal = p.lifepoints;
    a.current_life = actual + heal;
}

void Artifact ::printArtifact(Artifact p, WINDOW *w)
{
    int py = p.position.y;
    int px = p.position.x;
    mvwaddch(w, py, px, p.tag);
}