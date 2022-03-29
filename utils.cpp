#include "header/MyString.hpp"

// custom itoa, converts int to const char *
const char *itoa(int num)
{
    MyString str = MyString();
    bool isNeg = false;
    if (num < 0)
    {
        isNeg = true;
        num *= -1;
    }

    if (num == 0)
        str.append('0');

    for (int i = 0; num > 0; i++)
    {
        char c = '0' + num % 10;
        str.append(c);
        num = num / 10;
    }

    if (isNeg)
        str.append('-');

    str.reverse();

    return str.get();
}