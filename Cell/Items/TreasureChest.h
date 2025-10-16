#ifndef TRABALHOPRATICO_POO_TREASURECHEST_H
#define TRABALHOPRATICO_POO_TREASURECHEST_H

#include "./Item.h"

#include <memory>

class Desert;

class TreasureChest : public Item {
public:
    TreasureChest(int coordX, int coordY, int instancesLeft) : Item(instancesLeft, coordX, coordY) {}

    void applyEffect(Desert &desert) override;

};


#endif //TRABALHOPRATICO_POO_TREASURECHEST_H
