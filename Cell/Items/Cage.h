
#ifndef TRABALHOPRATICO_POO_CAGE_H
#define TRABALHOPRATICO_POO_CAGE_H

#include "./Item.h"

#include <memory>

class Desert;

class Cage : public Item {
public:
    Cage(int coordX, int coordY, int instancesLeft) : Item(instancesLeft, coordX, coordY) {}
    
    void applyEffect(Desert &desert) override;

};


#endif //TRABALHOPRATICO_POO_CAGE_H
