#pragma once

#include "ChessPiece.hpp"
#include <optional>

struct MoveRecord {
    int fromX, fromY;
    int toX, toY;
    ChessPiece movedPiece;
    std::optional<ChessPiece> capturedPiece;

    MoveRecord(int fx, int fy, int tx, int ty, ChessPiece moved, std::optional<ChessPiece> captured)
        : fromX(fx), fromY(fy), toX(tx), toY(ty), movedPiece(moved), capturedPiece(captured) {}
};
