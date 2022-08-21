#include "header/Protagonist.hpp"

p_bulletlist headB;

Protagonist::Protagonist()
{
    headB = NULL;
    current_life = 0;
    max_life = 0;
    atk_damage = 0;
    position.y = 0;
    position.x = 0;
    tag = 111;
}

Protagonist::Protagonist(p_bulletlist headB, int current_life, int max_life, int atk_damage, int y, int x, chtype tag) : Character(current_life, max_life, atk_damage, y, x, tag)
{
    this->headB = headB;
    this->current_life = current_life;
    this->max_life = max_life;
    this->atk_damage = atk_damage;
    this->position.y = y;
    this->position.x = x;
    this->tag = tag;
}

void Protagonist::printProtagonist(Protagonist P, WINDOW *w)
{
    int p_y = P.position.y;
    int p_x = P.position.x;

    mvwaddch(w, p_y, p_x, P.tag);
}

// head insert new bullet
p_bulletlist Protagonist::bulletHeadInsert(p_bulletlist head, bullet b)
{
    p_bulletlist newbullet = new bulletlist;
    newbullet->B = b;
    newbullet->next = head;
    head = newbullet;

    return head;
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
p_bulletlist Protagonist::bulletRemove(p_bulletlist head, bullet b)
{
    p_bulletlist x;
    p_bulletlist tmp;
    bool found = false;
    if (head == NULL)
    {
        head = head;
    }
    else if (head->B.bullet_damage == b.bullet_damage && head->B.bullet_tag == b.bullet_tag && head->B.bulletpos.x == b.bulletpos.x && head->B.bulletpos.y == b.bulletpos.y && head->B.direction == b.direction)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    else
    {
        x = head;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->B.bullet_damage == b.bullet_damage && x->next->B.bullet_tag == b.bullet_tag && x->next->B.bulletpos.x == b.bulletpos.x && x->next->B.bulletpos.y == b.bulletpos.y && x->next->B.direction == b.direction)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
    return head;
}

// add life based on artifact healing
void Protagonist::gainLife(Protagonist a, Artifact p)
{
    int actual = a.current_life;
    int heal = p.lifepoints;
    a.current_life = actual + heal;
}
