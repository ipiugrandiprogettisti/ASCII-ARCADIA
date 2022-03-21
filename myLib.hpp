#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

// Custom string class
class MyString
{
public:
    char *string;

public:
    MyString();

    MyString(char const *text);

    // append string
    void append(char const *text);

    // returns string length, does not count '\0'
    int getLength();

    // returns string
    const char *get();
};

// return new window
WINDOW *newWindow(int height, int width, int starty, int startx);

// destroy the given window
void destroyWindow(WINDOW *localWindow);

/*
draw the main menu and returns choice taken by user:
-1: error
- 0: Play
- 1: Credits
*/
int getMenu(int maxY, int maxX, int offY, int offX);