#include "BarbarianCaravan.h"
#include "../../Desert/Desert.h"

using namespace std;

void BarbarianCaravan::autoMove(const Desert &desert) {
    int iCaravan = 0, iMountain = 0;
    int jCaravan = 0, jMountain = 0;
    for (int i = this->getX() - 8; i < this->getX() + 8; i++) {
        if (desert.getXYCellType(i, this->getY()) == CARAVAN) {
            iCaravan = i;
        }
        if (desert.getXYCellType(i, this->getY()) == MOUNTAIN) {
            iMountain = i;
        }
    }
    for (int j = this->getY() - 6; j < this->getY() + 6; j++) {
        if (desert.getXYCellType(this->getX(), j) == CARAVAN) {
            jCaravan = j;
        }
        if (desert.getXYCellType(this->getX(), j) == MOUNTAIN) {
            jMountain = j;
        }
    }

    if (iCaravan != 0 || iMountain != 0) {
        if (abs(this->getX() - iCaravan) < abs(this->getX() - iMountain)) {
            if (iCaravan < this->getX()) {
                this->addXY(-1, 0, desert);
            } else if (iCaravan > this->getX()) {
                this->addXY(1, 0, desert);
            }
            this->nrMovesLeft--;
            return;
        }
    }
    if (jCaravan != 0 || jMountain != 0) {
        if (abs(this->getY() - jCaravan) < abs(this->getY() - jMountain)) {
            if (jCaravan < this->getY()) {
                this->addXY(0, -1, desert);
            } else if (jCaravan > this->getY()) {
                this->addXY(0, 1, desert);
            }
            this->nrMovesLeft--;
            return;
        }
    }

    vector<pair<int, int>> validMoves = this->getValidMoves(desert);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, (int) validMoves.size());

    int randomNumber = distrib(gen);

    if (this->nrMovesLeft == 0) {
        return;
    }

    pair<int, int> xyToAdd = validMoves[randomNumber];
    this->addXY(xyToAdd.first, xyToAdd.second, desert);
    this->nrMovesLeft--;
}

void BarbarianCaravan::nextShift() {
    this->nrInstancesUntilDead--;
}

bool BarbarianCaravan::isDead() {
    return this->nrInstancesUntilDead <= 0 || this->nrCrewMembers <= 0;
}

bool BarbarianCaravan::applySandstorm() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 1.0); // Distribuição de números reais entre 0 e 1
    double randomNumber = distrib(gen);

    this->nrCrewMembers = floor(0.90 * this->nrCrewMembers);

    if (randomNumber <= 0.25) {
        return true;
    }
    return false;
}

bool BarbarianCaravan::isOnCombat(Desert &desert) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (desert.getXYCellType(this->x + i, this->y + j) == CARAVAN) {
                isOperatingAutomatically = false;
                return true;
            }
        }
    }
    isOperatingAutomatically = true;
    return false;
}

