#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GamePhaseEnum.h"

#include "../Cell/Cell.h"
#include "../Cell/Caravans/Caravan.h"
#include "../Cell/Caravans/CommerceCaravan.h"
#include "../Cell/Caravans/MilitarCaravan.h"
#include "../Cell/Caravans/HestiaCaravan.h"
#include "../Cell/Caravans/BarbarianCaravan.h"
#include "../Cell/Caravans/CaravanTypeEnum.h"

#include "../Cell/Items/Item.h"
#include "../Cell/Items/PandorasBox.h"
#include "../Cell/Items/Mine.h"
#include "../Cell/Items/TreasureChest.h"
#include "../Cell/Items/Cage.h"
#include "../Cell/Items/Oasis.h"

#include "../Cell/City/City.h"

#include "../Cell/Terrain/Terrain.h"

#ifndef TRABALHOPRATICO_POO_DESERTO_H
#define TRABALHOPRATICO_POO_DESERTO_H

using namespace std;

class Desert {
public:
    Desert() : currentGamePhase(CONFIG_PHASE) {}

    int getMapLines() const { return this->mapLines; }

    int getMapColumns() const { return this->mapColumns; }

    GAME_PHASE getGamePhase() { return this->currentGamePhase; }

    void endConfigPhase();

    void endGamingPhase();

    bool isCaravanCOperatingAutomatically(int caravanC);

    int getSellPriceMerchandise() const { return this->sellPriceMerchandise; }

    int getBuyMerchandise() const { return this->buyPriceMerchandise; }

    int getinstancesCounter() const { return this->instancesCounter; };

    shared_ptr<Caravan> getCaravan(int x, int y) const;

    shared_ptr<Cell> getXYInfo(int x, int y) const;

    CellType getXYCellType(int x, int y) const;

    bool readDataFromFile(string fileName);

    bool doesCaravanNHasMaxMerch(int caravanN);

    bool doesCityCExists(char cityC);

    void buyCaravanTOnCityC(char caravanT, char cityC);

    map<CaravanType, int> listCaravansOnCityC(char cityC) const;

    shared_ptr<Caravan> listCaravanCDetails(int caravanC) const;

    bool isCaravanNOnCity(int caravanN);

    bool isCoordLREmpty(int coordL, int coordR);

    void createBarbarianCaravanLR(int coordL, int coordC);

    bool doesCaravanCExists(int caravanC);

    void addMerchMToCaravanN(int merchM, int caravanN);

    void sellCaravanNMerchandise(int caravanN);

    void moveCaravanNToX(int caravanN, char X, char D);

    void activateCaravanNAutoMode(int caravanN);

    void desactivateCaravanNAutoMode(int caravanN);

    void createSandstorm(int l, int c, int r);

    bool doesCaravanNHasMovesLeft(int caravanN);

    void coinsToAdd(int coinsAmount);

    void destroyCaravanN(int caravanNId);

    int getCoins() const { return this->coins; }

    void nextShift(int nShifts = 1);

    void addCrewMembersTToCaravanN(int caravanN, int nrCrewMembersTToAdd);

    void createRandomItem();

    void createRandomBarbarian();

    void destroyItemXY(int coordX, int coordY);

private:
    GAME_PHASE currentGamePhase;

    vector<shared_ptr<Terrain>> terrains;
    vector<shared_ptr<Caravan>> caravans;
    vector<shared_ptr<Item>> items;
    vector<shared_ptr<City>> cities;

    int mapColumns;

    int mapLines;

    int coins;

    int instancesBetweenNewItems;

    int itemDuration;

    int maxItems;

    int sellPriceMerchandise;

    int buyPriceMerchandise;

    int caravanPrice;

    int instancesBetweenNewBarbarians;

    int barbariansDuration;

    int instancesCounter;

};


#endif //TRABALHOPRATICO_POO_DESERTO_H
