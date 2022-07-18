#include "Entity.hpp"
#include "Character.hpp"

#define NMAX 30
#define COMMON 1  // 1 pt vita, simbolo ascii 169 "©"
#define RARE 2    // 3 pt vita, simbolo ascii 174 "®"
#define SPECIAL 3 // 7 pt vita, simbolo ascii 167 "§"
#define EPIC 4    // 10 pt vita, simbolo ascii 163 "£"

//  classe artefatto -> da vita etc
class Artifact : public Entity
{
protected:
    char name[NMAX];
    int lifepoints; // quanti punti vita dà
    int rarity;

public:
    // constructor
    Artifact();
    // constructor
    Artifact(char name[NMAX], int rarity, int y, int x, chtype tag);

    // returns artifact life points
    int getLifepoints(Artifact p);
    // returns artifact rarity
    int getRarity(Artifact p);
    // sets artifact lifepoints and tag based on rarity
    void setArtifact(Artifact p);

    // resets character life based on artifact healing
    void gainLife(Character a, Artifact p);
    // print artifact on certain position
    void printArtifact(Artifact p, WINDOW *w);
};