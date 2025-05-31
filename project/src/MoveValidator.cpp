#include "MoveValidator.hpp"
#include <cmath>

MoveValidator::MoveValidator(ChessBoard* board) : board(board) {}

bool MoveValidator::isValidMove(int fromX, int fromY, int toX, int toY, const std::string& color) {
    ChessPiece* startPiece = board->getPieceAt(fromX, fromY);
    if (!startPiece) return false;

    int boardSize = 8;
    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;

    q.push({fromX, fromY});
    visited.insert({fromX, fromY});

    while (!q.empty()) {
        std::pair<int, int> pos = q.front();
        int x = pos.first;
        int y = pos.second;
        q.pop();

        if (x == toX && y == toY) {
            board->movePiece(fromX, fromY, toX, toY);
            board->applyPortalTeleportation(toX, toY, color);
            return true;
        }

        std::vector<std::pair<int, int>> directions;

        if (startPiece->movement_int.count("forward") > 0) {
            int range = startPiece->movement_int.at("forward");
            for (int i = 1; i <= range; ++i) {
                if (y + i < boardSize) directions.push_back({x, y + i});
                if (y - i >= 0) directions.push_back({x, y - i});
            }
        }

        if (startPiece->movement_int.count("sideways") > 0) {
            int range = startPiece->movement_int.at("sideways");
            for (int i = 1; i <= range; ++i) {
                if (x + i < boardSize) directions.push_back({x + i, y});
                if (x - i >= 0) directions.push_back({x - i, y});
            }
        }

        if (startPiece->movement_int.count("diagonal") > 0) {
            int range = startPiece->movement_int.at("diagonal");
            for (int i = 1; i <= range; ++i) {
                if (x + i < boardSize && y + i < boardSize) directions.push_back({x + i, y + i});
                if (x - i >= 0 && y + i < boardSize) directions.push_back({x - i, y + i});
                if (x + i < boardSize && y - i >= 0) directions.push_back({x + i, y - i});
                if (x - i >= 0 && y - i >= 0) directions.push_back({x - i, y - i});
            }
        }

        if (startPiece->movement_bool.count("l_shape") && startPiece->movement_bool.at("l_shape")) {
            std::vector<std::pair<int, int>> knightMoves = {
                {x + 2, y + 1}, {x + 2, y - 1}, {x - 2, y + 1}, {x - 2, y - 1},
                {x + 1, y + 2}, {x - 1, y + 2}, {x + 1, y - 2}, {x - 1, y - 2}
            };
            for (auto move : knightMoves) {
                int nx = move.first;
                int ny = move.second;
                if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize) {
                    directions.push_back({nx, ny});
                }
            }
        }

        for (auto move : directions) {
            int nx = move.first;
            int ny = move.second;
            if (visited.count({nx, ny}) == 0) {
                ChessPiece* destPiece = board->getPieceAt(nx, ny);
                if (!destPiece) {
                    q.push({nx, ny});
                    visited.insert({nx, ny});

                    Portal* portal = board->getPortalAt(nx, ny);
                    if (portal && portal->cooldown == 0) {
                        bool allowed = false;
                        for (const auto& allowedColor : portal->allowed_colors) {
                            if (allowedColor == color) {
                                allowed = true;
                                break;
                            }
                        }
                        if (allowed) {
                            int ex = portal->exitX;
                            int ey = portal->exitY;
                            if (visited.count({ex, ey}) == 0) {
                                q.push({ex, ey});
                                visited.insert({ex, ey});
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
