#pragma once

#include "ChessBoard.hpp"
#include <queue>
#include <set>
#include <string>

class MoveValidator {
private:
    ChessBoard* board;

public:
    MoveValidator(ChessBoard* board);

    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::string& color);
};
