// Room class file

#include "header/Room.hpp"
#include "header/utils.hpp"
#include <ctime>

// place object in room with struct
void Room::placeObject(pos position, chtype tag)
{
    this->look[position.y][position.x] = tag;
}

// place object in room without struct
void Room::placeObject(int y, int x, chtype tag)
{
    this->look[y][x] = tag;
}

// place a door. y and x are position, i is the side where the door is located
void Room::placeDoor(door doorInfo)
{
    switch (doorInfo.side)
    {
    case 0: // bottom side
    case 2: // top side
        this->placeObject(doorInfo.y, doorInfo.x - 1, ACS_RTEE);
        this->placeObject(doorInfo.y, doorInfo.x + 1, ACS_LTEE);
        break;
    case 1: // left side
    case 3: // rigth side
        this->placeObject(doorInfo.y - 1, doorInfo.x, ACS_BTEE);
        this->placeObject(doorInfo.y + 1, doorInfo.x, ACS_TTEE);
        break;
    default:
        break;
    }

    if (doorInfo.isOpen == false)
        this->placeObject(doorInfo.y, doorInfo.x, doorInfo.tile.close);
    else
        this->placeObject(doorInfo.y, doorInfo.x, doorInfo.tile.open);
}

// aux function to prevent non-free wall
bool Room::tileIsFree(pos position)
{
    bool free = false;
    int sidesNotFree = 0;

    if (this->look[position.y + 1][position.x] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y - 1][position.x] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y][position.x + 1] != ' ')
        sidesNotFree += 1;
    if (this->look[position.y][position.x - 1] != ' ')
        sidesNotFree += 1;

    if (sidesNotFree < 4)
        free = true;

    return free;
}

// check if tiles around wall are free
bool Room::checkTilesAround(pos position, pos previousPosition)
{
    bool free = true;
    int i = 0;
    int j = 0;
    for (i = position.y; i < position.y + 2; i++)
    {
        for (j = position.x; j < position.x + 2; j++)
        {
            if (this->look[i][j] != ' ' && i != previousPosition.y && j != previousPosition.x)
            {
                free = false;
                break;
            }
        }
    }
    return free;
}

// places 1 power to open door
void Room::placePower(bool b)
{
    Power p;
    p.set_tag('P');
    chtype rar = p.get_tag();
    pos posPow;
    chtype var = ' ';
    do
    {
        int posy = rand() % WIDTH + 1;
        int posx = rand() % HEIGTH + 1;
        posPow.y = posy;
        posPow.x = posx;
        var = getTile(posPow);
    } while (var != ' ' || posPow.y > (WIDTH - 3) || posPow.y < 3 || posPow.x > (HEIGTH - 3) || posPow.x < 3);
    this->placeObject(posPow, rar);
    powerHeadinsert(p);
};

// places artifacts
void Room::placeArtifacts()
{
    Artifact a(0, 0, 2, 2, ' ');
    int nArt = rand() % 2;
    for (int i = 0; i < nArt; i++)
    {
        chtype chflag;
        do
        {
            a.setPosition(rand() % WIDTH, rand() % HEIGTH);
            pos flag;
            flag.x = a.getPosition().x;
            flag.y = a.getPosition().y;
            chflag = this->getTile(flag);
        } while (chflag != ' ');

        int artRarity = rand() % 100 + 1;

        if (artRarity <= 60 && artRarity > 0)
        {
            a.set_tag('C');
            a.setRarity(1);
            a.setLifepoints(1);
        }
        else if (artRarity > 60 && artRarity <= 85)
        {
            a.set_tag('R');
            a.setRarity(2);
            a.setLifepoints(3);
        }
        else if (artRarity > 85 && artRarity <= 95)
        {
            a.set_tag('$');
            a.setRarity(3);
            a.setLifepoints(5);
        }
        else if (artRarity > 95 && artRarity >= 100)
        {
            a.set_tag(ACS_DIAMOND);
            a.setRarity(4);
            a.setLifepoints(7);
        }

        placeObject(a.getPosition(), a.get_tag());
        ArtifactHeadinsert(a);
    }
}

// places random enemies
void Room::place_enemies(bool b)
{

    Enemy en(0, 0, 0, 0, ' ');

    int n = rand() % 3 + 1;

    for (int i = 0; i < n; i++)
    {
        int n_type = rand() % 100 + 1;
        if (n_type <= 40)
        {
            en.set_tag(ACS_BLOCK);
            en.set_enemyKey(1);
            en.set_score(20);
        }
        else if (n_type <= 80 && n_type > 40)
        {
            en.set_tag(ACS_NEQUAL);
            en.set_enemyKey(2);
            en.set_score(30);
        }
        else if (n_type <= 100 && n_type > 80)
        {
            en.set_tag('@');
            en.set_enemyKey(3);
            en.set_score(50);
        }

        bool flag = true;
        pos posEnemy;
        chtype p = ' ';
        while (flag == true)
        {
            posEnemy.y = rand() % 24 + 3;
            posEnemy.x = rand() % 94 + 3;

            en.setPosition(posEnemy.y, posEnemy.x);
            p = this->getTile(en.getPosition());
            if (p == ' ')
            {
                this->placeObject(en.getPosition(), en.get_tag());
                this->drawLook();
                this->HeadInsert_enemy(en);
                flag = false;
            }
        }
    }
}

// random wall path generator
void Room::randomPathWall(pos position, int h, int w)
{
    w -= 2;
    h -= 2;

    int random = 0;
    bool free = true;
    pos tmp = position;
    pos previousPosition;
    while (this->tileIsFree(tmp) && (h > 0 && w > 0))
    {
        random = rand() % 4;
        switch (random)
        {
        case 0:
            h -= 1;
            tmp.y += 1;
            free = checkTilesAround(position, previousPosition);
            break;
        case 1:
            h -= 1;
            tmp.y += 1;
            free = checkTilesAround(position, previousPosition);
            break;
        case 2:
            w -= 1;
            tmp.x += 1;
            free = checkTilesAround(position, previousPosition);
            break;
        case 3:
            h -= 1;
            tmp.x += 1;
            free = checkTilesAround(position, previousPosition);
            break;
        default:
            break;
        }
        if (free)
        {
            this->placeObject(tmp, ACS_CKBOARD);
            previousPosition = tmp;
        }
    }
}

// Constructor
Room ::Room()
{
    int key = -1; // a room is always created with a given key. if no set it to -1 (error)
    win = NULL;   // at the time of creating a room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new artifactsList;
    objects.enemies = new listEnemies;
    objects.powers = new powersList;
    objects.bulletEnemies = new bulletsEnemies;
    objects.artifacts = NULL; // set the amount of artifacts in the room to 0
    objects.enemies = NULL;   // set the amount of enemies in the room to 0
    objects.powers = NULL;    // set the amount of powers in the room to 0
    objects.bulletEnemies = NULL;
    // doorInfo are already set when defined, check Room.hpp for more info
}

// Constructor
Room::Room(int key)
{
    this->key = key;  // unique
    this->win = NULL; // at the time of creating a new room its window will be null. the first time that it will be drawed it also will be assigned
    objects.artifacts = new artifactsList;
    objects.enemies = new listEnemies;
    objects.powers = new powersList;
    objects.bulletEnemies = new bulletsEnemies;
    objects.artifacts = NULL; // set the amount of artifacts in the room to 0
    objects.enemies = NULL;   // set the amount of artifacts in the room to 0
    objects.powers = NULL;
    objects.bulletEnemies = NULL;
    // doorInfo are already set when defined, check Room.hpp for more info
}

// returns the key of the room
int Room::getKey()
{
    return key;
}

// returns the WINDOW of the room
WINDOW *Room::getWindow()
{
    return win;
}

// returns the object list of the room
struct objContainer Room::getObjectList()
{
    return objects;
}

// returns the given room's door information; if door doesn't exist returns a "-1" door (check struct door). 1 next room, 0 previous room
struct door Room::getDoor(int isNextRoom)
{
    struct door myDoor;
    myDoor = doorInfo[isNextRoom];

    return myDoor;
}

// set the given door information
void Room::setDoor(int isNextRoom, struct door myDoor)
{
    doorInfo[isNextRoom] = myDoor;
}

// draws the room
void Room::drawLook()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int k = 0; k < HEIGTH; k++)
        {
            mvwaddch(this->win, i, k, look[i][k]);
        }
    }
}

bool Room::getDrawnPower()
{
    return this->drawnPower;
}
void Room::setDrawnPower(bool b)
{
    this->drawnPower = b;
}

// sets up the room if myDoor doesnt exist (-1), then it is the first room being set up. myDoor is previous door of the new room, empty if first room
bool Room::setUp(int maxCols, int maxLines, struct door myDoor)
{
    // if room was already drew there is no need to redraw, so function ends
    if (drawn == true)
        return false;

    // if myDoor is a real door, then it isnt the first room that is being set up
    bool previousRoomExists = false;
    if (myDoor.x >= 0 || myDoor.y >= 0)
    {
        previousRoomExists = true;
    }

    WINDOW *room;

    // this will prints in the room window, which is a smaller window in the terminal
    int winWidth = HEIGTH / 1.5 + 1, winHeigth = WIDTH / 2 + 1; // room dimensions
    int halfY = maxCols / 2, halfX = maxLines / 2;
    int adjWidth = halfX - winWidth / 2;                              // adjusted width
    int adjHeigth = halfY - winHeigth / 2;                            // adjusted heigth
    int offY = (maxLines - WIDTH) / 2, offX = (maxCols - HEIGTH) / 2; // offset; useful to center box

    win = newwin(WIDTH, HEIGTH, offY, offX); // create a CENTERED box

    // PLACING DOORS
    if (previousRoomExists) // checking where the previous door was in order to place it on the opposite side after
    {
        door tmpDoor = myDoor;
        // placing previous door; it has to be placed on the opposite side where it was in the previous room
        switch (tmpDoor.side)
        {
        case 0: // bottom side
            tmpDoor.y = 0;
            tmpDoor.side = 2;
            placeDoor(tmpDoor);
            break;
        case 1: // left side
            tmpDoor.x = HEIGTH - 1;
            tmpDoor.side = 3;
            placeDoor(tmpDoor);
            break;
        case 2: // top side
            tmpDoor.y = WIDTH - 1;
            tmpDoor.side = 0;
            placeDoor(tmpDoor);
            break;
        case 3: // right side
            tmpDoor.x = 0;
            tmpDoor.side = 1;
            placeDoor(tmpDoor);
            break;

        default:
            break;
        }
        tmpDoor.isNextRoom = 0;
        doorInfo[0] = tmpDoor;
    }

    // now we have to draw 1 to (2-1) doors (previous one is already placed)

    int prevDoorsNumber = 0;
    if (previousRoomExists)
        prevDoorsNumber = 1;

    srand(time(0)); // random seed

    int i = 0;

    int side;
    bool isOccupied = true;

    while (isOccupied == true)
    {
        side = rand() % 4; // picking a casual side to place the door
        if (doorInfo[0].side == side)
            isOccupied = true;
        else
            isOccupied = false;
    }

    if (isOccupied == false) // if side is free, then place door
    {
        struct door myDoorTmp;
        myDoorTmp.side = side;
        myDoorTmp.isNextRoom = 1;
        switch (myDoorTmp.side) // match/adjust side to coords
        {
        case 0: // bottom side
            myDoorTmp.y = WIDTH - 1;
            myDoorTmp.x = HEIGTH / 2;
            placeDoor(myDoorTmp);
            break;
        case 1: // left side
            myDoorTmp.y = WIDTH / 2;
            myDoorTmp.x = 0;
            placeDoor(myDoorTmp);
            break;
        case 2: // top side
            myDoorTmp.y = 0;
            myDoorTmp.x = HEIGTH / 2;
            placeDoor(myDoorTmp);
            break;
        case 3: // right side
            myDoorTmp.y = WIDTH / 2;
            myDoorTmp.x = HEIGTH - 1;
            placeDoor(myDoorTmp);
            break;

        default:
            break;
        }

        doorInfo[1] = myDoorTmp;
    }

    // PLACING OBJECTS

    // place wall
    const int MAXWALLS = 75;           // max number of walls in a room
    for (int i = 0; i < MAXWALLS; i++) // number of walls
    {
        const int offsetSXDX = 6, offsetTOPBOTTOM = 3;
        int posY = (rand() % (WIDTH - (offsetTOPBOTTOM * 2))) + offsetTOPBOTTOM; // 3-27
        int posX = (rand() % (HEIGTH - (offsetSXDX * 2))) + offsetSXDX;          // 6-93
        const int MAXWALLHEIGTH = (((WIDTH - (offsetTOPBOTTOM)) - posY) / 1.5) + 1;
        const int MAXWALLWIDTH = (((HEIGTH - (offsetSXDX)) - posX) / 1.5) + 1;
        int h = (rand() % (MAXWALLHEIGTH)) + 1; // random number of walls
        int w = (rand() % (MAXWALLWIDTH)) + 1;  // random number of walls

        pos pos1;
        pos1.x = posX;
        pos1.y = posY;

        randomPathWall(pos1, h, w);
    }

    place_enemies(1);
    placeArtifacts();
    drawn = true;

    return drawn;
}

// true open doors, false close doors
void Room::openDoors(bool open)
{
    doorInfo[0].isOpen = open;
    doorInfo[1].isOpen = open;

    placeDoor(doorInfo[0]);
    placeDoor(doorInfo[1]);

    this->drawLook();
    refresh();
    wrefresh(this->getWindow());
}

// returns chtype for the given position in room
chtype Room::getTile(pos position)
{
    return this->look[position.y][position.x];
}

// returns the width of the room (look)
int Room::getMaxWidth()
{
    return WIDTH;
}

// returns the height of the room (look)
int Room::getMaxHeight()
{
    return HEIGTH;
}

chtype Room::checkNextPos(pos p, int direction)
{
    pos next = p;

    // testo future posizioni su posizione di prova
    if (direction == 3)
    { // direzione 3 : va verso dx, aumenta x di 1
        next.x++;
    }
    else if (direction == 0)
    { // direzione 0 : va verso il basso, aumenta y di 1
        next.y++;
    }
    else if (direction == 1)
    { // direzione 1 : va verso sx, diminuisce x di 1
        next.x--;
    }
    else if (direction == 2)
    { // direzione 2: va verso l'alto, diminuisce y di 1
        next.y--;
    }

    chtype nextChar = getTile(next);
    return nextChar;
}

pos Room::nextPos(pos p, int direction)
{
    pos next;
    next.y = p.y;
    next.x = p.x;

    if (direction == 3)
    { // direzione 3 : va verso dx, aumenta x di 1
        next.y = p.y;
        next.x++;
    }
    else if (direction == 0)
    { // direzione 0 : va verso il basso, aumenta y di 1
        next.y++;
        next.x = p.x;
    }
    else if (direction == 1)
    { // direzione 1 : va verso sx, diminuisce x di 1
        next.x--;
        next.y = p.y;
    }
    else if (direction == 2)
    { // direzione 2: va verso l'alto, diminuisce y di 1
        next.y--;
        next.x = p.x;
    }

    return next;
}

// manages one ally bullet collision and movement
void Room::aBullMov(Protagonist &P, bullet &b)
{

    p_bulletlist tmp = P.getHeadB();

    chtype empty = ' ';
    chtype nextP; // char in next position
    int dir = b.direction;

    pos now = b.bulletpos; // actual pos
    // nextP = checkNextPos(now, b.direction);   // char in pos futura
    pos next = nextPos(now, dir); // pos futura

    nextP = Room::getTile(next);
    if (nextP == ACS_VLINE || nextP == ACS_HLINE || nextP == ACS_CKBOARD || nextP == ACS_RTEE || nextP == ACS_LTEE || nextP == ACS_BTEE || nextP == ACS_TTEE) // PROIETTILE -> MURO
    {
        placeObject(now, empty); // remove bull from map
        P.bulletRemove(b);       // remove bull from list
    }
    else if (nextP == 'C' || nextP == 'R' || nextP == '$' || nextP == '%') // PROIETTILE -> ARTEF
    {
        chtype nextA = checkNextPos(next, dir);                                                                                                                   // chtype dopo artefatto //due posti dopo bull
        pos posNextA = nextPos(next, dir);                                                                                                                        // posizione dopo Artefatto
        if (nextA == ACS_VLINE || nextA == ACS_HLINE || nextA == ACS_CKBOARD || nextA == ACS_RTEE || nextA == ACS_LTEE || nextA == ACS_BTEE || nextA == ACS_TTEE) // PROIETTILE -> ARTEF -> MURO
        {                                                                                                                                                         // dopo proiettile e dopo artefatto c'è muro, faccio sparire proiettile
            placeObject(now, empty);                                                                                                                              // rimuove bullet da posizione attuale
            P.bulletRemove(b);                                                                                                                                    // rimuove bullet dalla lista (anna io qui ci passerei P.getHeadB(), non tmp)
        }
        else if (nextA == empty) // PROIETTILE -> ARTEF -> SPAZIO VUOTO
        {

            placeObject(now, empty);
            placeObject(posNextA, ACS_BULLET);
            b.bulletpos = posNextA;
        }
        else if (nextA == 'P') // PROIETTILE -> ARTEF -> POTERE
        {
            chtype nextB = checkNextPos(posNextA, b.direction);                                                                                                       // chtype dopo potere
            pos posNextB = nextPos(posNextA, b.direction);                                                                                                            // pos dopo potere, tre posti dopo bull
            if (nextB == ACS_VLINE || nextB == ACS_HLINE || nextB == ACS_CKBOARD || nextB == ACS_RTEE || nextB == ACS_LTEE || nextB == ACS_BTEE || nextB == ACS_TTEE) // PROIETTILE -> ARTEF -> POTERE -> MURO
            {

                placeObject(now, empty);
                P.bulletRemove(b);
            }
            else if (nextB == empty) // PROIETTILE -> ARTEF -> POTERE -> SPAZIO VUOTO
            {
                placeObject(now, empty);
                placeObject(posNextB, ACS_BULLET);
                b.bulletpos = posNextB;
            }
        }
        else if (nextA == ACS_BULLET || nextA == ACS_DEGREE) // PROIETTILE->ARTEF->PROIETTILE O NEMICO O ALLEATO
        {
            Room::placeObject(now, empty);
            P.bulletRemove(b);
        }

        this->drawLook();
        refresh();
        wrefresh(this->getWindow());
    }
    else if (nextP == '@' || nextP == ACS_NEQUAL || nextP == ACS_BLOCK) // PROIETTILE -> NEMICO
    {

        pListEnemies enList = this->objects.enemies;
        while (enList != NULL)
        { // search enemy
            if (next.x == enList->e.getPosition().x && next.y == enList->e.getPosition().y)
            {
                // enemy found
                Enemy workEn = enList->e;

                P.set_score(workEn.get_score());
                // remove both
                this->enemyRemove(workEn);
                this->placeObject(next, ' ');
                P.bulletRemove(b);
                this->placeObject(now, ' ');
            }
            enList = enList->next;
        }
    }
    else if (nextP == ACS_DEGREE) // PROIETTILE -> PROETTILE NEMICO, vengono eliminati entrambi
    {
        p_bulletsEnemies tmpnem = this->objects.bulletEnemies;
        bool flag = false;
        while (tmpnem != NULL && !flag)
        {

            if (tmpnem->B.bulletpos.y == next.y && tmpnem->B.bulletpos.x == next.x)
            {
                flag = true;
                this->placeObject(now, empty);
                P.bulletRemove(b);
                this->placeObject(next, empty);
                this->bullet_enemyRemove(tmpnem->B);
            }
            tmpnem = tmpnem->next;
        }
    }
    else if (nextP == 'P') // PROIETTILE -> POTERE
    {
        chtype nextA = checkNextPos(next, b.direction);
        pos posNextA = nextPos(next, b.direction); // pos after power

        if (nextA == 'C' || nextA == 'R' || nextA == '$' || nextA == '%')
        {                                                                                                                                                             // PROIETTILE -> POTERE -> ARTEFATTO
            chtype nextB = checkNextPos(posNextA, b.direction);                                                                                                       // chtype dopo artefatto
            pos posNextB = nextPos(posNextA, b.direction);                                                                                                            // pos dopo artef, tre posti dopo bull
            if (nextB == ACS_VLINE || nextB == ACS_HLINE || nextB == ACS_CKBOARD || nextB == ACS_RTEE || nextB == ACS_LTEE || nextB == ACS_BTEE || nextB == ACS_TTEE) // PROIETTILE ->POTERE -> ARTEF -> MURO
            {

                placeObject(now, empty);
                P.bulletRemove(b);
            }
            else if (nextB == empty) // PROIETTILE -> POTERE -> ARTEFATTO -> SPAZIO VUOTO
            {
                placeObject(now, empty);
                placeObject(posNextB, ACS_BULLET);
                b.bulletpos = posNextB;
            }
        }
        else if (nextA == empty)
        {
            placeObject(now, empty);
            placeObject(posNextA, ACS_BULLET);
            b.bulletpos = posNextA;
        }
        else if (nextA == ACS_VLINE || nextA == ACS_HLINE || nextA == ACS_CKBOARD || nextA == ACS_RTEE || nextA == ACS_LTEE || nextA == ACS_BTEE || nextA == ACS_TTEE) // PROIETTILE -> POTERE -> MURO
        {                                                                                                                                                              // dopo proiettile e dopo potere c'è muro, faccio sparire proiettile
            placeObject(now, empty);                                                                                                                                   // rimuove bullet da posizione attuale
            P.bulletRemove(b);                                                                                                                                         // rimuove bullet dalla lista
        }
    }
    else if (nextP == empty)
    {

        if (next.y == 0 || next.y == 29)
        {
            if (next.x == 50)
            {
                Room::placeObject(now, empty);
                P.bulletRemove(b);
            }
        }
        else
        {
            placeObject(now, empty);
            placeObject(next, ACS_BULLET);
            b.bulletpos = next;
        }
        Room::drawLook();
        wrefresh(Room::getWindow());
        refresh();
    }
}

// manages all ally bullets

void Room::allABullMov(Protagonist &p)
{
    p_bulletlist tmp = p.getHeadB();

    while (tmp != NULL)
    {
        aBullMov(p, tmp->B);
        tmp = tmp->next;
    }
}

// power head insert
void Room::powerHeadinsert(Power p)
{
    p_powersList newpow = new powersList;
    newpow->P = p;
    newpow->next = this->objects.powers;
    this->objects.powers = newpow;
}

// powers remove
void Room::removePower(chtype tag, pos position)
{
    p_powersList x;
    p_powersList tmp;
    bool found = false;
    if (this->objects.powers == NULL)
    {
        this->objects.powers = this->objects.powers;
    }
    else if (this->objects.powers->P.get_tag() == tag && this->objects.powers->P.getPosition().x == position.x && this->objects.powers->P.getPosition().x == position.y)
    {
        tmp = this->objects.powers;
        this->objects.powers = this->objects.powers->next;
        delete tmp;
    }
    else
    {
        x = this->objects.powers;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->P.get_tag() == tag && x->next->P.getPosition().x == position.x && x->next->P.getPosition().y == position.y)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
}

// artifact head insert
void Room::ArtifactHeadinsert(Artifact a)
{
    p_artifactsList newart = new artifactsList;
    newart->A = a;
    newart->next = this->objects.artifacts;
    this->objects.artifacts = newart;
}

// artifactslist remove
void Room::removeArtifact(Artifact a)
{
    p_artifactsList x;
    p_artifactsList tmp;
    bool found = false;
    if (this->objects.artifacts == NULL)
    {
        this->objects.artifacts = this->objects.artifacts;
    }
    else if (this->objects.artifacts->A.get_tag() == a.get_tag() && this->objects.artifacts->A.getPosition().x == a.getPosition().x && this->objects.artifacts->A.getPosition().x == a.getPosition().y)
    {
        tmp = this->objects.artifacts;
        this->objects.artifacts = this->objects.artifacts->next;
        delete tmp;
    }
    else
    {
        x = this->objects.artifacts;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->A.get_tag() == a.get_tag() && x->next->A.getPosition().x == a.getPosition().x && x->next->A.getPosition().y == a.getPosition().y)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
}

// makes the player move
void Room::ProtagonistMovement(Protagonist &p, int direction)
{

    pos currentpos = p.getPosition();
    pos newPos = Room::nextPos(currentpos, direction);

    if (Room::getTile(newPos) == ' ')
    {
        Room::placeObject(currentpos, ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.get_tag());
    }
    else if (Room::getTile(newPos) == 'C' || Room::getTile(newPos) == 'R' || Room::getTile(newPos) == '$' || Room::getTile(newPos) == '%') // hits artifact
    {

        p_artifactsList tmp = this->objects.artifacts;
        while (tmp != NULL)
        {
            if (tmp->A.getPosition().y == newPos.y && tmp->A.getPosition().x == newPos.x)
            {
                p.gainLife(tmp->A.getLifepoints());
                Room::removeArtifact(tmp->A);
            }
            tmp = tmp->next;
        }

        Room::placeObject(currentpos, ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.get_tag());
    }
    else if (Room::getTile(newPos) == 'P') // hits power
    {
        removePower('P', newPos);
        Room::placeObject(p.getPosition(), ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.get_tag());
        Room::openDoors(true);
        Room::placeArtifacts();
    }
    else if (Room::getTile(newPos) == ACS_DEGREE) // hits enemy bullet
    {
        p_bulletsEnemies tmp1 = this->objects.bulletEnemies;
        // p_bulletlist tmp2 = p.getHeadB();
        while (tmp1 != NULL)
        {
            if (tmp1->B.bulletpos.y == newPos.y && tmp1->B.bulletpos.x == newPos.x)
            {

                Room::placeObject(tmp1->B.bulletpos, ' ');
                bool dead = p.takeDamage(tmp1->B.bullet_damage);
                if (dead == true)
                {
                    p.setisAlive(FALSE);
                    Room::placeObject(p.getPosition(), ' ');
                }
                else
                {

                    bullet_enemyRemove(tmp1->B);
                }
            }

            tmp1 = tmp1->next;
        }
    }
    else if (Room::getTile(newPos) == ACS_BULLET) // hits ally bullet
    {
        p_bulletlist tmp2 = p.getHeadB();
        bool done = false;
        while (tmp2 != NULL && !done)
        {
            if (tmp2->B.bulletpos.y == newPos.y && tmp2->B.bulletpos.x == newPos.x)
            {
                p.bulletRemove(tmp2->B);
                Room::placeObject(p.getPosition(), ' ');
                p.setPosition(newPos.y, newPos.x);
                Room::placeObject(p.getPosition(), p.get_tag());
                done = true;
            }

            tmp2 = tmp2->next;
        }
    }
    else if (Room::getTile(newPos) == ACS_NEQUAL || Room::getTile(newPos) == ACS_BLOCK || Room::getTile(newPos) == '@') // hits enemy
    {
        p.takeDamage(p.getLife());
        p.setisAlive(FALSE);
        Room::placeObject(p.getPosition(), ' ');
    }
}

void Room::enBullHeadInsert(bullet b)
{

    p_bulletsEnemies newbullet = new bulletsEnemies;
    newbullet->B = b;
    newbullet->next = this->objects.bulletEnemies;
    this->objects.bulletEnemies = newbullet;
}

void Room::HeadInsert_enemy(Enemy en)
{

    pListEnemies newEnemy = new listEnemies;
    newEnemy->e = en;
    newEnemy->next = this->objects.enemies;
    this->objects.enemies = newEnemy;
}

void Room::bullet_enemyRemove(bullet b)
{
    p_bulletsEnemies x;
    p_bulletsEnemies tmp;
    bool found = false;
    if (this->objects.bulletEnemies == NULL)
    {
        this->objects.bulletEnemies = this->objects.bulletEnemies;
    }
    else if (this->objects.bulletEnemies->B.bullet_damage == b.bullet_damage && this->objects.bulletEnemies->B.bullet_tag == b.bullet_tag && this->objects.bulletEnemies->B.bulletpos.x == b.bulletpos.x && this->objects.bulletEnemies->B.bulletpos.y == b.bulletpos.y && this->objects.bulletEnemies->B.direction == b.direction)
    {
        tmp = this->objects.bulletEnemies;
        this->objects.bulletEnemies = this->objects.bulletEnemies->next;
        delete tmp;
    }
    else
    {
        x = this->objects.bulletEnemies;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->B.bullet_damage == b.bullet_damage && x->next->B.bullet_tag == b.bullet_tag && x->next->B.bulletpos.x == b.bulletpos.x && x->next->B.bulletpos.y == b.bulletpos.y && x->next->B.direction == b.direction)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
}

void Room::enemyRemove(Enemy en)
{
    pListEnemies x;
    pListEnemies tmp;
    bool found = false;
    if (this->objects.enemies == NULL)
    {
        this->objects.enemies = this->objects.enemies;
    }
    else if (this->objects.enemies->e.get_enemyKey() == en.get_enemyKey() && this->objects.enemies->e.getPosition().y == en.getPosition().y && this->objects.enemies->e.getPosition().x == en.getPosition().x && this->objects.enemies->e.get_tag() == en.get_tag())
    {
        tmp = this->objects.enemies;
        this->objects.enemies = this->objects.enemies->next;
        delete tmp;
    }
    else
    {
        x = this->objects.enemies;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->e.get_enemyKey() == en.get_enemyKey() && x->next->e.getPosition().y == en.getPosition().y && x->next->e.getPosition().x == en.getPosition().x && x->next->e.get_tag() == en.get_tag())
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
}

void Room::enemy_movement(Protagonist &P, Enemy &e, int dir)
{
    pos now = e.getPosition();
    chtype c_next = checkNextPos(now, dir);
    pos next = nextPos(now, dir);
    if (c_next == ' ')
    {
        Room::placeObject(next, e.get_tag());
        Room::placeObject(now, ' ');
        e.setPosition(next.y, next.x);
    }
    else if (c_next == ACS_PI)
    {
        P.takeDamage(P.getLife());
        P.setisAlive(FALSE);
        Room::placeObject(now, ' ');
        Room::placeObject(next, e.get_tag());
        e.setPosition(next.y, next.x);
    }
    /*else if (c_next == ACS_BULLET)
    {
        p_bulletlist tmp = P.getHeadB();

        while (tmp != NULL)
        {
            if (tmp->B.bulletpos.x == next.x && tmp->B.bulletpos.x == next.x)
            {
                P.set_score(e.get_score());
                P.bulletRemove(tmp->B);
                Room::enemyRemove(e);
                Room::placeObject(now, ' ');
                Room::placeObject(next, ' ');
            }
            tmp = tmp->next;
        }
    }*/

    else if (c_next == ACS_DEGREE)
    {
        p_bulletsEnemies tmp_en = this->objects.bulletEnemies;
        while (tmp_en != NULL)
        {
            if (tmp_en->B.bulletpos.x == next.x && tmp_en->B.bulletpos.y == next.y)
            {
                bullet_enemyRemove(tmp_en->B);
                placeObject(now, ' ');
                placeObject(next, e.get_tag());
                e.setPosition(next.y, next.x);
            }
            tmp_en = tmp_en->next;
        }
    }
};

void Room::allEnemyMov(Protagonist &p)
{
    // prendi lista nemici
    pListEnemies entmp = this->objects.enemies;

    // scorri lista nemici
    while (entmp != NULL)
    {
        int direction = rand() % 4;

        if (entmp->e.get_enemyKey() != 1)
        {
            enemy_movement(p, entmp->e, direction);
        }

        entmp = entmp->next;
    }
}

// da rivedere
void Room::spawnEnBull()
{
    int n = rand() % 3;
    if (n == 1)
    {
        pListEnemies en_tmp = objects.enemies;
        bullet b;
        b.direction = rand() % 4;
        b.bullet_tag = ACS_DEGREE;

        while (en_tmp != NULL)
        {
            if (en_tmp->e.get_enemyKey() != 2)
            {
                switch (en_tmp->e.get_enemyKey())
                {
                case 1:
                    b.bullet_damage = 2;
                    break;
                case 3:
                    b.bullet_damage = 3;
                    break;
                default:
                    break;
                }
                pos now = en_tmp->e.getPosition();
                chtype c_next = checkNextPos(now, b.direction);
                pos next = nextPos(now, b.direction);
                if (c_next == ' ')
                {
                    b.bulletpos = next;
                    placeObject(b.bulletpos, b.bullet_tag);
                    enBullHeadInsert(b);
                }
            }
            en_tmp = en_tmp->next;
        }
    }
}

void Room::enBullet_move(bullet &b, Protagonist &p)
{

    pos now = b.bulletpos;
    pos next = nextPos(now, b.direction);
    chtype c_next = checkNextPos(now, b.direction);
    if (c_next == ' ')
    {
        placeObject(now, ' ');
        placeObject(next, b.bullet_tag);
        b.bulletpos = next;
    }
    else if (c_next == ACS_PI) // il proiettile incontra il player
    {
        placeObject(now, ' ');
        bool dead = p.takeDamage(b.bullet_damage);
        if (dead == true)
        {
            p.setisAlive(FALSE);
            placeObject(p.getPosition(), ' ');
        }
        else
        {
            bullet_enemyRemove(b);
        }
    }
    else if (c_next == ACS_VLINE || c_next == ACS_HLINE || c_next == ACS_CKBOARD || c_next == ACS_RTEE || c_next == ACS_LTEE || c_next == ACS_BTEE || c_next == ACS_TTEE) // COLLISIONI PROIETTILE-MURO
    {
        // cancello il proiettile e lo rimuovo dalla lista
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    // non ci sono collisioni tra i proiettili del nemico e i poteri

    else if (c_next == 'C' || c_next == 'R' || c_next == '$' || c_next == '%') // COLLISIONE PROIETTILE-ARTEFATTO
    {
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    else if (c_next == ACS_BLOCK || c_next == ACS_NEQUAL || c_next == '@') // COLLISIONE PRIOETTILE NEMICO
    {
        // cancello il proiettile e lo rimuovo dalla lista
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    // COLLISIONE PROIETTILE - PROIETTILE
    // da rivedere
    /*
    else if (c_next == ACS_BULLET)
    {
        p_bulletlist tmp = p.getHeadB();
        bool flag = false;

        while (tmp != NULL && !flag)
        {
            if (tmp->B.bulletpos.x == next.x && tmp->B.bulletpos.y == next.y)
            {
                flag = true;
                this->placeObject(now, ' ');
                this->bullet_enemyRemove(b);
                this->placeObject(next, ' ');
                p.bulletRemove(tmp->B);

                //his->drawLook();
                //wrefresh(this->getWindow());
                //refresh();

            }
        }
    }
    */
    else if (c_next == ACS_DEGREE) // collisione col proiettile nemico
    {
        p_bulletsEnemies tmpEn = this->objects.bulletEnemies;
        bool control = false;
        while (tmpEn != NULL && !control)
        {
            if (tmpEn->B.bulletpos.x == next.x && tmpEn->B.bulletpos.y == next.y)
            {
                control = true;
                placeObject(next, ' ');
                bullet_enemyRemove(tmpEn->B);
                placeObject(now, ' ');
                bullet_enemyRemove(b);
            }
            tmpEn = tmpEn->next;
        }
    }
}

void Room::allEnBullet_move(Protagonist &p)
{

    p_bulletsEnemies enBulltmp = objects.bulletEnemies;
    while (enBulltmp != NULL)
    {
        enBullet_move(enBulltmp->B, p);
        enBulltmp = enBulltmp->next;
    }
}

// spawns allybullets right next to the player
void Room::spawnAllyBullet(Protagonist &p, int dir)
{
    bullet b;
    b.bullet_tag = ACS_BULLET;
    b.direction = dir;
    pos newpos;
    pListEnemies tmpenList = NULL;
    switch (b.direction)
    {
    case 0:
        newpos.y = p.getPosition().y + 1;
        newpos.x = p.getPosition().x;

        if (Room::getTile(newpos) == ACS_BLOCK || Room::getTile(newpos) == ACS_NEQUAL || Room::getTile(newpos) == '@')
        {
            tmpenList = this->objects.enemies;
            while (tmpenList != NULL)
            {
                if (newpos.x == tmpenList->e.getPosition().x && newpos.y == tmpenList->e.getPosition().y)
                {
                    p.set_score(tmpenList->e.get_score());
                    this->enemyRemove(tmpenList->e);
                    this->placeObject(newpos, ' '); // rimuovo en da mappa
                }
                tmpenList = tmpenList->next;
            }
        }
        else if (Room::getTile(newpos) == ' ')
        {
            if (newpos.y != 29)
            {
                b.bulletpos.y = p.getPosition().y + 1;
                b.bulletpos.x = p.getPosition().x;
                Room::placeObject(b.bulletpos, b.bullet_tag);
                p.bulletHeadInsert(b);
            }
            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }

        break;

    case 1:
        newpos.y = p.getPosition().y;
        newpos.x = p.getPosition().x - 1;

        if (Room::getTile(newpos) == ACS_BLOCK || Room::getTile(newpos) == ACS_NEQUAL || Room::getTile(newpos) == '@')
        {
            tmpenList = this->objects.enemies;
            while (tmpenList != NULL)
            {
                if (newpos.x == tmpenList->e.getPosition().x && newpos.y == tmpenList->e.getPosition().y)
                {
                    p.set_score(tmpenList->e.get_score());
                    this->enemyRemove(tmpenList->e);
                    this->placeObject(newpos, ' '); // rimuovo en da mappa
                }
                tmpenList = tmpenList->next;
            }
        }
        else if (Room::getTile(newpos) == ' ')
        {

            b.bulletpos.y = p.getPosition().y;
            b.bulletpos.x = p.getPosition().x - 1;
            Room::placeObject(b.bulletpos, b.bullet_tag);
            p.bulletHeadInsert(b);
            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }

        break;
    case 2:

        newpos.y = p.getPosition().y - 1;
        newpos.x = p.getPosition().x;

        if (Room::getTile(newpos) == ACS_BLOCK || Room::getTile(newpos) == ACS_NEQUAL || Room::getTile(newpos) == '@')
        {
            tmpenList = this->objects.enemies;
            while (tmpenList != NULL)
            {
                if (newpos.x == tmpenList->e.getPosition().x && newpos.y == tmpenList->e.getPosition().y)
                {
                    p.set_score(tmpenList->e.get_score());
                    this->enemyRemove(tmpenList->e);
                    this->placeObject(newpos, ' '); // rimuovo en da mappa
                }
                tmpenList = tmpenList->next;
            }
        }
        else if (Room::getTile(newpos) == ' ')
        {
            if (newpos.y != 0)
            {
                b.bulletpos.y = p.getPosition().y - 1;
                b.bulletpos.x = p.getPosition().x;
                Room::placeObject(b.bulletpos, b.bullet_tag);
                p.bulletHeadInsert(b);
            }

            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }

        break;

    case 3:

        newpos.y = p.getPosition().y;
        newpos.x = p.getPosition().x + 1;

        if (Room::getTile(newpos) == ACS_BLOCK || Room::getTile(newpos) == ACS_NEQUAL || Room::getTile(newpos) == '@')
        {
            tmpenList = this->objects.enemies;
            while (tmpenList != NULL)
            {
                if (newpos.x == tmpenList->e.getPosition().x && newpos.y == tmpenList->e.getPosition().y)
                {
                    p.set_score(tmpenList->e.get_score());
                    this->enemyRemove(tmpenList->e);
                    this->placeObject(newpos, ' '); // rimuovo en da mappa
                }
                tmpenList = tmpenList->next;
            }
        }
        else if (Room::getTile(newpos) == ' ')
        {

            b.bulletpos.y = p.getPosition().y;
            b.bulletpos.x = p.getPosition().x + 1;
            Room::placeObject(b.bulletpos, b.bullet_tag);
            p.bulletHeadInsert(b);
            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }
    default:
        break;
    }
}
