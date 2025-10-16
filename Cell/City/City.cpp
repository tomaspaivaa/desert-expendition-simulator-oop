#include "City.h"

bool City::isCaravanTypeAvailableForPurchase(CaravanType caravanType) const {
    if (!this->typeCaravansForSale.contains(caravanType)) {
        return false;
    }

    return this->typeCaravansForSale.at(caravanType) > 0;
}

CellType City::getCellType() {
    return this->cellType;
}

