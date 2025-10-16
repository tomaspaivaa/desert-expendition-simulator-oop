#ifndef TRABALHOPRATICO_POO_PANDORASBOX_H
#define TRABALHOPRATICO_POO_PANDORASBOX_H

#include "./Item.h"

#include <memory>

class Desert;

class PandorasBox : public Item {
public:
    PandorasBox(int coordX, int coordY, int instancesLeft) : Item(instancesLeft, coordX, coordY) {}

    void applyEffect(Desert &desert) override;


private:
};


#endif //TRABALHOPRATICO_POO_PANDORASBOX_H
