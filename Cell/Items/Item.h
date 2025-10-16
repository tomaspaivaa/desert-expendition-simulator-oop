#ifndef TRABALHOPRATICO_POO_ITEM_H
#define TRABALHOPRATICO_POO_ITEM_H

#include "../Cell.h"
#include "../CellTypeEnum.h"

#include <string>
#include <iostream>

using namespace std;

class Desert;

class Item : public Cell {
public:
    Item(int instancesLeft, int coordX, int coordY) : cellType(ITEM), instancesLeft(instancesLeft),
                                                      Cell(coordX, coordY) {}

    virtual void applyEffect(Desert &desert) = 0;

    void nextShift() { this->instancesLeft--; }

    bool isDead() const { return this->instancesLeft <= 0; }

    CellType getCellType() override;

protected:
    int instancesLeft;

    CellType cellType;
};


#endif //TRABALHOPRATICO_POO_ITEM_H
