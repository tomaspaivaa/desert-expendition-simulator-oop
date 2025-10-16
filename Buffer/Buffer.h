#ifndef TRABALHOPRATICO_POO_BUFFER_H
#define TRABALHOPRATICO_POO_BUFFER_H


#include <iostream>
#include <iomanip>  //setw

class Buffer {
public:
    Buffer() : lines(0), columns(0), cursorRow(0), cursorColumn(0), matrix(nullptr) {}

    Buffer(const Buffer &other);

    ~Buffer();

    void setLinesColumns(int lines, int column);

    void cleanBuffer(); // limpa a tela mas não reseta os dados do mapa
    void printTerminal();

    void moveCursor(int cursorLinha, int cursorColuna);

    void writeCurrentPos(char caracter); // escreve um caractere
    void writeCurrentPos(int numero);    // escreve um numero

    int getLines() const { return this->lines; }

    int getColumns() const { return this->columns; }

private:
    int lines, columns;
    char **matrix; //Em vez de definir uma matriz estática como char matriz[10][10],
    // usamos char** para criar matrizes cujo tamanho pode ser definido em tempo de execução.
    int cursorRow, cursorColumn; // posicão do cursor
};


#endif //TRABALHOPRATICO_POO_BUFFER_H
