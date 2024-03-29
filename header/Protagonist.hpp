#include "Character.hpp"
#include "Artifact.hpp"
#include "Power.hpp"

// ASCII symbol ACS_PI

// bullet list
typedef struct bulletlist
{
    bullet B;
    bulletlist *next;

} bulletlist;

// pointer to protagonist's bullets list
typedef bulletlist *p_bulletlist;

// class protagonist
class Protagonist : public Character
{
protected:
    bool isAlive;
    p_bulletlist headB;
    int current_life; // in termini di cuori posseduti al momento

public:
    // constructor
    Protagonist();

    // constructor
    Protagonist(bool isAlive, p_bulletlist headB, int current_life, int score, int y, int x, chtype tag);

    //ritorna il bool isAlive
    bool getisAlive();

    //modifica il bool isAlive
    void setisAlive(bool b);

    // returns head to list of ally bullets
    p_bulletlist getHeadB();

    void setHeadB(p_bulletlist p);

    // head insert a new bullet
    void bulletHeadInsert(bullet b);

    // removes whatever bullet is given as parameter
    void bulletRemove(bullet b);

    // ritorna la vita corrente
    int getLife();

    // prende in input il danno ricevuto e aggiorna la vita sottraendoglielo
    bool takeDamage(int damage_received);

    // increases life basing on the gained artifact
    void gainLife(int p);

    // sets protagonist's score;
    void set_score(int newscore);
};