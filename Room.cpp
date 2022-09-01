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
        // this->look[doorInfo.y][doorInfo.x - 1] = ACS_RTEE;
        this->placeObject(doorInfo.y, doorInfo.x - 1, ACS_RTEE);
        // this->look[doorInfo.y][doorInfo.x + 1] = ACS_LTEE;
        this->placeObject(doorInfo.y, doorInfo.x + 1, ACS_LTEE);
        break;
    case 1: // left side
    case 3: // rigth side
        // this->look[doorInfo.y - 1][doorInfo.x] = ACS_BTEE;
        this->placeObject(doorInfo.y - 1, doorInfo.x, ACS_BTEE);
        // this->look[doorInfo.y + 1][doorInfo.x] = ACS_TTEE;
        this->placeObject(doorInfo.y + 1, doorInfo.x, ACS_TTEE);
        break;
    default:
        break;
    }

    if (doorInfo.isOpen == false)
        // this->look[doorInfo.y][doorInfo.x] = doorInfo.tile.close;
        this->placeObject(doorInfo.y, doorInfo.x, doorInfo.tile.close);
    else
        // this->look[doorInfo.y][doorInfo.x] = doorInfo.tile.open;
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
    p.tag = 'P';
    chtype rar = p.tag;
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
};

// places artifacts
void Room::placeArtifacts()
{
    Artifact a(0, 0, 2, 2, ' ');
    int nArt = rand() % 3;
    for (int i = 0; i < nArt; i++)
    {
        chtype chflag;
        do
        {
            a.position.x = rand() % HEIGTH;
            a.position.y = rand() % WIDTH;
            pos flag;
            flag.x = a.position.x;
            flag.y = a.position.y;
            chflag = this->getTile(flag);
        } while (chflag != ' ');

        int artRarity = rand() % 100 + 1;

        if (artRarity <= 60 && artRarity > 0)
        {
            a.tag = 'C';
            a.rarity = 1;
            a.lifepoints = 1;
        }
        else if (artRarity > 60 && artRarity <= 85)
        {
            a.tag = 'R';
            a.rarity = 2;
            a.lifepoints = 3;
        }
        else if (artRarity > 85 && artRarity <= 95)
        {
            a.tag = '$';
            a.rarity = 3;
            a.lifepoints = 5;
        }
        else if (artRarity > 95 && artRarity >= 100)
        {
            a.tag = ACS_DIAMOND;
            a.rarity = 4;
            a.lifepoints = 7;
        }

        placeObject(a.position, a.tag);
    }
}
// places random enemies
void Room::place_enemies(bool b)
{

    Enemy en(0, 5, 5, 2, 0, 0, ' ');


    int n = rand() % 3 + 1;

    for (int i = 0; i < n; i++)
    {
        int n_type = rand() % 100 + 1;
        if (n_type <= 40)
        {
            en.tag = ACS_BLOCK;
            en.key = 1;
        }
        else if (n_type <= 80 && n_type >= 40)
        {
            en.tag = ACS_NEQUAL;
            en.key = 2;
        }
        else if (n_type <= 100 && n_type >= 80)
        {
            en.tag = '@';
            en.key = 3;
        }

        bool flag = true;
        pos posEnemy;
        chtype p = ' ';
        while (flag == true)
        {
            posEnemy.y = rand() % 24 + 3;
            posEnemy.x= rand() % 94 + 3;
            
            en.position = posEnemy;
            p = this->getTile(en.position);
            if (p == ' ')
            {
                this->placeObject(en.position, en.tag);
                this->drawLook();
                this->HeadInsert_enemy(en);
                flag = false;
            }
        }
    }

    // qui va funzione per aggiungere enemy en alla lista
}

// random path generator
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
            // this->look[tmp.y][tmp.x] = ACS_CKBOARD;
            this->placeObject(tmp, ACS_CKBOARD);
            previousPosition = tmp;
        }
    }
}

// aux function to place walls
/*void Room::createWall(int width, int heigth, int posY, int posX)
{
    for (int i = 0; i < heigth; i++)
    {
        for (int k = 0; k < width; k++)
        {
            pos position;
            position.y = i + posY, position.x = k + posX;

            // if (tileIsFree(position))
            //{
            placeObject(position, ACS_CKBOARD);
            freeRowCol(position);
            //}
            //else FIXME finire freeRowCol
          //  {
           //     freeRowCol(position);
           // }

            //if ((i == 0 || k == 0 || i == heigth - 1 || k == width - 1) || tileIsFree(position))
            //{
            //    placeObject(position, ACS_CKBOARD);
            //}
        }
    }
}*/

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

// returns the bool drawn
bool Room::getDrawn()
{
    return drawn;
}

// returns the object list of the room
struct objContainer Room::getObjectList()
{
    return objects;
}

// returns the given room's door information; if door doesn't exist returns a "-1" door (check struct door)
// isNextRoom= 1 se è la porta alla stanza successiva, =0 se dà sulla stanza precedente
struct door Room::getDoor(int isNextRoom)
{
    struct door myDoor;
    myDoor = doorInfo[isNextRoom];

    /*if (doorInfo[isNextRoom].x > -1 || doorInfo[isNextRoom].y > -1)
        myDoor = doorInfo[isNextRoom];*/

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
    // this->look[2][2] = (char)key + 48;       // debug info, prints room key
    // this->placeObject(2, 2, (char)key + 48); // debug info, prints room key

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

    // now we have to draw 1 to (4-1) doors (previous one is already placed)

    int prevDoorsNumber = 0;
    if (previousRoomExists)
        prevDoorsNumber = 1;

    // srand(4); // FIXME: seed casuale
    srand(time(0)); // seed is 0

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

        /*createWall(1, 1, offsetTOPBOTTOM, offsetSXDX);
        createWall(1, 1, 26, offsetSXDX);
        createWall(1, 1, offsetTOPBOTTOM, 93);
        createWall(1, 1, 26, 93);*/
        pos pos1;
        pos1.x = posX;
        pos1.y = posY;

        randomPathWall(pos1, h, w);
        // createWall(w, h, posY, posX);
    }

    // place artifacts

    // TODO: place player
    // TODO: place enemies
    // TODO:  place etc

    place_enemies(1);
    placeArtifacts();
    placePower(1);
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

    // testo future posizioni su posizione di prova
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
    // controllo collisione proiettili alleati
    p_bulletlist tmp = P.getHeadB(); // lista proiettili protagonista

    chtype empty = ' ';
    chtype nextP; // char in next position
    int dir = b.direction;

    pos now = b.bulletpos; // salvo posizione attuale
    // nextP = checkNextPos(now, b.direction);   // char in pos futura
    pos posNextP = nextPos(now, dir); // pos futura

    nextP = Room::getTile(posNextP);
    if (nextP == ACS_VLINE || nextP == ACS_HLINE || nextP == ACS_CKBOARD) // PROIETTILE -> MURO
    {
        placeObject(now, empty); // rimuove bullet da posizione attuale
        P.bulletRemove(tmp, b);  // rimuove bullet dalla lista
    }
    else if (nextP == 'C' || nextP == 'R' || nextP == '$' || nextP == ACS_STERLING) // PROIETTILE -> ARTEF
    {
        chtype nextA = checkNextPos(posNextP, dir);                           // chtype dopo artefatto //due posti dopo bull
        pos posNextA = nextPos(posNextP, dir);                                // posizione dopo Artefatto
        if (nextA == ACS_VLINE || nextA == ACS_HLINE || nextA == ACS_CKBOARD) // PROIETTILE -> ARTEF -> MURO
        {                                                                     // dopo proiettile e dopo artefatto c'è muro, faccio sparire proiettile
            placeObject(now, empty);                                          // rimuove bullet da posizione attuale
            P.bulletRemove(tmp, b);                                           // rimuove bullet dalla lista
        }
        else if (nextA == empty) // PROIETTILE -> ARTEF -> SPAZIO VUOTO
        {

            placeObject(now, empty);           // pos attuale cancello
            placeObject(posNextA, ACS_BULLET); // pos futura disegno
            b.bulletpos = posNextA;            // aggiorno posizione sulla lista
        }
        else if (nextA == 'P') // PROIETTILE -> ARTEF -> POTERE
        {
            chtype nextB = checkNextPos(posNextA, b.direction);                   // chtype dopo potere
            pos posNextB = nextPos(posNextA, b.direction);                        // pos dopo potere, tre posti dopo bull
            if (nextB == ACS_VLINE || nextB == ACS_HLINE || nextB == ACS_CKBOARD) // PROIETTILE -> ARTEF -> POTERE -> MURO
            {

                placeObject(now, empty); // rimuove bullet da posizione attuale
                P.bulletRemove(tmp, b);  // rimuove bullet dalla lista
            }
            else if (nextB == empty) // PROIETTILE -> ARTEF -> POTERE -> SPAZIO VUOTO
            {
                placeObject(now, empty);           // pos attuale cancello
                placeObject(posNextB, ACS_BULLET); // pos futura disegno
                b.bulletpos = posNextB;            // aggiorno posizione sulla lista
            }
        }
        Room::drawLook();
        refresh();
        wrefresh(this->getWindow());
        // NON CI SONO ALTRE COLLISIONI DELLA SERIE PROIETT -> ARTEF -> ALTRO PERCHè GLI ARTEFATTI SPAWNANO SOLO DOPO CHE I NEMICI SONO MORTI
    }
    else if (nextP == '@' || nextP == ACS_NEQUAL || nextP == ACS_BLOCK) // PROIETTILE -> NEMICO
    {
        // proiettili alleato tolgono solo parte della vita
        /*
        scorri lista nemici, trovi il nemico in pos nextP,
        controlli la vita, togli vita in base al proiettile,
        cancelli proiettile, cancelli nemico se finisce la vita
        */
    }
    else if (nextP == ACS_BULLET) // PROIETTILE -> PROETTILE NEMICO
    {
        // manca ancora lista proiettili nemici, ho usato lista proiett all, da cambiare
        int dirNem = 0;
        int dirAll = dir;
        p_bulletsEnemies tmpnem;
        /*
        bisogna capire la direzione del proiettile nemico
        se sono perpendicolari basta muovere di una posizione proiettile nemico
        e poi posizionare proiettile all

        se sono direzionati nella stessa retta sono diretti uno contro l'altro,
        non possono avere la stessa direzione
        in questo caso basta scambiarli di posizione
        */
        // scorro lista proiettili nemici per capire quale proiettile è in quella pos, e mi salvo la direzione
        while (tmpnem != NULL)
        {                                     // manca lista proiettili nemici
            pos posnem = tmpnem->B.bulletpos; // posizione del proiettile in lista che sto controllando
            if (posnem.y == posNextP.y && posnem.x == posNextP.x)
            {
                dirNem = tmpnem->B.direction;
                if (dirNem == dirAll + 2 || dirNem == dirAll - 2)
                { // direzione sulla stessa retta, stanno per scontrarsi frontalmente, scambio pos
                    // non serve cambire char, è lo stesso
                    tmpnem->B.bulletpos = now;
                    b.bulletpos = posNextP;
                }
                else if (dirNem == dirAll + 1 || dirNem == dirAll - 1 || dirNem == dirAll + 3 || dirNem == dirAll - 3)
                { // direzioni perpendicolari
                    pos nextPosEnemyBull = nextPos(posNextP, dirNem);
                    // devo fare funzione per controllare dove sta andando il proiettile nemico
                    tmpnem->B.bulletpos = nextPosEnemyBull;    // aggiorno posizione bullnem in lista
                    b.bulletpos = posNextP;                    // aggiorno posizione bullall in lista
                    placeObject(nextPosEnemyBull, ACS_BULLET); // disegno in prox pos
                    placeObject(now, empty);                   // cancello da vecchia pos
                }
            }
            tmpnem = tmpnem->next;
        }
    }
    else if (nextP == 'P') // PROIETTILE -> POTERE
    {
        chtype nextA = checkNextPos(posNextP, b.direction); // chtype dopo potere //due posti dopo bull
        pos posNextA = nextPos(posNextP, b.direction);      // posizione dopo potere

        if (nextA == 'C' || nextA == 'R' || nextA == '$' || nextA == ACS_STERLING)
        {                                                                         // PROIETTILE -> POTERE -> ARTEFATTO
            chtype nextB = checkNextPos(posNextA, b.direction);                   // chtype dopo artefatto
            pos posNextB = nextPos(posNextA, b.direction);                        // pos dopo artef, tre posti dopo bull
            if (nextB == ACS_VLINE || nextB == ACS_HLINE || nextB == ACS_CKBOARD) // PROIETTILE ->POTERE -> ARTEF -> MURO
            {
                // salvo proiettile del nodo attuale
                placeObject(now, empty); // rimuove bullet da posizione attuale
                P.bulletRemove(tmp, b);  // rimuove bullet dalla lista
            }
            else if (nextB == empty) // PROIETTILE -> POTERE -> ARTEFATTO -> SPAZIO VUOTO
            {
                placeObject(now, empty);           // pos attuale cancello
                placeObject(posNextB, ACS_BULLET); // pos futura disegno
                b.bulletpos = posNextB;            // aggiorno posizione sulla lista
            }
        }
        else if (nextA == empty)
        {
            placeObject(now, empty);           // pos attuale cancello
            placeObject(posNextA, ACS_BULLET); // pos futura disegno
            b.bulletpos = posNextA;            // aggiorno posizione sulla lista
        }
        else if (nextA == ACS_VLINE || nextA == ACS_HLINE || nextA == ACS_CKBOARD) // PROIETTILE -> POTERE -> MURO
        {                                                                          // dopo proiettile e dopo potere c'è muro, faccio sparire proiettile
            placeObject(now, empty);                                               // rimuove bullet da posizione attuale
            P.bulletRemove(tmp, b);                                                // rimuove bullet dalla lista
        }
    }
    else if (nextP == empty)
    { // se prossima pos è vuota aggiorno pos proiettile e lo piazzo

        placeObject(now, empty);
        placeObject(posNextP, ACS_BULLET);
        b.bulletpos = posNextP;
        Room::drawLook();
        wrefresh(Room::getWindow());
        refresh();
    }
}

// manages all ally bullets
// scorre tutta la lista di proiettili alleati e li muove di 1 pos
void Room::allABullMov(Protagonist &p)
{
    p_bulletlist tmp = p.getHeadB(); // testa d'appoggio per scorrere

    while (tmp != NULL)
    {
        aBullMov(p, tmp->B);
        tmp = tmp->next;
    }
}

// artifact head insert
p_artifactsList Room::ArtifactHeadinsert(p_artifactsList head, Artifact a)
{
    p_artifactsList newart = new artifactsList;
    newart->A = a;
    newart->next = head;
    head = newart;

    return head;
}

// artifactslist remove
p_artifactsList Room::removeArtifact(p_artifactsList head, chtype tag, pos position)
{
    p_artifactsList x;
    p_artifactsList tmp;
    bool found = false;
    if (head == NULL)
    {
        head = head;
    }
    else if (head->A.tag == tag && head->A.getPosition().x == position.x && head->A.getPosition().x == position.y)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    else
    {
        x = head;
        while (!found && (x != NULL) && (x->next != NULL))
        {
            if (x->next->A.tag == tag && x->next->A.getPosition().x == position.x && x->next->A.getPosition().y == position.y)
            {
                tmp = x->next;
                x->next = x->next->next;
                delete tmp;
                found = true;
            }
            x = x->next;
        }
    }
    return head;
}

// makes the player move
int Room::ProtagonistMovement(Protagonist &p, int direction)
{
    int flag = 0;
    pos currentpos = p.getPosition();
    pos newPos = Room::nextPos(currentpos, direction);

    if (Room::getTile(newPos) == ' ')
    {
        Room::placeObject(currentpos, ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.tag);
    }
    else if (Room::getTile(newPos) == 'C' || Room::getTile(newPos) == 'R' || Room::getTile(newPos) == '$' || Room::getTile(newPos) == ACS_STERLING) // hits artifact, the flag is set to 1
    {
        flag = 1;

        switch (Room::getTile(newPos))
        {
        case 'C':
            p.gainLife(1);
            Room::removeArtifact(this->objects.artifacts, 'C', newPos);
            break;
        case 'R':
            p.gainLife(3);
            Room::removeArtifact(this->objects.artifacts, 'R', newPos);
            break;
        case '$':
            p.gainLife(5);
            Room::removeArtifact(this->objects.artifacts, '$', newPos);
            break;
        case 'ACS_STERLING':
            p.gainLife(7);
            Room::removeArtifact(this->objects.artifacts, ACS_STERLING, newPos);
            break;

        default:
            break;
        }
        
        Room::placeObject(currentpos, ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.tag);
    }
    else if (Room::getTile(newPos) == 'P') // hits power, the flag is set to 2
    {
        Room::placeObject(p.getPosition(), ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::placeObject(p.getPosition(), p.tag);
        Room::openDoors(true);
        flag = 2;
    }
    /*else if (Room::getTile(newPos) == '-') // hits enemy bullet
    {
        p_bulletsEnemies tmp = this->objects.bulletEnemies;
        while (tmp != NULL)
        {
            if (tmp->B.direction == direction && tmp->B.bulletpos.y == newPos.y && tmp->B.bullet_damage.x == newPos.x)
            {

            }

            tmp = tmp->next;
        }
    }*/

    return flag;
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
    else if (this->objects.enemies->e.key == en.key && this->objects.enemies->e.current_life == en.current_life && this->objects.enemies->e.max_life == en.max_life && this->objects.enemies->e.atk_damage == en.atk_damage && this->objects.enemies->e.position.y == en.position.y && this->objects.enemies->e.position.x == en.position.x && this->objects.enemies->e.tag == en.tag)
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
            if (x->next->e.key == en.key && x->next->e.current_life == en.current_life && x->next->e.max_life == en.max_life && x->next->e.atk_damage == en.atk_damage && x->next->e.position.y == en.position.y && x->next->e.position.x == en.position.x && x->next->e.tag == en.tag)
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



    /* visto che il protagonista muore al contatto con un nemico bisogna semplicemnte mettere il menù di morte invece che sta roba
    else if (c_next == ACS_PI)
    {
        int life_now = P.current_life;
        life_now -= e.atk_damage;
        if (life_now <= 0)
        {
            // DA INSERIRE MENU' DI MORTE
        }
        if (life_now > 0)
        {
            chtype c_next2;
            pos next_2;
            do
            {
                int new_dir = rand() % 4;
                c_next2 = checkNextPos(next, new_dir);
                next_2 = nextPos(next, new_dir);
            } while (c_next2 != ' ');

            placeObject(next_2, e.tag);
            placeObject(next, ' ');
            e.position = next_2;
        }
    }
    */
   /*
    else if (c_next == ACS_BULLET)
    {
        // qui va aggiunto un controllo ma prima mi deve funzionare la parte dei proittili
        e.current_life -= P.atk_damage;
        if (e.current_life <= 0)
        {
            placeObject(e.position, ' ');
            enemyRemove(e);
            if (this->objects.enemies == NULL)
            {
                placePower(1);
                // richiamare spwan artifact
                // placeArtifacts(1);
                // openDoors(true);
            }
        }
    }
    */


void Room::allEnemyMov(Protagonist &p)
{
    // prendi lista nemici
    pListEnemies entmp = this->objects.enemies;

    // scorri lista nemici
    while (entmp != NULL)
    {
        int direction = rand() % 4;
        
        if (entmp->e.key != 1)
        {
            pos now = entmp->e.position;
            chtype c_next = checkNextPos(now, direction);
            pos next = nextPos(now, direction);
            if (c_next == ' ')
            {
            placeObject(next, entmp->e.tag);
            placeObject(now, ' ');
            entmp->e.position = next;
        } 
        }

        entmp = entmp->next;
    }
}

// one function for all independent movements (enemy, enemybull, allybull)
void Room::oneMove(Protagonist p)
{
    // ally bullets movement
    allABullMov(p);
    // all enemies movement
    allEnemyMov(p);

    // TO-DO
    // all enemy bullets movement
}

// da rivedere
void Room::spawnEnBull()
{
    pListEnemies en_tmp = objects.enemies;
    bullet b;
    b.direction = rand() % 4;

    while (en_tmp != NULL)
    {
        switch (en_tmp->e.key)
        {
        case 1:
            b.bullet_damage = 20;
            break;
        case 3:
            b.bullet_damage = 30;
            break;
        default:
            break;
        }

        pos now = en_tmp->e.position;
        chtype c_next = checkNextPos(now, b.direction);
        pos next = nextPos(now, b.direction);
        if (c_next == ' ')
        {
            b.bulletpos = next;
            this->placeObject(b.bulletpos, b.bullet_tag);
            this->enBullHeadInsert(b);
        }

        en_tmp = en_tmp->next;
    }

}

// da rivedere
void Room::enBullet_move(bullet b, Protagonist &p)
{
    pos now = b.bulletpos;
    pos next = nextPos(now, b.direction);
    chtype c_next = checkNextPos(now, b.direction);
    if (c_next == ' ')
    {
        placeObject(next, b.bullet_tag);
        placeObject(now, ' ');
        b.bulletpos = next;
    }
    if (c_next == ACS_PI) // se il proiettile incontra un nemico il priettile viene cancellato e il nemico perde i danni
    {
        int life_now = p.current_life;
        life_now -= b.bullet_damage;
        if (life_now <= 0)
        {
            // DA INSERIRE MENU' DI MORTE
        }
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    if (c_next == ACS_VLINE || c_next == ACS_HLINE || c_next == ACS_CKBOARD) // COLLISIONI PROIETTILE-MURO
    {
        // cancello il proiettile e lo rimuovo dalla lista
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    // non ci sono collisioni tra i proiettili del nemico e gli artefatti

    if (c_next == 'P') // COLLISIONE PROIETTILE-POTERE
    {
        pos next_P = nextPos(next, b.direction); // posizione dopo il potere
        chtype c_nextP = checkNextPos(next, b.direction);

        if (c_nextP == ' ') // dopo il potere c'è uno spazio vuoto
        {
            placeObject(now, ' ');
            placeObject(next_P, ACS_BULLET);
            b.bulletpos = next_P;
        }
        else if (c_nextP == ACS_VLINE || c_nextP == ACS_HLINE || c_nextP == ACS_CKBOARD) // dopo il potere c'è un muro
        {
            placeObject(now, ' ');
            bullet_enemyRemove(b);
        }
        else if (c_nextP == ACS_PI)
        {
            p.current_life -= b.bullet_damage;
            if (p.current_life <= 0)
            {
                // MENU' di MORTE
            }
            placeObject(now, ' ');
            bullet_enemyRemove(b);
        }
        else if (c_nextP == ACS_BLOCK || c_nextP == ACS_NEQUAL || c_nextP == '@')
        {
            placeObject(now, ' ');
            bullet_enemyRemove(b);
        }
    }
    if (c_next == ACS_BLOCK || c_next == ACS_NEQUAL || c_next == '@') // COLLISIONE PRIOETTILE NEMICO
    {
        // cancello il proiettile e lo rimuovo dalla lista
        placeObject(now, ' ');
        bullet_enemyRemove(b);
    }
    // COLLISIONE PROIETTILE - PROIETTILE
    // da rivedere
    if (c_next == ACS_BULLET)
    {
        p_bulletsEnemies tmpEn = objects.bulletEnemies;
        p_bulletlist tmp = p.getHeadB();
        bool flag = false;
        /*
        bisogna capire la direzione del proiettile nemico
        se sono perpendicolari basta muovere di una posizione proiettile nemico
        e poi posizionare proiettile all

        se sono direzionati nella stessa retta sono diretti uno contro l'altro,
        non possono avere la stessa direzione
        in questo caso basta scambiarli di posizione
        */
        // scorro lista proiettili nemici per capire quale proiettile è in quella pos, e mi salvo la direzione
        while (tmp != NULL)
        {

            if (tmp->B.bulletpos.x == next.x && tmp->B.bulletpos.y == next.y)
            {
                flag = true;
                if (tmp->B.direction == b.direction + 2 || tmp->B.direction == b.direction - 2)
                {
                    // direzione sulla stessa retta, stanno per scontrarsi frontalmente, scambio pos
                    tmp->B.bulletpos = now;
                    b.bulletpos = next;
                }
                else if (tmp->B.direction == b.direction + 1 || tmp->B.direction == b.direction - 1 || tmp->B.direction == b.direction + 3 || tmp->B.direction == b.direction - 3)
                { // direzioni perpendicolari
                    pos allyPos_next = nextPos(next, tmp->B.direction);
                    chtype c_allyPos = checkNextPos(next, tmp->B.direction);

                    if (c_allyPos == ' ')
                    {
                        tmp->B.bulletpos = allyPos_next;
                        b.bulletpos = next;
                        placeObject(allyPos_next, ACS_BULLET);
                        placeObject(now, ' ');
                    }
                    // manca il controllo con il potere
                    else
                    {
                        // rimuovo il proiettile alleato perchè ha fatto  collisione
                        placeObject(now, ' ');
                        p.bulletRemove(tmp, tmp->B);
                    }
                }
                tmp = tmp->next;
            }
        }
        if (flag == false) // vuol dire che il proiettile che ha incontrato era un altro proiettile nemico
        {
            // scambio anche nel caso di collisione PROIETTILE NEMICO-PROIETTILE NEMICO(?)
            // adesso ho messo di no poi al massimo si cambia
            while (tmpEn != NULL)
            {
                if (tmpEn->B.bulletpos.x == next.x && tmpEn->B.bulletpos.y == next.y)
                {
                    placeObject(next, ' ');
                    placeObject(now, ' ');
                    bullet_enemyRemove(b);
                    bullet_enemyRemove(tmpEn->B);
                }
                tmpEn = tmpEn->next;
            }
        }
    }
}

void Room::allEnBullet_move(Protagonist &p)
{
    p_bulletsEnemies enBulltmp = objects.bulletEnemies;
    while (enBulltmp != NULL)
    {
        bullet enB = enBulltmp->B;
        enBullet_move(enB, p);
        enBulltmp = enBulltmp->next;
    }
}
/*
void Room::spawnSXBul(Protagonist p)
{
    pos blletpos = p.createSXBul();
    placeObject(blletpos, ACS_BULLET);
};
*/

// spawns allybullets right next to the player
void Room::spawnAllyBullet(Protagonist &p, int dir)
{
    bullet b;
    b.direction = dir;
    pos newpos;
    switch (b.direction)
    {
    case 0:
        newpos.y = p.getPosition().y + 1;
        newpos.x = p.getPosition().x;
        if (Room::getTile(newpos) == ' ')
        {
            b.bulletpos.y = p.getPosition().y + 1;
            b.bulletpos.x = p.getPosition().x;
            Room::placeObject(b.bulletpos, b.bullet_tag);
            p.bulletHeadInsert(b);
            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }

        break;

    case 1:
        newpos.y = p.getPosition().y;
        newpos.x = p.getPosition().x - 1;
        if (Room::getTile(newpos) == ' ')
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
        if (Room::getTile(newpos) == ' ')
        {
            b.bulletpos.y = p.getPosition().y - 1;
            b.bulletpos.x = p.getPosition().x;
            Room::placeObject(b.bulletpos, b.bullet_tag);
            p.bulletHeadInsert(b);
            Room::drawLook();
            refresh();
            wrefresh(this->getWindow());
        }

        break;

    case 3:

        newpos.y = p.getPosition().y;
        newpos.x = p.getPosition().x + 1;
        if (Room::getTile(newpos) == ' ')
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