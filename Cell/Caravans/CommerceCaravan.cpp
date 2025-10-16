#include "CommerceCaravan.h"
#include "../../Desert/Desert.h"

using namespace std;

void CommerceCaravan::autoMove(const Desert &desert) {
    if (this->nrCrewMembers > 0) {
        int iItem = 0, iMountain = 0;
        int jItem = 0, jMountain = 0;
        for (int i = this->getX() - 2; i < this->getX() + 2; i++) {
            if (desert.getXYCellType(i, this->getY()) == ITEM) {
                iItem = i;
            }
            if (desert.getXYCellType(i, this->getY()) == MOUNTAIN) {
                iMountain = i;
            }
        }
        for (int j = this->getY() - 6; j < this->getY() + 6; j++) {
            if (desert.getXYCellType(this->getX(), j) == ITEM) {
                jItem = j;
            }
            if (desert.getXYCellType(this->getX(), j) == MOUNTAIN) {
                jMountain = j;
            }
        }

        if (iItem != 0 || iMountain != 0) {
            if (abs(this->getX() - iItem) < abs(this->getX() - iMountain)) {
                if (iItem < this->getX()) {
                    this->addXY(-1, 0, desert);
                } else if (iItem > this->getX()) {
                    this->addXY(1, 0, desert);
                }
                this->nrMovesLeft--;
                return;
            }
        }
        if (jItem != 0 || jMountain != 0) {
            if (abs(this->getY() - jItem) < abs(this->getY() - jMountain)) {
                if (jItem < this->getY()) {
                    this->addXY(0, -1, desert);
                } else if (jItem > this->getY()) {
                    this->addXY(0, 1, desert);
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


void CommerceCaravan::nextShift() {
    if (this->nrCrewMembers <= 0) {
        this->nrInstancesUntilDead--;
        return;
    }
    if (this->nrLitersWater <= 0) {
        this->nrCrewMembers--;
        return;
    }
    this->nrLitersWater--;
    if (this->nrCrewMembers > (this->nrMaxCrewMembers / 2)) {
        this->nrLitersWater--;
    }
}

bool CommerceCaravan::applySandstorm() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 1.0); // Distribuição de números reais entre 0 e 1

    double randomNumber = distrib(gen);
    if (this->nrTonsMerch >= (0.50 * this->nrMaxTonsMerch) && randomNumber < 0.50) {
        return true;
    } else if (this->nrTonsMerch < (0.50 * this->nrMaxTonsMerch) && randomNumber < 0.25) {
        return true;
    }

    // sobreviveu

    this->nrTonsMerch = 0.75 * this->nrTonsMerch;
    return false;
}

bool CommerceCaravan::isDead() {
    return this->nrInstancesUntilDead == 0;
}
