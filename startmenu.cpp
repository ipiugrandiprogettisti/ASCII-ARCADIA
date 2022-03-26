#include "header/startmenu.hpp"
/*
draw the main menu and returns choice taken by user:
- 0: Play
- 1: Credits
*/
int getMenu(int maxY, int maxX, int offY, int offX)
{
    const int MAX_ITEMS = 2,
              MIN_ITEMS = 0,
              MAX_LENGTH_ITEM = 20;
    int maxX = COLS, maxY = LINES, width, height, halfX, halfY;
    char string[MAX_ITEMS][MAX_LENGTH_ITEM] = {"Play", "Credits"};
    int selectedItem = 0; // could only be -1, 0 or 1. 0 is default

    WINDOW *myWin = newwin(maxY, maxX, offY, offX);
    wrefresh(myWin);
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();               /* Start color 			*/
    wbkgd(myWin, COLOR_PAIR(1)); // sets all window attribute
    wrefresh(myWin);
    // Activating color for one line
    /*
    attron(COLOR_PAIR(1));
    mvaddstr(startY, startY, "ciao a tutti");
    attroff(COLOR_PAIR(1));
    */
    // center string
    halfY = LINES / 2 - 1;
    halfX = COLS / 2 - 1;
    int padding = 0; // set padding between menu items when displayed
    for (int i = 0; i < MAX_ITEMS; i++)
    {

        // check if current item is the selected one, if it is like so print it glowly
        if (i == selectedItem)
        {
            attron(COLOR_PAIR(2));
            mvaddstr(halfY + padding, halfX, string[i]);
            attroff(COLOR_PAIR(2));
        }
        else
        {
            attron(COLOR_PAIR(1));
            mvaddstr(halfY + padding, halfX, string[i]);
            attroff(COLOR_PAIR(1));
        }
        padding += 3;
    }

    int ch; // pressed key
    MyString item = MyString();
    // KEYBOARD EVENT LISTENER
    while ((ch = getch()) != KEY_F(1)) // if F1 is pressed quit
    {
        switch (ch)
        {
        case KEY_UP:
            move(0, 0);
            clrtoeol();
            /*
            erase the current line to the right of the cursor,
            inclusive, to the end of the current line.
            Blanks created by erasure have the current background
            rendition (as set by wbkgdset) merged into them.
            */
            wrefresh(myWin);
            if (selectedItem + 1 > MAX_ITEMS - 1)
                selectedItem = MIN_ITEMS; // reset selectedItem to 0
            else
                selectedItem++;
            item.reset();
            item.append(itoa(selectedItem));
            addstr(item.get());
            break;

        case KEY_DOWN:
            move(0, 0);
            clrtoeol();
            wrefresh(myWin);
            if (selectedItem - 1 < MIN_ITEMS - 1)
                selectedItem = MAX_ITEMS; // reset selectedItem to 0
            else
                selectedItem--;

            item.reset();
            item.append(itoa(selectedItem));
            addstr(item.get());
            break;
        }
    }

    return selectedItem;
}