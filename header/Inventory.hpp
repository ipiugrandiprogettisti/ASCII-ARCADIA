#include "Power.hpp"

// costruzione lista per inventario
struct inventory
{
    Power p;
    inventory *next;
};

typedef inventory *p_invent;

// inventario per i poteri raccolti
class Inventory
{
protected:
    p_invent invent_head;
    int y;
    int x;

public:
    // costruttore nullo
    Inventory();
    // costruttore
    Inventory(p_invent invent_head, int y, int x);
};