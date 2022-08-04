#include "Character.hpp"
#include "Artifact.hpp"
#include "Power.hpp"

// ASCII symbol 182 ¶

//lista degli artefatti che ha presp il protagonista
typedef struct inventoryA
{
    Artifact A;
    inventoryA *next;
} inventoryA;

typedef struct inventoryP
{
    Power P;
    inventoryP *next;
} inventoryP;

typedef inventoryA *p_inventA;
typedef inventoryP *p_inventP;

// classe protagonista
class Protagonist : public Character
{
protected:
    int n_bullets;
    p_inventA headA;
    p_inventP headP;

public:
    // constructor
    Protagonist();

    // constructor
    Protagonist(int n_bullets, p_inventA headA, p_inventP headP, int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // print protagonist
    void printProtagonist(Protagonist P, WINDOW *w);
};