# Progetto-programmazione

PREREQUISITI:
gcc, g++, ncurses, curses

ISTRUZIONI:
Per compilare:

- make main

Per eseguire:

- ./main

Per clean:

- make clean

Per compilare ed eseguire con un solo comando:

- make run

Idea stanze:

- le porte presenti dentro la classe Map si riferiscono al puntatore della prossima stanza (Room)
- le porte presenti dentro la classe Room si riferiscono esclusivamente ai tratti estetici/funzionali della porta
  - cioè dove è posizionata, se è aperta, ecc...

CARATTERI

Angoli muri: ACS_ULCORNER ACS_LLCORNER ACS_LRCORNER ACS_URCORNER
Protagonista: ACS_PI
Prioettile: ACS_BULLET
Artefatti: 'C' (common) 'R' (rare) '$' (special) ACS_STERLING (epic)
Nemici: '@' ACS_NEQUAL ACS_BLOCK
Muri dxsx: ACS_VLINE ACS_HLINE ACS_CKBOARD
Potere: 'P'

DIREZIONI

0 basso
1 sx
2 alto
3 dx
