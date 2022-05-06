#include "MyString.hpp"
const int MIN_COLS = 110, MIN_LINES = 40;

// custom itoa, converts int to const char *
MyString itoa(int num);

// check if screen size is correct to play the game; 110x40
void checkScreen(int screenCols, int screenLines);

// check if color is supported by user's terminal
void checkColors();

