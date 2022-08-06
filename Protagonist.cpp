#include "header/Protagonist.hpp"

int n_bullets;
p_inventA headA;
p_inventP headP;

Protagonist::Protagonist()
{
    n_bullets = 0;
    headA = NULL;
    headP = NULL;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

Protagonist::Protagonist(int n_bullets, p_inventA headA, p_inventP headP, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, y, x, tag)
{
    this->n_bullets = 1;
    this->headA = headA;
    this->headP = headP;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = 0;
    this->position.x = 0;
    this->tag = 182;
}

void Protagonist::printProtagonist(Protagonist P, WINDOW *w)
{
    int p_y = P.position.y;
    int p_x = P.position.x;

    mvwaddch(w, p_y, p_x, P.tag);
}

// da qui in giù metto le mie funzioni -annalisa
// check if the power is of the right type, if it is adds a bullet
void Protagonist ::addBullet(Protagonist a, Power p)
{
    if (p.type == 2)
    {
        a.n_bullets++;
    }
}

// add life based on artifact healing
void Protagonist::gainLife(Protagonist a, Artifact p)
{
    int actual = a.current_life;
    int heal = p.lifepoints;
    a.current_life = actual + heal;
}

void Protagonist ::eraseItem(Protagonist a, Artifact c, Power p, WINDOW *w)
{
    // protagonista e artef/potere nella stessa pos, disegna protagonista sopra
    if (a.position.y == c.position.y && a.position.x == c.position.x || a.position.y == p.position.y && a.position.x == p.position.x)
    {
        mvwaddch(w, a.position.y, a.position.x, a.tag);
    }
}