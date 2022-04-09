#include "header/MyString.hpp"

MyString::MyString()
{

    /*string = new char[strlen("\0") + 1];
    strcpy(string, "\0");
    this->length = strlen("\0");*
    */
    string = new char[1];
    string[0] = '\0';
    this->length = 0;
}

MyString::MyString(char const *text)
{
    this->length = strlen(text);
    string = new char[strlen(text) + 1];
    strcpy(string, text);
}

// append string
void MyString::append(char const *text)
{
    char *oldStr = new char[strlen(string) + 1];

    for (int i = 0; string[i] != '\0'; i++)
        oldStr[i] = string[i];

    length = strlen(oldStr) + strlen(text);
    string = new char[length + 1];

    for (int i = 0; oldStr[i] != '\0'; i++)
        string[i] = oldStr[i];

    int c = 0;
    for (int i = strlen(oldStr); text[c] != '\0'; i++)
    {
        string[i] = text[c];
        c++;
    }

    delete oldStr;
}

// appen char
// FIXME problema append, a volte viene stampato garbage... problemi con \0 finale DA TESTARE ANCHE QUI SE C'È PROBLEMA
void MyString::append(char ch)
{
    char *oldStr = new char[strlen(string) + 1];

    for (int i = 0; string[i] != '\0'; i++)
        oldStr[i] = string[i];

    length = strlen(oldStr) + 1;
    string = new char[length + 1];

    for (int i = 0; oldStr[i] != '\0'; i++)
        string[i] = oldStr[i];

    string[strlen(oldStr)] = ch;

    delete oldStr;
}

// reverse string
void MyString::reverse()
{
    char *tmpStr = new char[strlen(string)];
    strcpy(tmpStr, string);
    int c = 0;
    for (int i = strlen(tmpStr) - 1; i >= 0; i--)
    {
        string[c] = tmpStr[i];
        c++;
    }
}

// reset string to "\0"
void MyString::reset()
{ /*
     string = new char[strlen("\0") + 1];
     strcpy(string, "\0");
     this->length = strlen("\0");
     */
    string = new char[1];
    string[0] = '\0';
    this->length = 0;
}

// returns string length, does not count '\0'
int MyString::getLength()
{
    return length;
}

// returns string
const char *MyString::get()
{
    return string;
}
