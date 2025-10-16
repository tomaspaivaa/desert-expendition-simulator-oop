#ifndef TRABALHOPRATICO_POO_OASIS_H
#define TRABALHOPRATICO_POO_OASIS_H

#include "./Item.h"

#include <memory>

class Desert;

class Oasis : public Item {
public:
    Oasis(int coordX, int coordY, int instancesLeft) : Item(instancesLeft, coordX, coordY) {}

    void applyEffect(Desert &desert) override;

};


#endif //TRABALHOPRATICO_POO_OASIS_H
