class Key
{
protected:
    int number = -1;

public:
    int getNumber()
    {
        number += 1;
        return number;
    }

}
//prova 2

class Stanza
{
protected:
    Key key; // numero univoco
    listaOggetti; //all'interno c'è listaNemici listaTesori....

public:
    int getKey()
    {
        return key;
    }
    void init()
    {
        key = key.getNumber();
    }
}

#include <ncurses.h>

struct listaStanze
{
    Stanza stanza;
    listaStanze *porta1;
    listaStanze *porta2;
    listaStanze *porta3;
    listaStanze *prev;
};

listaStanze createListStanze()
{
    // crea lista con key univoca
    stanza = stanza.init();
}

main()
{
    listaStanze myLista createListStanze();

    WINDOW stanza1;
    initscr(g);

    /*initscr();                 /* Start curses mode 		  */
    // printw("Hello World !!!"); /* Print Hello World		  */
    // refresh();                 /* Print it on to the real screen */
    // getch();                   /* Wait for user input */
    // endwin();                  /* End curses mode		  */
    return 0;
}