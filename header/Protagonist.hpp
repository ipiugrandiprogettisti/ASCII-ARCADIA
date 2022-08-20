#include "Character.hpp"
#include "Artifact.hpp"
#include "Power.hpp"

// ASCII symbol 182 ¶

// lista degli artefatti che ha preso il protagonista
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

// pointer to protagonist's artifacts list
typedef inventoryA *p_inventA;

// pointer to protagonist's powers list
typedef inventoryP *p_inventP;

// lista dei proiettili sparati
typedef struct bulletlist
{
    bullet B;
    bulletlist *next;

} bulletlist;

// pointer to protagonist's bullets list
typedef bulletlist *p_bulletlist;

// classe protagonista
class Protagonist : public Character
{
public:
    int n_bullets;
    p_inventA headA;
    p_inventP headP;
    p_bulletlist headB;

    // constructor
    Protagonist();

    // constructor
    Protagonist(int n_bullets, p_inventA headA, p_inventP headP, p_bulletlist headB, int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // print protagonist
    void printProtagonist(Protagonist P, WINDOW *w);

    // inserisce un nuovo bullet in testa
    p_bulletlist bulletHeadInsert(p_bulletlist head, bullet b);

    // inserisce un nuovo bullet in coda
    p_bulletlist bulletTailInsert(p_bulletlist head, bullet b);

    // funzione che rimuove un bullet qualunque
    p_bulletlist bulletRemove(p_bulletlist head, bullet b);

    void gainLife(Protagonist a, Artifact p);
};