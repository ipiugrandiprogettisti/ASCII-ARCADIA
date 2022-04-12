typedef struct pos
{
    int x;
    int y;
} pos;

class Entity
{
protected:
    pos position;

public:
    // constructor
    Entity();

    // constructor
    Entity(int x, int y);

    // returns entity's current position
    pos getPosition();
};