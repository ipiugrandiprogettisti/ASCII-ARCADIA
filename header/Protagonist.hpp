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

    /*
     da qui in giù metto le mie funzioni, non toccatele pls -annalisa
     le funzioni che comprendono sia un artefatto/potere che personaggio
     le facciamo tutte sulla classe protagonista perchè non posso includere il file
     personaggio nelle classi artef/potere o si includono  a vicenda e per compilare
     va in loop
    */

    // check if the power is of the right type, if it is adds a bullet
    void addBullet(Protagonist a, Power p);
    // adds life based on artifact healing
    void gainLife(Protagonist a, Artifact p);
};