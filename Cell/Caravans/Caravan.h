#ifndef TRABALHOPRATICO_POO_CARAVAN_H
#define TRABALHOPRATICO_POO_CARAVAN_H

#include "../Cell.h"
#include "../CellTypeEnum.h"

#include "CaravanTypeEnum.h"

#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

class Desert;

class Caravan : public Cell {
public:
    Caravan(int nrMaxMovesPerTurn, int nrMaxLitersWater, int nrMaxTonsMerch, int nrMaxCrewMembers,
            int nrInstancesUntilDead, bool isOperatingAutomatically, CellType cellType, CaravanType caravanType,
            int coordX, int coordY);

    virtual void autoMove(const Desert &desert) = 0;

    void resetNrMovesLeft();

    virtual bool applySandstorm() = 0;

    virtual void nextShift() = 0;

    CellType getCellType() override;

    void setIsOperatingAutomatically(bool newIsOperatingAutomatically) {
        this->isOperatingAutomatically = newIsOperatingAutomatically;
    }

    bool getIsOperatingAutomatically() const { return this->isOperatingAutomatically; }

    bool hasMovesLeft() const { return this->nrMovesLeft > 0; }

    void setNrMovesLeft(int newNrMovesLeft) { this->nrMovesLeft = newNrMovesLeft; }

    void setNrInstancesUntilDead(int newNrInstancesUntilDead) { this->nrInstancesUntilDead = newNrInstancesUntilDead; }

    void setNrLitersWater(int newNrLitersWater) { this->nrLitersWater = newNrLitersWater; }

    void decrementNrMovesLeft() { this->nrMovesLeft--; }

    CaravanType getCaravanType() const { return this->caravanType; }

    bool isEmpty() const { return this->nrCrewMembers == 0; }

    int getId() const { return this->id; }

    int getNrCrewMembers() const { return nrCrewMembers; }

    int getNrMaxCrewMembers() const { return this->nrMaxCrewMembers; }

    void setNrCrewMembers(int newNrCrewMembers) { this->nrCrewMembers = newNrCrewMembers; }

    int getNrMaxTonsMerch() const { return this->nrMaxTonsMerch; }

    int getNrTonsMerch() const { return this->nrTonsMerch; }

    int getNrMaxMovesPerTurn() const { return this->nrMaxMovesPerTurn; }

    int getNrMaxLitersWater() const { return this->nrMaxLitersWater; }

    int getNrLitersWater() const { return this->nrLitersWater; }

    void setNrTonsMerch(int newNrTonsMerch) { this->nrTonsMerch = newNrTonsMerch; }

    virtual bool isDead() = 0;

protected:
    bool isOperatingAutomatically;

    const int nrMaxMovesPerTurn;
    int nrMovesLeft;

    const int nrMaxLitersWater;
    int nrLitersWater;

    const int nrMaxTonsMerch;
    int nrTonsMerch;

    const int nrMaxCrewMembers;
    int nrCrewMembers;

    int nrInstancesUntilDead;

    int id;

    CellType cellType;

    CaravanType caravanType;

    vector<pair<int, int>> getValidMoves(const Desert &desert);

private:
    static int nextId;

};


#endif //TRABALHOPRATICO_POO_CARAVAN_H
