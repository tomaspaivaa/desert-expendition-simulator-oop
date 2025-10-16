
#ifndef TRABALHOPRATICO_POO_TERRAIN_H
#define TRABALHOPRATICO_POO_TERRAIN_H

#include "../Cell.h"
#include "../CellTypeEnum.h"

class Terrain : public Cell {
public:
    Terrain(CellType cellType, int coordX, int coordY) : cellType(cellType), Cell(coordX, coordY) {}

    virtual CellType getCellType() override;

private:
    CellType cellType;
};


#endif //TRABALHOPRATICO_POO_TERRAIN_H
