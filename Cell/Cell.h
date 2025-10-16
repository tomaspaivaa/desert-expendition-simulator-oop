
#ifndef TRABALHOPRATICO_POO_CELL_H
#define TRABALHOPRATICO_POO_CELL_H

#include "CellTypeEnum.h"

class Desert;

class Cell {
public:
    Cell(int coordX, int coordY) : x(coordX), y(coordY) {}

    int getX() const { return this->x; }

    int getY() const { return this->y; }

    virtual CellType getCellType() = 0;

    void addXY(int xToAdd, int yToAdd, const Desert &desert);

protected:
    int x;

    int y;

};


#endif //TRABALHOPRATICO_POO_CELL_H
