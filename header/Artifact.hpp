#include "Entity.hpp"
#include "Character.hpp"

#define NMAX 30
#define COMMON 1     // 1 pt vita
#define RARE 2       // 3 pt vita
#define VERY_RARE 3  // 5 pt vita
#define SPECIAL 4    // 7 pt vita
#define EPIC 5       // 10 pt vita
#define LEGENDARY 6, // 15 pt vita
#define MYTHIC 7     // 20 pt vita
// i could difference between consumable and collectables
//  classe artefatto -> da vita etc
class Artifact : public Entity
{
protected:
    char name[NMAX];
    int lifepoints; // quanti punti vita dà
    int rarity;

public:
    Artifact();

    Artifact(char name[NMAX], int rarity, int y, int x, chtype tag);

    // returns artifact life points
    int getlifep(Artifact p);
    // returns artifact rarity
    int getrarity(Artifact p);
    // sets artifact lifepoints based on rarity
    void set_lifep(Artifact p, int prarity);
    // resets character life based on artifact healing
    void gainlife(Character a, Artifact p);
};