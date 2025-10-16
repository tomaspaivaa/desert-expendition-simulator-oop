

#ifndef TRABALHOPRATICO_POO_HESTIACARAVAN_H
#define TRABALHOPRATICO_POO_HESTIACARAVAN_H

#include "./Caravan.h"

using namespace std;

class HestiaCaravan : public Caravan {
public:
    HestiaCaravan(int coordX, int coordY) : Caravan(1, 400, 150,
                                                    50, 20, false, CARAVAN, HESTIA, coordX,
                                                    coordY) {}


    void autoMove(const Desert &desert) override;

    void nextShift() override;

    bool applySandstorm() override;

    bool isDead() override;

};


#endif //TRABALHOPRATICO_POO_HESTIACARAVAN_H
