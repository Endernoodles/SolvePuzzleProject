#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "move.h"

class boardT {
    public:
    boardT();
    boardT(std::string argv);
    void execute(moveT thisMove);
    bool isBoardSolvable() const;
    void setHashKey();
    int getHashKey() const;
    int getTile(int row, int col) const;
    int getDepth() const;

    typedef std::vector<moveT>::iterator iterator;
    iterator begin() { return pathToBoard.begin();}
    iterator end() { return pathToBoard.end();}

    friend std::ostream& operator<<(std::ostream& os, const boardT& dt);
    bool operator==(const boardT& otherBoard) const;

    private:
    int calculateHashKey();
    int board[3][3];
    int key;
    std::vector<moveT> pathToBoard;

};

boardT::boardT(std::string argv) {
     if (argv.size() != 9) {
        std::cerr << "Invalid board configuration! Board must have 9 digits." << std::endl;
        exit(1); // Exit if the configuration is invalid.
    }
    
    int index = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = argv[index] - '0';
            index++;
        }
    }
    key = calculateHashKey();  
}

bool boardT::isBoardSolvable() const {
    std::vector<int> tiles;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] != 0) {
                tiles.push_back(board[row][col]);
            }
        }
    }

    int countInversions = 0;
    for (size_t i = 0; i < tiles.size(); ++i) {
        for (size_t j = i + 1; j < tiles.size(); ++j) {
            if (tiles[i] > tiles[j]) {
                ++countInversions;
            }
        }
    }

    return (countInversions % 2) == 0;
}

std::ostream& operator<<(std::ostream& os, const boardT& thisBoard) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            os << thisBoard.board[row][col] << ' ';
        }
        std::cout << std::endl; 
    }
    return os; 
}
bool boardT::operator==(const boardT& otherBoard) const {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != otherBoard.board[row][col]) {
                return false;
            }
        }
    }
    return true;
}
void boardT::execute(moveT thisMove) {
    int emptyRow = -1, emptyCol = -1;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == 0) {
                emptyRow = row;
                emptyCol = col;
                break;
            }
        }
    }

    int toRow = thisMove.getToRow();
    int toCol = thisMove.getToCol();

    if (toRow >= 0 && toRow < 3 && toCol >= 0 && toCol < 3) {
        std::swap(board[emptyRow][emptyCol], board[toRow][toCol]);
    } else {
        std::cerr << "Invalid move!" << std::endl;
    }
    setHashKey();
}

int boardT::getDepth() const {
    return pathToBoard.size();
}
int boardT::getTile(int row, int col) const {
    return board[row][col];
}
void boardT::setHashKey() {
    key = calculateHashKey();
}

int boardT::getHashKey() const {
    return key;
}

int boardT::calculateHashKey() {
    int hash = 0;
    int factor = 1;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            hash += board[row][col] * factor;
            factor *= 10;
        }
    }
    return hash;
}

boardT::boardT() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = 0;
        }
    }
    key = calculateHashKey();
}