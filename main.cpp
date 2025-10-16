#include <iostream>
#include "Buffer/Buffer.h"
#include "Interface.h"

using namespace std;

int main() {
    Desert desert;
    Buffer buffer;
    Interface interface = Interface(desert, buffer);

    interface.startGame();

    return 0;
}
