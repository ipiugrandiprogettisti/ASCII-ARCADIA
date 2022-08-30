#include "Entity.hpp"

#define COMMON 1  // 1 life point, simbolo ascii 'C'
#define RARE 2    // 3 life points, simbolo ascii 'R'
#define SPECIAL 3 // 5 life points, simbolo ascii "$"
#define EPIC 4    // 7 life points, simbolo ascii "£"

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
    Artifact(int rarity, int lifepoints, int y, int x, chtype tag);

    // returns artifact life points
    int getArtLifepoints();

    // return chtype
    chtype getArtTile();

    // sets artifact lifepoints and tag based on rarity
    // void setArtifact(int r);
};