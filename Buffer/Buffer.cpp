#include "Buffer.h"

using namespace std;

Buffer::Buffer(const Buffer &other)
        : lines(other.lines), columns(other.columns), cursorRow(other.cursorRow), cursorColumn(other.cursorColumn) {
    matrix = new char *[lines];
    for (int i = 0; i < lines; ++i) {
        matrix[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

Buffer::~Buffer() {
    for (int i = 0; i < lines; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Buffer::setLinesColumns(int newLines, int newColumns) {
    this->lines = newLines;
    this->columns = newColumns;

    if (matrix != nullptr) {
        for (int i = 0; i < this->lines; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    matrix = new char *[lines];
    for (int i = 0; i < lines; ++i) {
        matrix[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = '.'; // preenche todas as células com espaço em branco
        }
    }
}

//fazemos esta funcao porque pode ser necessário "resetar" o buffer para o estado inicial sem destruir e recriar o objeto Buffer.
void Buffer::cleanBuffer() {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = ' ';
        }
    }
    cursorRow = cursorColumn = 0;  // Reseta o cursor
}

void Buffer::printTerminal() {
    cout << "  ";
    for (int j = 0; j < columns; ++j) {
        cout << setw(4) << j;  // Usa setw(4) para garantir mais espaço entre os números das colunas
    }
    cout << endl;

    // Impressão das linhas com índices e conteúdo
    for (int i = 0; i < lines; ++i) {
        cout << setw(2) << i << " | ";  // Alinha o índice da linha e adiciona uma barra separadora
        for (int j = 0; j < columns; ++j) {
            cout << matrix[i][j] << "   ";  // Adiciona mais espaçamento entre os caracteres
        }
        cout << endl;  // Nova linha após imprimir uma linha do buffer
    }
}


//verifica se as coordenadas do cursor estão dentro do tabuleiro
void Buffer::moveCursor(int linha, int coluna) {
    if (linha >= 0 && linha < lines && coluna >= 0 && coluna < columns) {
        cursorRow = linha;
        cursorColumn = coluna;
    }
}

//enunciado: desloca o cursor para caracter seguinte ao último impresso
void Buffer::writeCurrentPos(char caracter) {
    if ((cursorRow >= 0 && cursorRow < lines) && (cursorColumn >= 0 && cursorColumn < columns)) {
        matrix[cursorRow][cursorColumn] = caracter;
        ++cursorColumn;
        if (cursorColumn == columns) {
            cursorColumn = 0;
            ++cursorRow;
        }
    }
}

void Buffer::writeCurrentPos(int numero) {
    char ola = '0' + numero;

    writeCurrentPos(ola); // escreve a string
}