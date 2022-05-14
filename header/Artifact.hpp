#include "Entity.hpp"
#include "Character.hpp"

#define NMAX 30
#define COMMON 1     // 1 pt vita, simbolo ascii 169 "©"
#define RARE 2       // 3 pt vita, simbolo ascii 174 "®"
#define VERY_RARE 3  // 5 pt vita, simbolo ascii 248 "ø"
#define SPECIAL 4    // 7 pt vita, simbolo ascii 216 "Ø"
#define EPIC 5       // 10 pt vita, simbolo ascii 163 "£"
#define LEGENDARY 6, // 15 pt vita, simbolo ascii 165 "¥"
#define MYTHIC 7     // 20 pt vita, simbolo ascii 167 "§"
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
    void set_lifep(Artifact p);
    // sets artifact symbol based on rarity
    void set_symbol(Artifact p);

        // resets character life based on artifact healing
    void gainlife(Character a, Artifact p);

    void printArtifact(Artifact p, WINDOW *w);
};