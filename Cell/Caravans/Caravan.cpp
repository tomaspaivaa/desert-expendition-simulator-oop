
#include "Caravan.h"
#include "../../Desert/Desert.h"

int Caravan::nextId = 0;

CellType Caravan::getCellType() {
    return this->cellType;
}

vector<pair<int, int>> Caravan::getValidMoves(const Desert &desert) {
    vector<pair<int, int>> validMoves;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            CellType cellTypeToMove = desert.getXYCellType(this->x + i, this->y + j);
            if (cellTypeToMove != MOUNTAIN && cellTypeToMove != CARAVAN && cellTypeToMove != BARBARIANCARAVAN) {
                validMoves.emplace_back(i, j);
            }
        }
    }
    return validMoves;

}

void Caravan::resetNrMovesLeft() {
    this->nrMovesLeft = this->nrMaxMovesPerTurn;
}

Caravan::Caravan(int nrMaxMovesPerTurn, int nrMaxLitersWater, int nrMaxTonsMerch, int nrMaxCrewMembers,
                 int nrInstancesUntilDead, bool isOperatingAutomatically, CellType cellType, CaravanType caravanType,
                 int coordX, int coordY)
        :
        nrMaxMovesPerTurn(nrMaxMovesPerTurn), nrMaxLitersWater(nrMaxLitersWater),
        nrMaxTonsMerch(nrMaxTonsMerch), nrTonsMerch(0), nrMaxCrewMembers(nrMaxCrewMembers),
        nrCrewMembers(nrMaxCrewMembers), nrInstancesUntilDead(nrInstancesUntilDead), nrMovesLeft(nrMaxMovesPerTurn),
        nrLitersWater(nrMaxLitersWater), isOperatingAutomatically(isOperatingAutomatically),
        cellType(cellType), caravanType(caravanType), Cell(coordX, coordY) {
    if (cellType != BARBARIANCARAVAN) {
        this->id = ++nextId;
    } else {
        this->id = -1;
    }
}
