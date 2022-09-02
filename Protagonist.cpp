#include "header/Protagonist.hpp"

int score;
p_bulletlist headB;

Protagonist::Protagonist()
{
    score = 0;
    headB = NULL;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = ' ';
}

Protagonist::Protagonist(int score, p_bulletlist headB, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, y, x, tag)
{
    this->score = score;
    this->headB = headB;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

int Protagonist::getScore()
{
    return this->score;
}

void Protagonist::printProtagonist(Protagonist P, WINDOW *w)
{
    int p_y = P.position.y;
    int p_x = P.position.x;

    mvwaddch(w, p_y, p_x, P.tag);
}

// returns head to list of ally bullets
p_bulletlist Protagonist::getHeadB()
{
    return this->headB;
}

// head insert new bullet
void Protagonist::bulletHeadInsert(bullet b)
{
    p_bulletlist newbullet = new bulletlist;
    newbullet->B = b;
    newbullet->next = this->headB;
    this->headB = newbullet;
}

// tail insert a new bullet
p_bulletlist Protagonist::bulletTailInsert(p_bulletlist head, bullet b)
{
    p_bulletlist tmp;
    if (head == NULL)
    {
        head = new bulletlist;
        head->B = b;
        head->next = NULL;
    }
    else
    {
        for (tmp = head; tmp->next != NULL; tmp = tmp->next)
        {
        }
        tmp->next = new bulletlist;
        tmp->next->B = b;
        tmp->next->next = NULL;
    }
    return head;
}

// removes whatever bullet given as a parameter
void Protagonist::bulletRemove(bullet b)
{
    p_bulletlist x;
    p_bulletlist tmp;
    bool found = false;
    if (this->headB == NULL)
    {
        this->headB = this->headB;
    }
    else if (this->headB->B.bullet_tag == b.bullet_tag && this->headB->B.bulletpos.x == b.bulletpos.x && this->headB->B.bulletpos.y == b.bulletpos.y && this->headB->B.direction == b.direction)
    {
        tmp = this->headB;
        this->headB = this->headB->next;
        delete tmp;
    }
    else
    {
        x = this->headB;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->B.bullet_tag == b.bullet_tag && x->next->B.bulletpos.x == b.bulletpos.x && x->next->B.bulletpos.y == b.bulletpos.y && x->next->B.direction == b.direction)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
}

// add life
void Protagonist::gainLife(int p)
{
    this->current_life += p;
}

// spawn bullet at sx
/*
pos Protagonist ::createBul(int direction)
{
    pos bpos;
    switch(direction){
        case 0:
            bpos.y = position.y++;
            bpos.x = position.x;
        case 1:
        etc..
    }

    bullet bl;
    bl.bulletpos = bpos;
    bl.bullet_tag = ACS_BULLET;
    bl.bullet_damage = 10; // <-- messo a caso
    bl.direction = 1;

    this->bulletHeadInsert(headB, bl);
}
*/