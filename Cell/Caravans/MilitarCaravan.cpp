
#include "MilitarCaravan.h"
#include "../../Desert/Desert.h"

bool MilitarCaravan::applySandstorm() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 1.0); // Distribuição de números reais entre 0 e 1

    double randomNumber = distrib(gen);

    this->nrCrewMembers = 0.90 * this->nrCrewMembers;

    if (randomNumber < 0.33) {
        return true;
    }

    return false;
}

void MilitarCaravan::autoMove(const Desert &desert) {
    if (this->nrCrewMembers <= 0) {
        vector<pair<int, int>> validMoves = this->getValidMoves(desert);
        for (const auto &move: validMoves) { //
            if (move.first == this->lastXMovement && move.second == this->lastYMovement) {
                this->addXY(this->lastXMovement, this->lastYMovement, desert);
            }
        }
        return;
    }
    int iBarbarian = 0, iMountain = 0;
    int jBarbarian = 0, jMountain = 0;

    for (int i = this->getX() - 6; i < this->getX() + 6; i++) {
        if (desert.getXYCellType(i, this->getY()) == BARBARIANCARAVAN) {
            iBarbarian = i;
        }
        if (desert.getXYCellType(i, this->getY()) == MOUNTAIN) {
            iMountain = i;
        }
    }
    for (int j = this->getY() - 6; j < this->getY() + 6; j++) {
        if (desert.getXYCellType(this->getX(), j) == BARBARIANCARAVAN) {
            cout << this->getX() << "|" << j << endl;
            jBarbarian = j;
        }
        if (desert.getXYCellType(this->getX(), j) == MOUNTAIN) {
            jMountain = j;
        }
    }

    if (iBarbarian != 0 || iMountain != 0) {
        if (abs(this->getX() - iBarbarian) < abs(this->getX() - iMountain)) {
            if (iBarbarian < this->getX()) {
                this->addXY(-1, 0, desert);
            } else if (iBarbarian > this->getX()) {
                this->addXY(1, 0, desert);
            }
        }
    }
    if (jBarbarian != 0 || jMountain != 0) {
        if (abs(this->getY() - jBarbarian) < abs(this->getY() - jMountain)) {
            if (jBarbarian < this->getY()) {
                this->addXY(0, -1, desert);
            } else if (jBarbarian > this->getY()) {
                this->addXY(0, 1, desert);
            }
        }
    }
    this->nrMovesLeft--;
}

void MilitarCaravan::nextShift() {
    if (this->nrCrewMembers <= 0) {
        this->nrInstancesUntilDead--;
        return;
    }
    if (this->nrLitersWater <= 0) {
        this->nrCrewMembers--;
        return;
    }
    if (this->nrCrewMembers < (this->nrMaxCrewMembers / 2)) {
        this->nrLitersWater--;
        return;
    }
    this->nrLitersWater -= 3;
}

bool MilitarCaravan::isDead() {
    return this->nrInstancesUntilDead == 0;
}

void MilitarCaravan::setLastMovement(int newLastXMovement, int newLastYMovement) {
    this->lastXMovement = newLastXMovement;
    this->lastYMovement = newLastYMovement;
}


