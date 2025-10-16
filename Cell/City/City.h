#ifndef TRABALHOPRATICO_POO_CITY_H
#define TRABALHOPRATICO_POO_CITY_H

#include "../Cell.h"
#include "../CellTypeEnum.h"

#include "../Caravans/CaravanTypeEnum.h"

#include <map>
#include <string>
#include <sstream>

using namespace std;

class City : public Cell {
public:
    City(char name, int coordX, int coordY) : name(name),
                                              typeCaravansForSale({{COMMERCE, 1},
                                                                   {MILITAR,  1},
                                                                   {HESTIA,   1}}),
                                              cellType(CITY),
                                              Cell(coordX, coordY) {}

    CellType getCellType() override;

    char getName() const { return name; }

    map<CaravanType, int> getTypeCaravansForSale() const { return this->typeCaravansForSale; };

    bool isCaravanTypeAvailableForPurchase(CaravanType caravanType) const;

    void purchaseCaravanType(CaravanType caravanType) { this->typeCaravansForSale[caravanType]--; }

    int getMerchSellCoinsValue() const { return this->merchSellCoinsValue; }

    int getMerchBuyCoinsValue() const { return this->merchBuyCoinsValue; }

    void setMerchSellCoinsValue(int newMerchSellCoinsValue) { this->merchSellCoinsValue = newMerchSellCoinsValue; }

    void setMerchBuyCoinsValue(int newMerchBuyCoinsValue) { this->merchBuyCoinsValue = newMerchBuyCoinsValue; }

private:
    const char name;
    map<CaravanType, int> typeCaravansForSale;

    int merchSellCoinsValue;
    int merchBuyCoinsValue;

    int nrTonMerchandise;

    CellType cellType;
};


#endif //TRABALHOPRATICO_POO_CITY_H
