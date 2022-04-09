#include "header/map.hpp"
#include "header/utils.hpp"
#include "header/MyString.hpp"

Map ::Map(WINDOW *myWin) : myWin(myWin)
{
}

void Map::drawRoom()
{
    MyString str = MyString("Colonne: ");
   // str.append("Colonne: ");
   // str.append(itoa(COLS));
  //  str.append(", length =");
   // str.append(itoa(str.length));
    mvaddstr(0, 0, str.get());
    str.reset();
    str.append("Righe:");
    str.append(itoa(LINES));
    str.append(", length =");
    str.append(itoa(str.length));
    mvaddstr(1, 0, str.get());
    int width = 80, heigth = 15;
    int halfY = LINES / 2;
    int halfX = COLS / 2;
    int adjWidth = halfX - width / 2;   // adjusted width
    int adjHeigth = halfY - heigth / 2; // adjusted heigth

    for (int i = 0; i < width; i++)
    {
        mvaddstr(halfY - heigth / 2, adjWidth + i, "-");
    }
    for (int i = 0; i < width; i++)
    {
        mvaddstr(halfY + heigth / 2, adjWidth + i, "-");
    }

    for (int i = 0; i < heigth; i++)
    {
        mvaddstr(adjHeigth + i, adjWidth + width, "|");
    }
    for (int i = 0; i < heigth; i++)
    {
        mvaddstr(adjHeigth + i, adjWidth, "|");
    }
}