
#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

//Custom string class
class MyString
{
    char *data;      /*!< The ASCII characters that comprise the MyString */
    unsigned length; /*!< The number of characters allocated in data */

public:
    // Constructor
    MyString();

    // Constructor
    MyString(char c);

    // Constructor
    MyString(const char *c);

    // Constructor
    MyString(const MyString &s);

    // Deconstructor
    ~MyString();

    // Return length
    unsigned getLength() const;

    // Returns first index of the first char c it founds; -1 if not found
    int getIndex(char c) const;

    // Return current string
    const char *get();

    // Reverses string
    void reverse();

    // Resets string to "\0"
    void reset();

    // Sets uppercase letters from string[first] to string[last]
    void upperCase(unsigned first, unsigned last);

    // Sets lowercase letters from string[first] to string[last]
    void lowerCase(unsigned first, unsigned last);

    // Returns string[index]. throws 1 if index > length
    char operator[](unsigned index) const;
    // Returns string[index]. throws 1 if index > length
    char &operator[](unsigned index);

    // Sets string = "something"
    MyString &operator=(const MyString &string);
    // Appends string to string. string = "HellO "; string += "world"
    MyString &operator+=(const MyString &string);

    /*A friend function can access the private and protected data of a class*/

    // Concatenates lhs string with rhs string
    friend MyString operator+(const MyString &lhs, const MyString &rhs);
    // Concatenates lhs string with rhs string
    friend MyString operator+(const MyString &lhs, char rhs);
    // Concatenates lhs string with rhs string
    friend MyString operator+(const MyString &lhs, const char *rhs);
    // Concatenates lhs string with rhs string
    friend MyString operator+(char lhs, const MyString &rhs);
    // Concatenates lhs string with rhs string
    friend MyString operator+(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs == rhs
    friend bool operator==(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs == rhs
    friend bool operator==(const MyString &lhs, char rhs);
    // Returns (bool) lhs == rhs
    friend bool operator==(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs == rhs
    friend bool operator==(char lhs, const MyString &rhs);
    // Returns (bool) lhs == rhs
    friend bool operator==(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs != rhs
    friend bool operator!=(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs != rhs
    friend bool operator!=(const MyString &lhs, char rhs);
    // Returns (bool) lhs != rhs
    friend bool operator!=(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs != rhs
    friend bool operator!=(char lhs, const MyString &rhs);
    // Returns (bool) lhs != rhs
    friend bool operator!=(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs > rhs
    friend bool operator>(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs > rhs
    friend bool operator>(const MyString &lhs, char rhs);
    // Returns (bool) lhs > rhs
    friend bool operator>(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs > rhs
    friend bool operator>(char lhs, const MyString &rhs);
    // Returns (bool) lhs > rhs
    friend bool operator>(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs < rhs
    friend bool operator<(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs < rhs
    friend bool operator<(const MyString &lhs, char rhs);
    // Returns (bool) lhs < rhs
    friend bool operator<(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs < rhs
    friend bool operator<(char lhs, const MyString &rhs);
    // Returns (bool) lhs < rhs
    friend bool operator<(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs >= rhs
    friend bool operator>=(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs >= rhs
    friend bool operator>=(const MyString &lhs, char rhs);
    // Returns (bool) lhs >= rhs
    friend bool operator>=(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs >= rhs
    friend bool operator>=(char lhs, const MyString &rhs);
    // Returns (bool) lhs >= rhs
    friend bool operator>=(const char *lhs, const MyString &rhs);

    // Returns (bool) lhs <= rhs
    friend bool operator<=(const MyString &lhs, const MyString &rhs);
    // Returns (bool) lhs <= rhs
    friend bool operator<=(const MyString &lhs, char rhs);
    // Returns (bool) lhs <= rhs
    friend bool operator<=(const MyString &lhs, const char *rhs);
    // Returns (bool) lhs <= rhs
    friend bool operator<=(char lhs, const MyString &rhs);
    // Returns (bool) lhs <= rhs
    friend bool operator<=(const char *lhs, const MyString &rhs);
};
