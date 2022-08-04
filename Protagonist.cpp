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
    this->n_bullets = n_bullets;
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