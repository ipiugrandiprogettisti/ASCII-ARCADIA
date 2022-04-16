
// max length of item string
const int MAX_LENGTH_ITEM = 20;

// print main menu, sel is selected item to highlight
void printMenu(int sel, int totItems, char menuItems[][MAX_LENGTH_ITEM]);

/*
draw the main menu and returns choice taken by user:
- 0: Play
- 1: Credits
- 2: Exit
*/
int getMenu(WINDOW *myWin);

// starts the game
void startGame(WINDOW *myWin);
