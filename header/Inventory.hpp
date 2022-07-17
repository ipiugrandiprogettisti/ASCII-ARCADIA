#include "Power.hpp"

struct invent
{
    Power p;
    invent *next;
};

typedef invent *p_invent;

class Inventory
{
protected:
    p_invent invent_head;
    int y;
    int x;

public:
    Inventory();

    Inventory(p_invent invent_head, int y, int x);
};