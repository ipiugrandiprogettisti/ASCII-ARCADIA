
#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

// Custom string class
class MyString
{
public:
    char *string;
    int length = 0;

public:
    MyString();

    MyString(char const *text);

    // append string
    void append(char const *text);

    // append char
    void append(char ch);

    // reverse string
    void reverse();

    // reset string to "\0"
    void reset();

    // returns string length, does not count '\0'
    int getLength();

    // returns string
    const char *get();
};
