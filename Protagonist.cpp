#include "header/Protagonist.hpp"

p_bulletlist headB;

Protagonist::Protagonist()
{
    headB = NULL;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    score = 0;
    position.y = 0;
    position.x = 0;
    tag = ' ';
}

Protagonist::Protagonist(p_bulletlist headB, int current_life, int max_life, int atk_damage, int score, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, score, y, x, tag)
{
    this->headB = headB;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->score = score;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
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

//sets protagonist's score
void Protagonist::set_score(int newscore)
{
    this->score += newscore;
}
