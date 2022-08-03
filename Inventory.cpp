#include "header/Inventory.hpp"

p_invent invent_head;
int y;
int x;
Inventory ::Inventory()
{
    invent_head = NULL;
    y = 0;
    x = 0;
};
Inventory ::Inventory(p_invent invent_head, int y, int x)
{
    this->invent_head = invent_head;
    this->y = y;
    this->x = x;
};