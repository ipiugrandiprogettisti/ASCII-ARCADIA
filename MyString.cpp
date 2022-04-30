#include "header/MyString.hpp"

// Constructor
MyString::MyString()
{
    length = 0;
    data = new char[0];
}

// Constructor
MyString::MyString(char c)
{
    length = 1;
    data = new char(c);
}

// Constructor
MyString::MyString(const char *c)
{
    if (c)
    {
        unsigned n = 0;
        while (c[n] != '\0')
            n++;
        length = n;
        data = new char[n];
        for (unsigned j = 0; j < n; j++)
            data[j] = c[j];
    }
    else
    {
        length = 0;
        data = new char[0];
    }
}

// Constructor
MyString::MyString(const MyString &s)
{
    length = s.getLength();
    data = new char[length];
    for (unsigned j = 0; j < length; j++)
        data[j] = s[j];
}

// Deconstructor
MyString::~MyString()
{
    delete[] data;
}

unsigned MyString::getLength() const
{
    return length;
}

// Returns first index of the first char c it founds; -1 if not found
int MyString::getIndex(char c) const
{
    for (unsigned j = 0; j < length; j++)
        if (data[j] == c)
            return (int)j;
    return -1;
}

// Returns current string
const char *MyString::get()
{
    return data;
}

// Reverses string
void MyString::reverse()
{
    MyString tmp = data;
    int c = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        data[c] = tmp[i];
        c++;
    }
}

// Resets string
void MyString::reset()
{
    length = 0;
    data = new char[0];
}

// Sets uppercase letters from string[first] to string[last]
void MyString::upperCase(unsigned first, unsigned last)
{
    if ((first >= last) || (last > length))
        throw 1;

    for (unsigned j = first; j < last; j++)
        if ('a' <= data[j] && data[j] <= 'z')
            data[j] -= ('a' - 'A');
}

// Sets lowercase letters from string[first] to string[last]
void MyString::lowerCase(unsigned first, unsigned last)
{
    if ((first >= last) || (last > length))
        throw 1;

    for (unsigned j = first; j < last; j++)
        if ('A' <= data[j] && data[j] <= 'Z')
            data[j] += ('a' - 'A');
}

// Returns string[index]. throws 1 if index > length
char MyString::operator[](unsigned index) const
{
    if (index >= length)
        throw 1;
    return data[index];
}

// Returns string[index]. throws 1 if index > length
char &MyString::operator[](unsigned index)
{
    if (index >= length)
        throw 1;
    return data[index];
}

// Sets string = "something"
MyString &MyString::operator=(const MyString &string)
{
    if (this == &string)
        return *this;

    delete data;
    length = string.getLength();
    data = new char[length];
    for (unsigned j = 0; j < length; j++)
        data[j] = string[j];
    return *this;
}

// Appends string to string. string = "HellO "; string += "world"
MyString &MyString::operator+=(const MyString &string)
{
    unsigned len = length + string.getLength();
    char *str = new char[len];

    for (unsigned j = 0; j < length; j++)
        str[j] = data[j];

    for (unsigned i = 0; i < string.getLength(); i++)
        str[length + i] = string[i];

    delete data;
    length = len;
    data = str;
    return *this;
}

MyString operator+(const MyString &lhs, const MyString &rhs)
{
    return MyString(lhs) += rhs;
}

// Concatenates lhs string with rhs string
MyString operator+(const MyString &lhs, char rhs)
{
    return MyString(lhs) += MyString(rhs);
}

// Concatenates lhs string with rhs string
MyString operator+(const MyString &lhs, const char *rhs)
{
    return MyString(lhs) += MyString(rhs);
}

// Concatenates lhs string with rhs string
MyString operator+(char lhs, const MyString &rhs)
{
    return MyString(lhs) += rhs;
}
// Concatenates lhs string with rhs string
MyString operator+(const char *lhs, const MyString &rhs)
{
    return MyString(lhs) += rhs;
}

// Returns (bool) lhs == rhs
bool operator==(const MyString &lhs, const MyString &rhs)
{
    if (lhs.getLength() != rhs.getLength())
        return false;

    unsigned cap = lhs.getLength();
    unsigned n = 0;
    while ((n < cap) && (lhs[n] == rhs[n]))
        n++;
    return (n == cap);
}

// Returns (bool) lhs == rhs
bool operator==(const MyString &lhs, char rhs)
{
    return (lhs == MyString(rhs));
}

// Returns (bool) lhs == rhs
bool operator==(const MyString &lhs, const char *rhs)
{
    return (lhs == MyString(rhs));
}

// Returns (bool) lhs == rhs
bool operator==(char lhs, const MyString &rhs)
{
    return (MyString(lhs) == rhs);
}

// Returns (bool) lhs == rhs
bool operator==(const char *lhs, const MyString &rhs)
{
    return (MyString(lhs) == rhs);
}
// Returns (bool) lhs != rhs
bool operator!=(const MyString &lhs, const MyString &rhs)
{
    return !(lhs == rhs);
}

// Returns (bool) lhs != rhs
bool operator!=(const MyString &lhs, char rhs)
{
    return !(lhs == rhs);
}

// Returns (bool) lhs != rhs
bool operator!=(const MyString &lhs, const char *rhs)
{
    return !(lhs == rhs);
}

// Returns (bool) lhs != rhs
bool operator!=(char lhs, const MyString &rhs)
{
    return !(lhs == rhs);
}

// Returns (bool) lhs != rhs
bool operator!=(const char *lhs, const MyString &rhs)
{
    return !(lhs == rhs);
}

// Returns (bool) lhs > rhs
bool operator>(const MyString &lhs, const MyString &rhs)
{
    unsigned cap = (lhs.getLength() < rhs.getLength()) ? lhs.getLength() : rhs.getLength();
    unsigned n = 0;
    while ((n < cap) && (lhs[n] == rhs[n]))
        n++;
    if (n == cap)
        return (lhs.getLength() > rhs.getLength());

    if ((('A' <= lhs[n] && lhs[n] <= 'Z') || ('a' <= lhs[n] && lhs[n] <= 'z')) &&
        (('A' <= rhs[n] && rhs[n] <= 'Z') || ('a' <= rhs[n] && rhs[n] <= 'z')))
    {
        char A = (lhs[n] & ~32);
        char B = (rhs[n] & ~32);
        if (A != B)
            return (A > B);
    }
    return lhs[n] > rhs[n];
}

// Returns (bool) lhs > rhs
bool operator>(const MyString &lhs, char rhs)
{
    return (lhs > MyString(rhs));
}

// Returns (bool) lhs > rhs
bool operator>(const MyString &lhs, const char *rhs)
{
    return (lhs > MyString(rhs));
}

// Returns (bool) lhs > rhs
bool operator>(char lhs, const MyString &rhs)
{
    return (MyString(lhs) > rhs);
}

// Returns (bool) lhs > rhs
bool operator>(const char *lhs, const MyString &rhs)
{
    return (MyString(lhs) > rhs);
}

// Returns (bool) lhs < rhs
bool operator<(const MyString &lhs, const MyString &rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

// Returns (bool) lhs < rhs
bool operator<(const MyString &lhs, char rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

// Returns (bool) lhs < rhs
bool operator<(const MyString &lhs, const char *rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

// Returns (bool) lhs < rhs
bool operator<(char lhs, const MyString &rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

// Returns (bool) lhs < rhs
bool operator<(const char *lhs, const MyString &rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

// Returns (bool) lhs >= rhs
bool operator>=(const MyString &lhs, const MyString &rhs)
{
    return (lhs == rhs) || (lhs > rhs);
}

// Returns (bool) lhs >= rhs
bool operator>=(const MyString &lhs, char rhs)
{
    return (lhs == rhs) || (lhs > rhs);
}

// Returns (bool) lhs >= rhs
bool operator>=(const MyString &lhs, const char *rhs)
{
    return (lhs == rhs) || (lhs > rhs);
}

// Returns (bool) lhs >= rhs
bool operator>=(char lhs, const MyString &rhs)
{
    return (lhs == rhs) || (lhs > rhs);
}

// Returns (bool) lhs >= rhs
bool operator>=(const char *lhs, const MyString &rhs)
{
    return (lhs == rhs) || (lhs > rhs);
}

// Returns (bool) lhs <= rhs
bool operator<=(const MyString &lhs, const MyString &rhs)
{
    return !(lhs > rhs);
}

// Returns (bool) lhs <= rhs
bool operator<=(const MyString &lhs, char rhs)
{
    return !(lhs > rhs);
}

// Returns (bool) lhs <= rhs
bool operator<=(const MyString &lhs, const char *rhs)
{
    return !(lhs > rhs);
}

// Returns (bool) lhs <= rhs
bool operator<=(char lhs, const MyString &rhs)
{
    return !(lhs > rhs);
}

// Returns (bool) lhs <= rhs
bool operator<=(const char *lhs, const MyString &rhs)
{
    return !(lhs > rhs);
}
