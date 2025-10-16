

#ifndef TRABALHOPRATICO_POO_COMERCECARAVAN_H
#define TRABALHOPRATICO_POO_COMERCECARAVAN_H

#include "./Caravan.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class CommerceCaravan : public Caravan {
public:
    CommerceCaravan(int coordX, int coordY) : Caravan(2, 200, 40,
                                                      20, 5, false, CARAVAN, COMMERCE, coordX,
                                                      coordY) {}

    void autoMove(const Desert &desert) override;

    void nextShift() override;

    bool applySandstorm() override;

    bool isDead() override;

};


#endif //TRABALHOPRATICO_POO_COMERCECARAVAN_H
