#ifndef TRABALHOPRATICO_POO_MINE_H
#define TRABALHOPRATICO_POO_MINE_H

#include "./Item.h"

#include <memory>

class Desert;

class Mine : public Item {
public:
    Mine(int coordX, int coordY, int instancesLeft) : Item(instancesLeft, coordX, coordY) {}

    void applyEffect(Desert &desert) override;

};


#endif //TRABALHOPRATICO_POO_MINE_H
