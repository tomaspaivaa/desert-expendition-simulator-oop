#include <iostream>
#include <string>
#include <sstream>
#include "Interface.h"

using namespace std;

void Interface::startGame() {
    this->flagExit = false;
    while (!this->flagExit) {
        switch (this->desert.getGamePhase()) {
            case CONFIG_PHASE:
                configPhaseUi();
                break;

            case GAMING_PHASE:
                gamingPhaseUi();
                break;

                /*case END_PHASE:
                    endPhaseUi();
                    break;*/
        }
    }
}

vector<string> Interface::commandLineToWords() {
    string commandLine;
    string word;
    vector<string> words;
    words.clear();

    getline(cin, commandLine);

    stringstream ss(commandLine);

    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

void Interface::configPhaseUi() {
    bool readSuccess;
    vector<string> words;

    words.clear();
    cout << "[GAME] Indique se pretende sair ou dar config." << endl;

    words = commandLineToWords();

    if (!words.empty()) {
        if (words[0] == "config" && words.size() > 1) {
            readSuccess = true;
            try {
                this->desert.readDataFromFile(words[1]);
            } catch (const runtime_error &e) {
                readSuccess = false;
                cout << "[GAME] Erro " << e.what() << endl;
            }
        } else if (words[0] == "sair") {
            this->flagExit = true;
            cout << "[GAME] Fim do jogo!" << endl;
            return;
        }
    }

    if (readSuccess == true) {
        this->desert.endConfigPhase();
        return;
    }

    cout << "[GAME] Comando inválido. Tente novamente." << endl;
}

void Interface::updateBuffer() {
    this->buffer.setLinesColumns(desert.getMapLines(), desert.getMapColumns());
    this->buffer.moveCursor(0, 0);
    for (int i = 0; i < this->buffer.getLines(); i++) {
        for (int j = 0; j < this->buffer.getColumns(); j++) {
            shared_ptr<Cell> cell = this->desert.getXYInfo(i, j);
            auto city = static_pointer_cast<City>(cell);
            auto caravan = static_pointer_cast<Caravan>(cell);
            switch (cell->getCellType()) {
                case EMPTY:
                    this->buffer.writeCurrentPos('.');
                    break;

                case MOUNTAIN:
                    this->buffer.writeCurrentPos('+');
                    break;

                case ITEM:
                    this->buffer.writeCurrentPos('?');
                    break;

                case CITY:
                    this->buffer.writeCurrentPos(city->getName());
                    break;

                case CARAVAN:
                    this->buffer.writeCurrentPos(caravan->getId());
                    break;

                case BARBARIANCARAVAN:
                    this->buffer.writeCurrentPos('!');
                    break;
            }
        }
    }
    buffer.printTerminal();
}

string Interface::caravanTypeTostring(CaravanType c) {
    if (c == COMMERCE)
        return "comércio";
    if (c == MILITAR)
        return "militar";
    if (c == HESTIA)
        return "héstia";
    return nullptr;
}

void Interface::gamingPhaseUi() {
    updateBuffer();
    cout << "[GAME] \t############## TURNO " << desert.getinstancesCounter() << " ##############" << endl;
    cout << "[GAME] Indique que comando pretende fazer." << endl;

    userCommands(commandLineToWords());
}

void Interface::userCommands(vector<string> words) {
    int caravanId;
    int nrTonMerchandise;
    map<CaravanType, int> listCaravansInCityC;
    shared_ptr<Caravan> caravan;

    if (!gamingPhaseCommands.contains(words[0])) {
        cout << "[GAME] Usa um dos seguintes comandos permitidos:" << endl
             << "\t - exec <NomeFicheiro>" << endl
             << "\t - prox <n>" << endl
             << "\t - comprac <Cidade> <TipoCaravana>" << endl
             << "\t - precos" << endl
             << "\t - cidade <Cidade>" << endl
             << "\t - caravana <Caravana>" << endl
             << "\t - compra <Caravana> <ToneladasDeMercadoria>" << endl
             << "\t - vende <Caravana>" << endl
             << "\t - move <Movimento> <Direção>" << endl
             << "\t - auto <Caravana>" << endl
             << "\t - stop <Caravana>" << endl
             << "\t - barbaro <x> <y>" << endl
             << "\t - areia <x> <y> <Raio>" << endl
             << "\t - moedas <NumeroMoedas>" << endl
             << "\t - tripul <Caravana> <NumeroTripulantes>" << endl
             << "\t - saves <Nome>" << endl
             << "\t - loads <Nome>" << endl
             << "\t - lists" << endl
             << "\t - dels <Nome>" << endl
             << "\t - terminar" << endl;
        return;
    }
    switch (gamingPhaseCommands.at(words[0])) {
        case EXEC: {
            ifstream file(words[1]);
            if (!file.is_open()) {
                ostringstream oss;
                oss << "[GAME] O ficheiro " << words[1] << "não existe." << endl;
                break;
            }
            cout << "[GAME] A executar comandos do ficheiro " << words[1] << "." << endl;
            string fileLine;
            while (getline(file, fileLine)) {
                cout << "[GAME] A executar comando: " << fileLine << "\n";

                istringstream iss(fileLine);
                vector<string> fileWords;
                string word;
                while (iss >> word) {
                    fileWords.push_back(word);
                }

                if (fileWords.empty()) {
                    break;
                }
                userCommands(fileWords);
            }

            file.close();
            break;
        }

        case PROX:
            if (words.size() < 2) {
                this->desert.nextShift();
            } else {
                this->desert.nextShift(stoi(words[1]));
            }
            this->shiftCounter++;
            break;

        case COMPRAC:
            if (!this->desert.doesCityCExists(words[1][0])) {
                cout << "[GAME] A cidade " << words[1][0] << " não existe." << endl;
                break;
            }
            if (words[2][0] != 'C' && words[2][0] != 'M' && words[2][0] != 'S') {
                cout << "[GAME] O tipo de caravana " << words[2][0] << " não existe. Indique um correto: C, M ou S."
                     << endl;
                break;
            }
            try {
                this->desert.buyCaravanTOnCityC(words[2][0], words[1][0]);
            } catch (const runtime_error &e) {
                cout << "[GAME] A cidade " << words[1][0] << " não tem caravanas do tipo " << words[2][0]
                     << " para venda." << endl;
                break;
            }
            cout << "[GAME] Compraste uma caravana do tipo " << words[2][0] << " na cidade "
                 << words[1][0] << "." << endl;

            break;

        case PRECOS:
            cout << "[GAME] Lista dos preços das mercadorias: " << endl
                 << "\t - Compra: " << this->desert.getBuyMerchandise() << " moeda(s) por tonelada." << endl
                 << "\t - Venda: " << this->desert.getSellPriceMerchandise() << " moeda(s) por tonelada." << endl;
            break;

        case CIDADE:
            if (!this->desert.doesCityCExists(words[1][0])) {
                cout << "[GAME] A cidade " << words[1][0] << " não existe." << endl;
                break;
            }
            listCaravansInCityC = this->desert.listCaravansOnCityC(words[1][0]);
            cout << "[GAME] A cidade " << words[1][0] << " tem as seguintes caravanas para vendas: " << endl;
            for (const auto &[type, count]: listCaravansInCityC) {
                if (type == COMMERCE) {
                    cout << "\t - COMÉRCIO: " << count << endl;
                }
                if (type == MILITAR) {
                    cout << "\t - MILITAR: " << count << endl;
                }
                if (type == HESTIA) {
                    cout << "\t - HÉSTIA: " << count << endl;
                }
            }

            break;

        case CARAVANA:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            caravan = this->desert.listCaravanCDetails(caravanId);
            cout << "[GAME] A descrição da caravana " << caravanId << " tem os seguintes detalhes: " << endl
                 << "\t - Caravana do tipo: " << caravanTypeTostring(caravan->getCaravanType())
                 << endl
                 << "\t - Número de litros de água (MAX. " << caravan->getNrMaxLitersWater() << "): "
                 << caravan->getNrLitersWater() << endl
                 << "\t - Número de toneladas de mercadoria (MAX. " << caravan->getNrMaxTonsMerch() << "): "
                 << caravan->getNrTonsMerch() << endl
                 << "\t - Número de tripulantes (MAX. " << caravan->getNrMaxCrewMembers() << "): "
                 << caravan->getNrCrewMembers() << endl
                 << "\t - Está a operar automaticamente: " << caravan->getIsOperatingAutomatically() << endl;
            break;

        case COMPRA:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            if (!this->desert.isCaravanNOnCity(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não está numa cidade. Logo não pode comprar mercadoria."
                     << endl;
                break;
            }
            if (this->desert.doesCaravanNHasMaxMerch(caravanId)) {
                cout << "[GAME] Não é possível adicionar à caravana  " << caravanId << " as toneladas "
                     << nrTonMerchandise
                     << " de mercadoria, pois ela já tem o máximo de carga possível."
                     << endl;
            }
            nrTonMerchandise = stoi(words[2]);
            try {
                this->desert.addMerchMToCaravanN(nrTonMerchandise, caravanId);
            } catch (const runtime_error &e) {
                cout << "[GAME] Não é possível adicionar à caravana  " << caravanId << " as toneladas "
                     << nrTonMerchandise
                     << " de mercadoria, pois o utilizador não tem dinheiro."
                     << endl;
                break;
            }
            cout << "[GAME] Foi adicionada à caravana  " << caravanId << " as toneladas " << nrTonMerchandise
                 << " de mercadoria. Caso tenha tentado comprado mais mercadoria do que o máximo que a caravana suporta, compra até à carga máxima."
                 << endl;

            break;

        case VENDE:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            if (!this->desert.isCaravanNOnCity(caravanId)) {
                cout << "[GAME] A caravana " << caravanId
                     << " não está numa cidade. Logo não pode vender a sua mercadoria."
                     << endl;
                break;
            }
            desert.sellCaravanNMerchandise(caravanId);
            cout << "[GAME] A caravana " << caravanId << " vendeu toda a sua mercadoria." << endl;
            break;

        case MOVE:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            if (this->desert.isCaravanCOperatingAutomatically(caravanId)) {
                cout << "[GAME] A caravana " << caravanId
                     << " está a operar automaticamente, logo não pode ser movida manualmente." << endl;
                break;
            }
            if (words[2] != "D" && words[2] != "E" && words[2] != "C" && words[2] != "B" &&
                words[2] != "CE" && words[2] != "CD" && words[2] != "BE" && words[2] != "BD") {
                cout << "[GAME] A direção " << words[2] << " não está correta." << endl
                     << "\t Usa uma das seguintes: D, E, C, B, CE, CD, BE ou BD." << endl;
                break;
            }

            if (!this->desert.doesCaravanNHasMovesLeft(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " já esgotou os seus movimentos este turno." << endl;
                break;
            }

            try {
                this->desert.moveCaravanNToX(caravanId, words[2][0], words[2][1]);
            } catch (const runtime_error &e) {
                cout
                        << "[GAME] A posição para a qual queres mover a caravana é uma montanha ou uma caravana e não te podes mover para lá. Escolhe outra posição."
                        << endl;
                break;
            }
            cout << "[GAME] Moveste a caravana com sucesso para a posição que indicaste." << endl;

            break;

        case AUTO:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            try {
                this->desert.activateCaravanNAutoMode(caravanId);
            } catch (const runtime_error &e) {
                cout << "[GAME] A caravana " << caravanId << " já se encontra no modo automático." << endl;
                break;
            }
            cout << "[GAME] Foi ativado o modo automático da caravana " << caravanId << "." << endl;

            break;

        case STOP:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            try {
                this->desert.desactivateCaravanNAutoMode(caravanId);
            } catch (const runtime_error &e) {
                cout << "[GAME] A caravana " << caravanId << " já se encontra com modo auto desligado." << endl;
                break;
            }
            cout << "[GAME] O modo automático da caravana " << caravanId << " foi desativado com sucesso." << endl;

            break;

        case BARBARO:
            cout << "words" << words[1] << words[2] << endl;
            if (!this->desert.isCoordLREmpty(stoi(words[1]), stoi(words[2]))) {
                cout
                        << "[GAME] A coordenada que indicaste para criar uma caravana bárbara não é deserto. Indica uma coordenada de deserto."
                        << endl;
                break;
            }
            this->desert.createBarbarianCaravanLR(stoi(words[1]), stoi(words[2]));
            cout << "[GAME] Criaste uma caravana bárbara na coordenada (" << words[1] << ", " << words[2] << ")."
                 << endl;
            break;

        case AREIA:
            this->desert.createSandstorm(stoi(words[1]), stoi(words[2]), stoi(words[3]));

            cout << "[GAME]  Criaste uma tempestade de areia nas coordenadas (" << words[1] << ", "
                 << words[2] << "), com raio " << words[3] << "." << endl;

            break;

        case MOEDAS:
            this->desert.coinsToAdd(stoi(words[1]));
            cout << "[GAME] As moedas do jogador sofreram uma mudança! Novo valor: " << this->desert.getCoins() << endl;
            break;

        case TRIPUL:
            caravanId = stoi(words[1]);
            if (!this->desert.doesCaravanCExists(caravanId)) {
                cout << "[GAME] A caravana " << caravanId << " não existe." << endl;
                break;
            }
            if (!this->desert.isCaravanNOnCity(caravanId)) {
                cout << "[GAME] A caravana " << caravanId
                     << " não está numa cidade. Logo não pode adquirir novos tripulantes."
                     << endl;
                break;
            }
            try {
                this->desert.addCrewMembersTToCaravanN(caravanId, stoi(words[2]));
            } catch (const runtime_error &e) {
                cout
                        << "[GAME] O número de tripulantes excedia o máximo, e portanto, foram acrescentados o máximo de tripulantes até chegar ao seu limite."
                        << endl;
                break;
            }
            cout << "[GAME] Foram acrescentados " << words[2] << " tripulantes à caravana " << caravanId << "." << endl;
            break;

        case SAVES:
            if (words.size() > 1) {
                saveBuffer(words[1]);
                break;
            }
            cout << "[GAME] Indica o nome que queres dar à copia do buffer a salvar." << endl;
            break;

        case LOADS:
            if (words.size() > 1) {
                loadBuffer(words[1]);
                break;
            }
            break;

        case LISTS:
            listBuffers();
            break;

        case DELS:
            if (words.size() > 1) {
                deleteBuffer(words[1]);
                break;
            }

            break;

        case TERMINAR:
            desert.endGamingPhase();
            cout << "[GAME] Terminaste o jogo. A retornar à fase de configuração." << endl;
            break;

    }
}

void Interface::saveBuffer(const string &name) {
    if (savedBufferList.contains(name)) {
        cout << "[GAME] Já existe um buffer salvo com o nome " << name << "." << endl;
    } else {
        savedBufferList.insert({name, this->buffer});
        cout << "[GAME] Buffer salvo como " << name << "." << endl;
    }
}

void Interface::loadBuffer(const string &name) {
    auto it = savedBufferList.find(name);
    if (it != savedBufferList.end()) {
        it->second.printTerminal();
        cout << "[GAME] Buffer " << name << " carregado com sucesso." << endl;
    } else {
        cout << "[GAME] Nenhum buffer encontrado com o nome " << name << endl;
    }
}

void Interface::listBuffers() {
    if (savedBufferList.empty()) {
        cout << "[GAME] Não há buffers salvos." << endl;
        return;
    }
    cout << "[GAME] Buffers salvos:" << endl;
    for (const auto &pairBuffer: savedBufferList) {
        cout << "\t - " << pairBuffer.first << endl;
    }
}

void Interface::deleteBuffer(const string &name) {
    if (!savedBufferList.contains(name)) {
        cout << "[GAME] NÃO Removeste da lista o buffer " << name << "." << endl;
        return;
    }
    savedBufferList.erase(name);
    cout << "[GAME] Removeste da lista o buffer " << name << "." << endl;
}


