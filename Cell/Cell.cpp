#include "Cell.h"
#include "../Desert/Desert.h"

void Cell::addXY(int xToAdd, int yToAdd, const Desert &desert) {
    this->x += xToAdd;
    this->y += yToAdd;
    if (this->x > desert.getMapLines() - 1) {
        this->x = this->x - desert.getMapLines();
    }
    if (this->y > desert.getMapColumns() - 1) {
        this->y = this->y - desert.getMapColumns();
    }
    if (this->x < 0) {
        this->x = this->x + desert.getMapLines();
    }
    if (this->y < 0) {
        this->y = this->y + desert.getMapColumns();
    }
}