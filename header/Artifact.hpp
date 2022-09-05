#include "Entity.hpp"

#define COMMON 1  // 1 life point, simbolo ascii 'C'
#define RARE 2    // 3 life points, simbolo ascii 'R'
#define SPECIAL 3 // 5 life points, simbolo ascii "$"
#define EPIC 4    // 7 life points, simbolo ascii "£"

//  classe artefatto -> da vita
class Artifact : public Entity
{
protected:
    int lifepoints; // quanti punti vita dà
    int rarity;

public:
    // null constructor
    Artifact();
    // artifact constructor
    Artifact(int rarity, int lifepoints, int y, int x, chtype tag);

    // returns artifact life points
    int getLifepoints();
    int getRarity();
    void setLifepoints(int life);
    void setRarity(int rar);
};
