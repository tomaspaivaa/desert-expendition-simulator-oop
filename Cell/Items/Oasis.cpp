#include "Oasis.h"
#include "../Caravans/Caravan.h"
#include "../../Desert/Desert.h"

using namespace std;

void Oasis::applyEffect(Desert &desert) {
    int xToApply = 0, yToApply = 0;

    if (desert.getXYCellType(this->x + 1, this->y) == CARAVAN ||
        desert.getXYCellType(this->x + 1, this->y) == BARBARIANCARAVAN) {
        xToApply = 1;
    } else if (desert.getXYCellType(this->x - 1, this->y) == CARAVAN ||
               desert.getXYCellType(this->x - 1, this->y) == BARBARIANCARAVAN) {
        xToApply = -1;
    } else if (desert.getXYCellType(this->x, this->y + 1) == CARAVAN ||
               desert.getXYCellType(this->x, this->y + 1) == BARBARIANCARAVAN) {
        yToApply = 1;
    } else if (desert.getXYCellType(this->x, this->y - 1) == CARAVAN ||
               desert.getXYCellType(this->x, this->y - 1) == BARBARIANCARAVAN) {
        yToApply = -1;
    }
    if (xToApply != 0 || yToApply != 0) {
        shared_ptr<Caravan> caravan = desert.getCaravan(this->x + xToApply, this->y + yToApply);
        caravan->setNrLitersWater(caravan->getNrMaxLitersWater());
        desert.destroyItemXY(this->x, this->y);
    }
}