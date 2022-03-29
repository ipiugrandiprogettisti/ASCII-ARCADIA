const int NAME_LENGTH = 10;
struct listArtifacts
{
    Key key;
    char name[NAME_LENGTH];
    listArtifacts *next;
    listArtifacts *prev;
};

struct listEnemies
{
    Key key;
    char name[NAME_LENGTH];
    listEnemies *next;
    listEnemies *prev;
};

struct listObjects
{
    Key key;
    listEnemies mylistEnemies;
    listArtifacts myListArtifacts;
};

class Key
{
protected:
public:
    int number = -1;
    // ritorna il valore
    int get()
    {
        return number;
    }

    // Ritorna il valore number+1, univoco
    int createNew()
    {
        number += 1;
        return number;
    }
};

class Room
{
protected:
    Key key;                   // numero univoco
    listObjects mylistObjects; // all'interno c'è listEnemies listaTesori....

public:
    int getKey()
    {
        return key.get();
    }
    void init()
    {
        key.number = key.createNew();
    }
};

// listaStanze e listObjects sono collegate da una chiave univoca, ad esempio se voglio accedere alla lista della Room specifica
// il valore sarà la chiave comune ad entrambe

struct listaStanze
{
    Room room;
    Key key;
    listaStanze *door1;
    listaStanze *door2;
    listaStanze *door3;
    listaStanze *prev;
};

listaStanze createListStanze()
{
    // crea lista con key univoca
    Room room = room.init();
}

// make main
//  ./main