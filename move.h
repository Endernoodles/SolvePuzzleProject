#pragma once

#include <iostream>

class moveT {
    public:
    moveT(int fromRow, int fromCol, int toRow, int toCol) {
        this->fromRow = fromRow;
        this->fromCol = fromCol;
        this->toRow = toRow;
        this->toCol = toCol;
    }
    int getFromRow() {
        return fromRow;
    }
    int getFromCol() {
        return fromCol;
    }
    int getToRow() {
        return toRow;
    }
    int getToCol() {
        return toCol;
    }

    friend std::ostream& operator<<(std::ostream& os, const moveT& dt);

    private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

std::ostream& operator<<(std::ostream& os, const moveT& move) {
    os << "(" << move.fromRow << ", " << move.fromCol << ")->" << move.toRow << ", " << move.toCol << ")";
    return os;
}

