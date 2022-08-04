#include "Entity.hpp"

#define COMMON 1  // 1 life point, simbolo ascii 169 "©"
#define RARE 2    // 3 life points, simbolo ascii 174 "®"
#define SPECIAL 3 // 7 life points, simbolo ascii 167 "§"
#define EPIC 4    // 10 life points, simbolo ascii 163 "£"

//  classe artefatto -> da vita
class Artifact : public Entity
{
public:
    int lifepoints; // quanti punti vita dà
    int rarity;

public:
    // constructor
    Artifact();
    // artifact constructor with rarity, pos y, posx, tag (set it 111 by default)
    // after creating an artifact you need to set  his tag and lifepoints with funct setArtifact()
    Artifact(int rarity, int y, int x, chtype tag);

    // returns artifact life points
    int getLifepoints(Artifact p);
    // returns artifact rarity
    int getRarity(Artifact p);
    // sets artifact lifepoints and tag based on rarity
    void setArtifact(Artifact p);

    // print artifact on certain position
    void printArtifact(Artifact p, WINDOW *w);
};