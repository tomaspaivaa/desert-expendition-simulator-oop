
#ifndef TRABALHOPRATICO_POO_MILITARCARAVAN_H
#define TRABALHOPRATICO_POO_MILITARCARAVAN_H

#include "./Caravan.h"
#include <cstdlib>
#include <random>

class MilitarCaravan : public Caravan {
public:
    MilitarCaravan(int coordX, int coordY) : Caravan(3, 400, 5,
                                                     40, 7, false, CARAVAN, MILITAR, coordX, coordY) {}

    bool applySandstorm() override;

    void autoMove(const Desert &desert) override;

    void nextShift() override;

    bool isDead() override;

    void setLastMovement(int newLastXMovement, int newLastYMovement);

private:
    int lastXMovement;

    int lastYMovement;

};


#endif //TRABALHOPRATICO_POO_MILITARCARAVAN_H
