
#ifndef TRABALHOPRATICO_POO_INTERFACE_H
#define TRABALHOPRATICO_POO_INTERFACE_H

#include <fstream>
#include "Desert/Desert.h"
#include "Desert/GamePhaseEnum.h"
#include "GamingPhaseCommandsEnum.h"
#include "Buffer/Buffer.h"


class Interface {
public:
    Interface(Desert &desert, Buffer &buffer) : desert(desert), buffer(buffer) {}

    void startGame();

    void configPhaseUi();

    void gamingPhaseUi();

    void updateBuffer();
    
private:
    Desert &desert;

    Buffer &buffer;

    bool flagExit;

    int shiftCounter;

    map<string, Buffer> savedBufferList;

    void userCommands(vector<string> words);

    void saveBuffer(const string &name);

    void loadBuffer(const string &name);

    void listBuffers();

    void deleteBuffer(const string &name);

    vector<string> commandLineToWords();

    string caravanTypeTostring(CaravanType c);

    map<string, GAMING_PHASE_COMMANDS> gamingPhaseCommands = {
            {"exec",     EXEC},
            {"prox",     PROX},
            {"comprac",  COMPRAC},
            {"precos",   PRECOS},
            {"cidade",   CIDADE},
            {"caravana", CARAVANA},
            {"compra",   COMPRA},
            {"vende",    VENDE},
            {"move",     MOVE},
            {"auto",     AUTO},
            {"stop",     STOP},
            {"barbaro",  BARBARO},
            {"areia",    AREIA},
            {"moedas",   MOEDAS},
            {"tripul",   TRIPUL},
            {"saves",    SAVES},
            {"loads",    LOADS},
            {"lists",    LISTS},
            {"dels",     DELS},
            {"terminar", TERMINAR}
    };

};


#endif //TRABALHOPRATICO_POO_INTERFACE_H
