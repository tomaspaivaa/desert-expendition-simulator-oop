#include "Desert.h"

shared_ptr<Caravan> Desert::getCaravan(int x, int y) const {
    for (auto caravan: this->caravans) {
        if (caravan->getX() == x && caravan->getY() == y) {
            return caravan;
        }
    }

    ostringstream oss;
    oss << "Caravan not found in (" << x << ", " << y << ").";
    throw runtime_error(oss.str());
}

shared_ptr<Cell> Desert::getXYInfo(int x, int y) const {
    for (const auto &city: cities) {
        if (city->getX() == x && city->getY() == y) {
            return city;
        }
    }

    for (const auto &caravan: caravans) {
        if (caravan->getX() == x && caravan->getY() == y) {
            return caravan;
        }
    }

    for (const auto &item: items) {
        if (item->getX() == x && item->getY() == y) {
            return item;
        }
    }

    for (const auto &terrain: terrains) {
        if (terrain->getX() == x && terrain->getY() == y) {
            return terrain;
        }
    }
    throw runtime_error("Deu merda");
}

CellType Desert::getXYCellType(int x, int y) const {
    for (const auto &city: cities) {
        if (city->getX() == x && city->getY() == y) {
            return CITY;
        }
    }
    for (const auto &caravan: caravans) {
        if (caravan->getX() == x && caravan->getY() == y && caravan->getCaravanType() == BARBARIAN) {
            return BARBARIANCARAVAN;
        } else if (caravan->getX() == x && caravan->getY() == y) {
            return CARAVAN;
        }
    }
    for (const auto &item: items) {
        if (item->getX() == x && item->getY() == y) {
            return ITEM;
        }
    }
    for (const auto &terrain: terrains) {
        if (terrain->getX() == x && terrain->getY() == y) {
            if (terrain->getCellType() == MOUNTAIN) {
                return MOUNTAIN;
            }
            if (terrain->getCellType() == EMPTY) {
                return EMPTY;
            }
        }
    }
    return UNKNOWN;
}

bool Desert::doesCityCExists(char cityC) {
    for (const auto &city: cities) {
        if (city->getName() == cityC) {
            return true;
        }
    }
    return false;
}

bool Desert::isCaravanCOperatingAutomatically(int caravanC) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanC) {
            return caravan->getIsOperatingAutomatically();
        }
    }
    throw runtime_error("Caravan C doesn't exists.");
}

void Desert::activateCaravanNAutoMode(int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN && !caravan->getIsOperatingAutomatically()) {
            caravan->setIsOperatingAutomatically(true);
            return;
        }
    }
    throw runtime_error("Caravan N is already in auto mode.");
}

void Desert::desactivateCaravanNAutoMode(int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN && caravan->getIsOperatingAutomatically()) {
            caravan->setIsOperatingAutomatically(false);
            return;
        }
    }
    throw runtime_error("Caravan N has already auto mode desactivated.");
}

void Desert::buyCaravanTOnCityC(char caravanT, char cityC) {
    CaravanType caravanType;
    string className;
    if (caravanT == 'C')
        caravanType = COMMERCE;
    else if (caravanT == 'M')
        caravanType = MILITAR;
    else if (caravanT == 'S')
        caravanType = HESTIA;

    for (const auto &city: cities) {
        if (city->getName() == cityC && city->isCaravanTypeAvailableForPurchase(caravanType)) {
            city->purchaseCaravanType(caravanType);

            if (caravanT == 'C') {
                this->caravans.push_back(make_shared<CommerceCaravan>(city->getX(), city->getY()));
            } else if (caravanT == 'M') {
                this->caravans.push_back(make_shared<MilitarCaravan>(city->getX(), city->getY()));
            } else if (caravanT == 'S') {
                this->caravans.push_back(make_shared<HestiaCaravan>(city->getX(), city->getY()));
            }
            return;
        }
    }
    throw runtime_error("Caravan T doesn't exist in city C");
}

map<CaravanType, int> Desert::listCaravansOnCityC(char cityC) const {
    for (const auto &city: cities) {
        if (city->getName() == cityC) {
            return city->getTypeCaravansForSale();
        }
    }
    return {};
}

shared_ptr<Caravan> Desert::listCaravanCDetails(int caravanC) const {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanC) {
            return caravan;
        }
    }
    return nullptr;
}


bool Desert::doesCaravanCExists(int caravanC) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanC) {
            return true;
        }
    }
    return false;
}

bool Desert::isCaravanNOnCity(int caravanN) {
    for (const auto &city: cities) {
        for (const auto &caravan: caravans) {
            if (caravan->getId() == caravanN && (caravan->getX() == city->getX() && caravan->getY() == city->getY())) {
                return true;
            }
        }
    }
    return false;
}

void Desert::addMerchMToCaravanN(int merchM, int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN) {
            if (caravan->getNrTonsMerch() + merchM <= caravan->getNrMaxTonsMerch()) {
                if (this->coins < this->buyPriceMerchandise * merchM) {
                    throw runtime_error("The user doesn't have the money to buy the M tons of merch.");
                }
                this->coins = this->coins - this->buyPriceMerchandise * merchM;
                caravan->setNrTonsMerch(caravan->getNrTonsMerch() + merchM);
            } else {
                if (this->coins < (this->buyPriceMerchandise * caravan->getNrMaxTonsMerch() -
                                   caravan->getNrTonsMerch())) {
                    throw runtime_error("The user doesn't have the money to buy the M tons of merch.");
                }
                this->coins = this->coins - (this->buyPriceMerchandise * caravan->getNrMaxTonsMerch() -
                                             caravan->getNrTonsMerch());
                caravan->setNrTonsMerch(caravan->getNrMaxTonsMerch());
            }
        }
    }
}

bool Desert::doesCaravanNHasMaxMerch(int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN && caravan->getNrTonsMerch() == caravan->getNrMaxTonsMerch()) {
            return true;
        }
    }
    return false;
}

bool Desert::doesCaravanNHasMovesLeft(int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN) {
            if (!caravan->hasMovesLeft()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

void Desert::endConfigPhase() {
    this->currentGamePhase = GAMING_PHASE;
    this->instancesCounter = 0;
    createRandomItem();
}

void Desert::endGamingPhase() {
    this->currentGamePhase = CONFIG_PHASE;
    this->instancesCounter = 0;
}

void Desert::createRandomItem() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randomLineDistrib(0, this->mapLines);
    uniform_int_distribution<> randomColumnDistrib(0, this->mapColumns);

    int randomLine;
    int randomColumn;
    while (true) {
        randomLine = randomLineDistrib(gen);
        randomColumn = randomColumnDistrib(gen);
        if (isCoordLREmpty(randomLine, randomColumn)) {
            uniform_real_distribution<> probabilityDistrib(0.0, 1.0);
            double randomProb = probabilityDistrib(gen);
            if (randomProb <= 0.20) {
                this->items.push_back(make_shared<PandorasBox>(randomLine, randomColumn, this->itemDuration));
            } else if (randomProb <= 0.40) {
                this->items.push_back(make_shared<Mine>(randomLine, randomColumn, this->itemDuration));
            } else if (randomProb <= 0.60) {
                this->items.push_back(make_shared<TreasureChest>(randomLine, randomColumn, this->itemDuration));
            } else if (randomProb <= 0.80) {
                this->items.push_back(make_shared<Cage>(randomLine, randomColumn, this->itemDuration));
            } else if (randomProb <= 1.00) {
                this->items.push_back(make_shared<Oasis>(randomLine, randomColumn, this->itemDuration));
            }
            break;
        }
    }
}

void Desert::createRandomBarbarian() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randomLineDistrib(0, this->mapLines);
    uniform_int_distribution<> randomColumnDistrib(0, this->mapColumns);

    int randomLine;
    int randomColumn;
    while (true) {
        randomLine = randomLineDistrib(gen);
        randomColumn = randomColumnDistrib(gen);
        if (isCoordLREmpty(randomLine, randomColumn)) {
            this->caravans.push_back(make_shared<BarbarianCaravan>(randomLine, randomColumn));
            break;
        }
    }
}

void Desert::nextShift(int nShifts) {
    do {
        // Caravanas
        for (auto it = caravans.begin(); it != caravans.end();) {
            // ---- se há combate ----
            if ((*it)->getCaravanType() == BARBARIAN) {
                auto barbarianCaravan = static_pointer_cast<BarbarianCaravan>((*it));
                if (barbarianCaravan->isOnCombat(*this)) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distribBarbarian(0, barbarianCaravan->getNrCrewMembers());
                    int randomBarbarian = distribBarbarian(gen);
                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            if (getXYCellType(barbarianCaravan->getX() + i, barbarianCaravan->getY() + j) == CARAVAN) {
                                shared_ptr<Caravan> caravanOnCombat = getCaravan(barbarianCaravan->getX() + i,
                                                                                 barbarianCaravan->getY() + j);

                                uniform_int_distribution<> distribCaravan(0, caravanOnCombat->getNrCrewMembers());
                                int randomCaravan = distribCaravan(gen);
                                if (randomCaravan >= randomBarbarian) { //ganhou caravana user
                                    barbarianCaravan->setNrCrewMembers(
                                            floor((barbarianCaravan->getNrCrewMembers() -
                                                   caravanOnCombat->getNrCrewMembers() *
                                                   0.40))); // matar caravana barbara
                                    caravanOnCombat->setNrCrewMembers(
                                            floor((caravanOnCombat->getNrCrewMembers() * 0.80)));
                                    if (barbarianCaravan->getNrCrewMembers() <= 0) { //matar caravana barbara
                                        barbarianCaravan->setNrInstancesUntilDead(0); //matar caravana barbara
                                    }
                                } else { //ganhou caravana barbara
                                    caravanOnCombat->setNrCrewMembers(floor((caravanOnCombat->getNrCrewMembers() -
                                                                             barbarianCaravan->getNrCrewMembers() *
                                                                             0.40)));
                                    barbarianCaravan->setNrCrewMembers(
                                            floor((barbarianCaravan->getNrCrewMembers() * 0.80)));
                                    if (caravanOnCombat->getNrCrewMembers() <= 0) { //matar caravana user
                                        caravanOnCombat->setNrInstancesUntilDead(0); //matar caravana user
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // ------------------
            if ((*it)->isDead()) {
                it = caravans.erase(it);
                continue;
            } else if ((*it)->getIsOperatingAutomatically()) {
                while ((*it)->hasMovesLeft()) {
                    (*it)->autoMove(*this);
                }
            }
            (*it)->nextShift();
            (*it)->resetNrMovesLeft();
            ++it;
        }
        // Items
        for (auto it = items.begin(); it != items.end();) {
            if ((*it)->isDead()) {
                it = items.erase(it);
                continue;
            }
            (*it)->applyEffect(*this);
            (*it)->nextShift();
            ++it;
        }
        this->instancesCounter++;
        if (instancesCounter % this->instancesBetweenNewBarbarians == 0) {
            createRandomBarbarian();
        }
        if (instancesCounter % this->instancesBetweenNewItems == 0) {
            createRandomItem();
        }
        nShifts--;
    } while (nShifts > 0);
}

bool Desert::isCoordLREmpty(int coordL, int coordR) {
    for (const auto &terrain: terrains) {
        if (terrain->getX() == coordL && terrain->getY() == coordR && terrain->getCellType() == EMPTY) {
            return true;
        }
    }
    return false;
}

void Desert::createBarbarianCaravanLR(int coordL, int coordR) {
    this->caravans.push_back(make_shared<BarbarianCaravan>(coordL, coordR));
}

void Desert::destroyItemXY(int coordX, int coordY) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getX() == coordX && (*it)->getY() == coordY) {
            items.erase(it);
            break;
        }
    }
}

void Desert::moveCaravanNToX(int caravanN, char X, char D) {
    int xToAdd = 0;
    int yToAdd = 0;
    if (X == 'D' || D == 'D')
        yToAdd = 1;
    if (X == 'E' || D == 'E')
        yToAdd = -1;
    if (X == 'C')
        xToAdd = -1;
    if (X == 'B')
        xToAdd = 1;

    for (const auto &caravan: caravans) {
        if (caravan->getCaravanType() == MILITAR) {
            auto militarCaravan = static_pointer_cast<MilitarCaravan>(caravan);
            militarCaravan->setLastMovement(xToAdd, yToAdd);
        }
        if (caravan->getId() == caravanN) {
            if (getXYCellType(caravan->getX() + xToAdd, caravan->getY() + yToAdd) == MOUNTAIN ||
                getXYCellType(caravan->getX() + xToAdd, caravan->getY() + yToAdd) == CARAVAN ||
                getXYCellType(caravan->getX() + xToAdd, caravan->getY() + yToAdd) == BARBARIANCARAVAN) {
                throw runtime_error("Caravan N tried to move to a mountain.");
            }
            caravan->addXY(xToAdd, yToAdd, *this);
            caravan->decrementNrMovesLeft();
            for (const auto &item: items) {
                cout << "merda" << endl;
                item->applyEffect(*this);
            }
            return;
        }
    }
}

void Desert::sellCaravanNMerchandise(int caravanN) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN) {
            this->coins += caravan->getNrTonsMerch() * this->sellPriceMerchandise;
            caravan->setNrTonsMerch(0);
            return;
        }
    }
}

void Desert::createSandstorm(int l, int c, int r) {
    cout << "l: " << l << "c: " << c << "r: " << r << endl;
    int iMin = l - r;
    int iMax = l + r;
    int jMin = c - r;
    int jMax = c + r;

    for (int i = iMin; i <= iMax; i++) {
        for (int j = jMin; j <= jMax; j++) {
            for (auto it = caravans.begin(); it != caravans.end();) {
                if ((*it)->getX() == i && (*it)->getY() == j) {
                    if ((*it)->applySandstorm()) {
                        it = caravans.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
        }
    }
}

void Desert::destroyCaravanN(int caravanNId) {
    for (auto it = caravans.begin(); it != caravans.end(); ++it) {
        if ((*it)->getId() == caravanNId) {
            caravans.erase(it);
            break;
        }
    }
}

void Desert::coinsToAdd(int coinsAmount) {
    this->coins += coinsAmount;
}

void Desert::addCrewMembersTToCaravanN(int caravanN, int nrCrewMembersTToAdd) {
    for (const auto &caravan: caravans) {
        if (caravan->getId() == caravanN) {
            if ((caravan->getNrCrewMembers() + nrCrewMembersTToAdd) == caravan->getNrMaxCrewMembers()) {
                throw runtime_error("Adding N crew members to caravan N ultrapasses the limit.");
            }
            if ((caravan->getNrCrewMembers() + nrCrewMembersTToAdd) > caravan->getNrMaxCrewMembers()) {
                caravan->setNrCrewMembers(caravan->getNrMaxCrewMembers());
                throw runtime_error("Adding N crew members to caravan N ultrapasses the limit.");
            }
            caravan->setNrCrewMembers(caravan->getNrCrewMembers() + nrCrewMembersTToAdd);
            return;
        }
    }
}

bool Desert::readDataFromFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        ostringstream oss;
        oss << "Ficheiro " << fileName << "não existe." << endl;
        throw runtime_error(oss.str());
    }

    char character;
    string fileLine;

    file >> fileLine >> this->mapLines;

    file >> fileLine >> this->mapColumns;

    file.ignore(); //ignora o '\n'
    for (int i = 0; i < this->mapLines; i++) {
        getline(file, fileLine);
        for (int j = 0; j < this->mapColumns; j++) {
            character = fileLine[j];
            if (character == '+') {
                this->terrains.push_back(make_shared<Terrain>(MOUNTAIN, i, j));
            } else {
                this->terrains.push_back(make_shared<Terrain>(EMPTY, i, j));
            }
            if (character == '!') {
                this->caravans.push_back(make_shared<BarbarianCaravan>(i, j));
            }
            if (character >= 'a' && character <= 'z') {
                this->cities.push_back(make_shared<City>(character, i, j));
            }
            if (character >= '0' && character <= '9') {

                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<> distrib(0.0, 1.0);
                double randomNumber = distrib(gen);
                if (randomNumber <= 0.33) {
                    this->caravans.push_back(make_shared<CommerceCaravan>(i, j));
                } else if (randomNumber <= 0.66) {
                    this->caravans.push_back(make_shared<MilitarCaravan>(i, j));
                } else if (randomNumber <= 1.00) {
                    this->caravans.push_back(make_shared<HestiaCaravan>(i, j));
                }
            }
        }
    }
    file >> fileLine >> this->coins;

    file >> fileLine >> this->instancesBetweenNewItems;

    file >> fileLine >> this->itemDuration;

    file >> fileLine >> this->maxItems;

    file >> fileLine >> this->sellPriceMerchandise;
    for (const auto &city: cities) {
        city->setMerchSellCoinsValue(this->sellPriceMerchandise);
    }

    file >> fileLine >> this->buyPriceMerchandise;
    for (const auto &city: cities) {
        city->setMerchBuyCoinsValue(this->buyPriceMerchandise);
    }

    file >> fileLine >> this->caravanPrice;

    file >> fileLine >> this->instancesBetweenNewBarbarians;

    file >> fileLine >> this->barbariansDuration;

    file.close();

    return 1;
}

