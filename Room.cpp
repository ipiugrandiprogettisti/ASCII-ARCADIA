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

// places random artifacts
void Room::placeArtifacts(bool b)
{

    int nArtifacts = rand() % 3; // possono essercene da 0 a 2
    for (int i = 0; i < nArtifacts; i++)
    {
        Artifact p;
        /*
        percentuali probabilità di spawn in base alla rarità
        COMMON 60%  RARE 25%  SPECIAL 10%  EPIC 5%
        */
        const int probability = 101;

        int r = rand() % probability;

        if (r < 61)
        {
            p.setArtifact(1);
        }
        else if (r > 60 && r < 86)
        {
            p.setArtifact(2);
        }
        else if (r > 85 && r < 96)
        {
            p.setArtifact(3);
        }
        else if (r > 95)
        {
            p.setArtifact(4);
        }
        chtype rar = p.tag; // tag artefatto
        chtype var = ' ';   // uso per controllare tag in posizione in cui voglio spawnare
        pos posArt;
        do
        {
            int posy = rand() % WIDTH + 1;
            int posx = rand() % HEIGTH + 1;
            posArt.y = posy;
            posArt.x = posx;
            var = getTile(posArt);
        } while (var != ' ');
        this->placeObject(posArt, rar);

        // qui va funzione per aggiungere artefatto alla lista

        //  this->drawLook();
    }
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
    } while (var != ' ');
    this->placeObject(posPow, rar);
};

// places random enemies
void Room::place_enemies(bool b)
{

    Enemy en(0, 5, 5, 2, 0, 0, ' ');

    int n;
    int n_enemies = rand() % 10 + 1;
    if (n_enemies <= 4)
    {
        n = 1;
    }
    else if (n_enemies >= 5 && n_enemies <= 7)
    {
        n = 2;
    }
    else if (n_enemies >= 8 && n_enemies <= 10)
    {
        n = 3;
    }

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
            int enemyy = rand() % WIDTH + 1;
            int enemyx = rand() % HEIGTH + 1;
            posEnemy.y = enemyy;
            posEnemy.x = enemyx;
            en.position.y = enemyy;
            en.position.x = enemyx;
            p = getTile(posEnemy);
            if (p == ' ')
            {
                this->placeObject(posEnemy, en.tag);
                this->drawLook();
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
    this->placeObject(2, 2, (char)key + 48); // debug info, prints room key

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
    const int MAXWALLS = 150;          // max number of walls in a room
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
    placeArtifacts(1);
    place_enemies(1);
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

    return next;
};
// manages one ally bullet collision and movement
void Room::aBullMov(Protagonist P, bullet b)
{
    // controllo collisione proiettili alleati
    p_bulletlist tmp = P.headB; // lista proiettili protagonista

    chtype empty = ' ';
    chtype nextP;

    pos now = b.bulletpos;                                                // salvo posizione attuale
    nextP = checkNextPos(now, b.direction);                               // char in pos futura
    pos posNextP = nextPos(now, b.direction);                             // pos futura
    if (nextP == ACS_VLINE || nextP == ACS_HLINE || nextP == ACS_CKBOARD) // PROIETTILE -> MURO
    {
        placeObject(now, empty); // rimuove bullet da posizione attuale
        P.bulletRemove(tmp, b);  // rimuove bullet dalla lista
    }
    else if (nextP == 'C' || nextP == 'R' || nextP == '$' || nextP == ACS_STERLING) // PROIETTILE -> ARTEF
    {
        chtype nextA = checkNextPos(posNextP, b.direction);                   // chtype dopo artefatto //due posti dopo bull
        pos posNextA = nextPos(posNextP, b.direction);                        // posizione dopo Artefatto
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
        int dirAll = b.direction;
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
        b.bulletpos = posNextP;
        placeObject(now, empty);
        placeObject(posNextP, ACS_BULLET);
    }
}

// manages all ally bullets
// scorre tutta la lista di proiettili alleati e li muove di 1 pos
void Room::allABullMov(Protagonist p)
{
    p_bulletlist tmp = p.headB; // testa d'appoggio per scorrere

    while (tmp != NULL)
    {
        bullet b = tmp->B;
        aBullMov(p, b);
        tmp = tmp->next;
    }
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
void Room::ProtagonistMovement(Protagonist p, int direction)
{
    pos currentpos = p.position;
    pos newPos = Room::nextPos(p.position, direction);
    if (Room::getTile(newPos) == ' ')
    {
        Room::placeObject(p.position, ' ');
        p.setPosition(newPos.y, newPos.x);
        Room::drawLook();
    }
    else if (Room::getTile(newPos) == 'C')
    {
        /* code */
    }
}

p_bulletsEnemies Room::enBullHeadInsert(p_bulletsEnemies head, bullet b)
{

    p_bulletsEnemies newbullet = new bulletsEnemies;
    newbullet->B = b;
    newbullet->next = head;
    head = newbullet;

    return head;
}

pListEnemies Room::HeadInsert_enemy(pListEnemies head, Enemy en)
{

    pListEnemies newEnemy = new listEnemies;
    newEnemy->e = en;
    newEnemy->next = head;
    head = newEnemy;

    return head;
}

p_bulletsEnemies Room::bullet_enemyRemove(p_bulletsEnemies head, bullet b)
{
    p_bulletsEnemies x;
    p_bulletsEnemies tmp;
    bool found = false;
    if (head == NULL)
    {
        head = head;
    }
    else if (head->B.bullet_damage == b.bullet_damage && head->B.bullet_tag == b.bullet_tag && head->B.bulletpos.x == b.bulletpos.x && head->B.bulletpos.y == b.bulletpos.y && head->B.direction == b.direction)
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
    return head;
}

pListEnemies Room::enemyRemove(pListEnemies head, Enemy en)
{
    pListEnemies x;
    pListEnemies tmp;
    bool found = false;
    if (head == NULL)
    {
        head = head;
    }
    else if (head->e.key == en.key && head->e.current_life == en.current_life && head->e.max_life == en.max_life && head->e.atk_damage == en.atk_damage && head->e.position.y == en.position.y && head->e.position.x == en.position.x && head->e.tag == en.tag)
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
    return head;
}

void Room::enemy_movement(Enemy e, Protagonist P)
{
    int direction = rand() % 4; // 0 dwn, 1 sx , 2 up, 3 dx
    pos now = e.position;
    chtype c_next = checkNextPos(now, direction);
    pos next = nextPos(now, direction);
    if (c_next == ' ')
    {
        placeObject(next, e.tag);
        placeObject(now, ' ');
        e.position = next;
    }
    if (c_next == ACS_PI)
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
}

void Room::allEnemyMov(Protagonist p)
{
    // prendi lista nemici
    pListEnemies entmp = objects.enemies;

    // scorri lista nemici
    while (entmp != NULL)
    {
        Enemy ee = entmp->e;
        enemy_movement(ee, p);
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