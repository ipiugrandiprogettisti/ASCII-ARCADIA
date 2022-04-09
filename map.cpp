#include "header/map.hpp"

Map ::Map(WINDOW *myWin) : myWin(myWin)
{
}

void Map::drawRoom()
{
    int width = 35, heigth = 15;
    int halfY = LINES / 2 - 2;
    int halfX = COLS / 2 - 2;
    int adjWidth = halfX - width / 2;
    int adjHeigth = halfY - heigth / 2;

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
        mvaddstr(adjHeigth + i, adjWidth+width, "|");
    }
    for (int i = 0; i < heigth; i++)
    {
        mvaddstr(adjHeigth + i, adjWidth, "|");
    }
}