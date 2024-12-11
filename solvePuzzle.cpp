#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include "board.h"
#include "move.h"

std::vector<moveT> generateMoves(const boardT& board) {
    std::vector<moveT> moves;
    int emptyRow = -1, emptyCol = -1;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board.getTile(row, col) == 0) {
                emptyRow = row;
                emptyCol = col;
                break;
            }
        }
    }

    int deltas[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int dr = deltas[i][0];
        int dc = deltas[i][1];
        int newRow = emptyRow + dr;
        int newCol = emptyCol + dc;

        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            moves.push_back(moveT(emptyRow, emptyCol, newRow, newCol));
        }
    }

    return moves;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./solvePuzzle <initial_board_configuration>" << std::endl;
        return 1;
    }

    std::string initialConfig = argv[1];
    boardT initialBoard(initialConfig);
    boardT goalBoard("123456780");  // Goal state for the puzzle

    if (!initialBoard.isBoardSolvable()) {
        std::cout << "Initial board is not solvable!" << std::endl;
        return 0;
    }

    std::queue<boardT> toVisit;
    std::unordered_map<int, boardT> visited;
    std::unordered_map<int, std::vector<moveT>> solutionPaths;
    int movesConsidered = 0;

    toVisit.push(initialBoard);
    visited[initialBoard.getHashKey()] = initialBoard;
    solutionPaths[initialBoard.getHashKey()] = {};  // Start with an empty solution path

    while (!toVisit.empty()) {
        boardT currentBoard = toVisit.front();
        toVisit.pop();

        int currentKey = currentBoard.getHashKey();

        std::cout << "Exploring board (hashKey: " << currentKey << "):" << std::endl;
        std::cout << currentBoard << std::endl;

        if (currentBoard == goalBoard) {
            std::cout << "Goal board reached!" << std::endl;
            std::cout << "Moves considered: " << movesConsidered << std::endl;
            std::cout << "Visited board size = " << visited.size() << std::endl;
            for (const auto& move : solutionPaths[currentKey]) {
                std::cout << move << std::endl;
            }
            return 0;
        }

        for (const auto& move : generateMoves(currentBoard)) {
            boardT successorBoard = currentBoard;
            successorBoard.execute(move);

            int successorKey = successorBoard.getHashKey();

            if (visited.find(successorKey) == visited.end()) {
                toVisit.push(successorBoard);
                visited[successorKey] = successorBoard;

                // Add the current move to the solution path for the successor
                solutionPaths[successorKey] = solutionPaths[currentKey];
                solutionPaths[successorKey].push_back(move);
            }
        }

        movesConsidered++;
    }

    std::cout << "Goal not found!" << std::endl;
    return -1;
}

