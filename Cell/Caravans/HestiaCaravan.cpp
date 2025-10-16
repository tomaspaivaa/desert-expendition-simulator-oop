#include "HestiaCaravan.h"
#include "../../Desert/Desert.h"


using namespace std;

void HestiaCaravan::autoMove(const Desert &desert) {
    if (this->nrCrewMembers > 0) {
        int iBarbarian = 0, iMountain = 0;
        int jBarbarian = 0, jMountain = 0;
        for (int i = this->getX() - 8; i < this->getX() + 8; i++) {
            if (desert.getXYCellType(i, this->getY()) == BARBARIANCARAVAN) {
                iBarbarian = i;
            }
            if (desert.getXYCellType(i, this->getY()) == MOUNTAIN) {
                iMountain = i;
            }
        }
        for (int j = this->getY() - 8; j < this->getY() + 8; j++) {
            if (desert.getXYCellType(this->getX(), j) == BARBARIANCARAVAN) {
                jBarbarian = j;
            }
            if (desert.getXYCellType(this->getX(), j) == MOUNTAIN) {
                jMountain = j;
            }
        }

        if (iBarbarian != 0 || iMountain != 0) {
            if (abs(this->getX() - iBarbarian) < abs(this->getX() - iMountain)) {
                if (iBarbarian < this->getX()) {
                    this->addXY(1, 0, desert);
                } else if (iBarbarian > this->getX()) {
                    this->addXY(-1, 0, desert);
                }
                this->nrMovesLeft--;
                return;
            }
        }
        if (jBarbarian != 0 || jMountain != 0) {
            if (abs(this->getY() - jBarbarian) < abs(this->getY() - jMountain)) {
                if (jBarbarian < this->getY()) {
                    this->addXY(0, 1, desert);
                } else if (jBarbarian > this->getY()) {
                    this->addXY(0, -1, desert);
                }
                this->nrMovesLeft--;
                return;
            }
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

bool HestiaCaravan::applySandstorm() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 1.0); // Distribuição de números reais entre 0 e 1

    double randomNumber = distrib(gen);
    if (randomNumber < 0.10 && this->nrCrewMembers < 25) {
        this->setNrLitersWater(0.90 * this->nrLitersWater);
    } else if (randomNumber < 0.20 && this->nrCrewMembers > 25) {
        this->setNrLitersWater(0.80 * this->nrLitersWater);
    }

    return false;
}

void HestiaCaravan::nextShift() {
    if (this->nrCrewMembers <= 0) {
        this->nrInstancesUntilDead--;
        return;
    }
    if (this->nrLitersWater <= 0) {
        this->nrCrewMembers--;
        return;
    }
    this->nrLitersWater -= 3;
    if (this->nrCrewMembers > (this->nrMaxCrewMembers / 2)) {
        this->nrLitersWater -= 2;
    }
}

bool HestiaCaravan::isDead() {
    return this->nrInstancesUntilDead == 0;
}
