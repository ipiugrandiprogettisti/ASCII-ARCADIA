#include "header/map.hpp"
#include "header/utils.hpp"
#include "header/MyString.hpp"

Map ::Map(WINDOW *myWin) : myWin(myWin)
{
}

void Map::drawRoom()
{
    MyString str = MyString();
    str.append("Colonne: ");
    str.append(itoa(COLS));
    mvaddstr(0, 0, str.get());
    str.reset();
    str.append("Righe: ");
    str.append(itoa(LINES));
    mvaddstr(1, 0, str.get());
    int width = 80, heigth = 15;
    int halfY = LINES / 2;
    int halfX = COLS / 2;
    int adjWidth = halfX - width / 2;   // adjusted width
    int adjHeigth = halfY - heigth / 2; // adjusted heigth

    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width)
            mvaddch(halfY - heigth / 2, adjWidth + i, ACS_PLUS);
        else
            mvaddch(halfY - heigth / 2, adjWidth + i, ACS_HLINE);
    }
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width)
            mvaddch(halfY + heigth / 2, adjWidth + i, ACS_PLUS);

        else
            mvaddch(halfY + heigth / 2, adjWidth + i, ACS_HLINE);
    }

    for (int i = 0; i < heigth; i++)
    {
        if (i == 0 || i == heigth - 1)
            mvaddch(adjHeigth + i, adjWidth + width, ACS_PLUS);
        else
            mvaddch(adjHeigth + i, adjWidth + width, ACS_VLINE);
    }
    for (int i = 0; i < heigth; i++)
    {
        if (i == 0 || i == heigth - 1)
            mvaddch(adjHeigth + i, adjWidth, ACS_PLUS);
        else
            mvaddch(adjHeigth + i, adjWidth, ACS_VLINE);
    }
}