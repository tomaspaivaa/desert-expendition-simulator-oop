#include "TreasureChest.h"
#include "../../Desert/Desert.h"

using namespace std;

void TreasureChest::applyEffect(Desert &desert) {
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
        desert.coinsToAdd(static_cast<int> (0.10 * desert.getCoins()));
        desert.destroyItemXY(this->x, this->y);
    }
}