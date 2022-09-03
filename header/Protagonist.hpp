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

    p_bulletlist headB;

public:
    // constructor
    Protagonist();

    // constructor
    Protagonist(p_bulletlist headB, int current_life, int max_life, int atk_damage, int score, int y, int x, chtype tag);

    // returns head to list of ally bullets
    p_bulletlist getHeadB();

    // head insert a new bullet
    void bulletHeadInsert(bullet b);

    // removes whatever bullet is given as parameter
    void bulletRemove(bullet b);

    // increases life basing on the gained artifact
    void gainLife(int p);

    //sets protagonist's score;
    void set_score(int newscore);

};