#ifndef TRABALHOPRATICO_POO_BARBARIANCARAVAN_H
#define TRABALHOPRATICO_POO_BARBARIANCARAVAN_H

#include "Caravan.h"

#include <random>
#include <sstream>

using namespace std;


class BarbarianCaravan : public Caravan {
public:
    BarbarianCaravan(int coordX, int coordY) : Caravan(1, -1, -1,
                                                       40, 60, true, BARBARIANCARAVAN, BARBARIAN, coordX, coordY) {}

    void autoMove(const Desert &desert) override;

    void nextShift() override;

    bool applySandstorm() override;

    bool isDead() override;

    bool isOnCombat(Desert &desert);

};


#endif //TRABALHOPRATICO_POO_BARBARIANCARAVAN_H
