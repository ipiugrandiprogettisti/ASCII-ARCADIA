
#include "Entity.hpp"
// i could difference between consumable and collectables
//  classe artefatto -> da vita etc
class Artifact : public Entity
{
protected:
    enum rarity
    {
        common = 1,
        rare = 2,
        very_rare = 3,
        special = 4,
        epic = 5,
        legendary = 6,
        mithyc = 7
    };

public:
};