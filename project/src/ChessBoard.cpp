#include "ChessBoard.hpp"
#include <iostream>

void ChessBoard::initializeFromConfig(const GameConfig& config) {
    std::vector<ChessPiece> allPieces = config.pieces;
    allPieces.insert(allPieces.end(), config.custom_pieces.begin(), config.custom_pieces.end());

    for (const auto& piece : allPieces) {
        for (const auto& positionEntry : piece.positions) {
            const std::string& color = positionEntry.first;
            const std::vector<Position>& positions = positionEntry.second;
            for (const auto& pos : positions) {
                boardMap[{pos.x, pos.y}] = piece;
            }
        }
    }

    for (const auto& portal : config.portals) {
        std::string id = portal.id;
        portals[id] = portal;
        int entryX = portal.entryX;
        int entryY = portal.entryY;
        boardMap[{entryX, entryY}].type = "Portal";
    }
}

#include <iostream>
#include <map>

// ANSI escape codes for colors
#define RESET "\033[0m"
#define BLACK_BG "\033[40m"
#define WHITE_BG "\033[47m"
#define RED_TEXT "\033[31m"
#define BLUE_TEXT "\033[34m"

// Map piece types to symbols
std::map<std::string, char> whitePieces = {
    {"rook", '♖'}, {"knight", '♘'}, {"bishop", '♗'},
    {"queen", '♕'}, {"king", '♔'}, {"pawn", '♙'}
};

std::map<std::string, char> blackPieces = {
    {"rook", '♜'}, {"knight", '♞'}, {"bishop", '♝'},
    {"queen", '♛'}, {"king", '♚'}, {"pawn", '♟'}
};

void ChessBoard::displayBoard() {
    std::cout << "\n    a b c d e f g h\n";
    for (int y = 7; y >= 0; --y) {
        std::cout << " " << y + 1 << " ";
        for (int x = 0; x < 8; ++x) {
            bool isWhiteSquare = (x + y) % 2 == 0;
            std::string squareColor = isWhiteSquare ? WHITE_BG : BLACK_BG;

            std::cout << squareColor;

            auto it = boardMap.find({x, y});
            if (it != boardMap.end()) {
                const ChessPiece& piece = it->second;
                char symbol = '?';
                if (piece.positions.begin()->first == "white") {
                    if (whitePieces.count(piece.type)) {
                        symbol = whitePieces[piece.type];
                        std::cout << BLUE_TEXT;
                    }
                } else {
                    if (blackPieces.count(piece.type)) {
                        symbol = blackPieces[piece.type];
                        std::cout << RED_TEXT;
                    }
                }
                std::cout << " " << symbol << " " << RESET;
            } else {
                std::cout << "   " << RESET;
            }
        }
        std::cout << " " << y + 1 << "\n";
    }
    std::cout << "    a b c d e f g h\n";
}

ChessPiece* ChessBoard::getPieceAt(int x, int y) {
    auto it = boardMap.find({x, y});
    if (it != boardMap.end()) {
        return &it->second;
    }
    return nullptr;
}

void ChessBoard::movePiece(int fromX, int fromY, int toX, int toY) {
    auto it = boardMap.find({fromX, fromY});
    if (it != boardMap.end()) {
        ChessPiece piece = it->second;
        boardMap.erase(it);
        boardMap[{toX, toY}] = piece;
    }
}

void ChessBoard::placePiece(int x, int y, const ChessPiece& piece) {
    boardMap[{x, y}] = piece;
}

Portal* ChessBoard::getPortalAt(int x, int y) {
    for (auto& portalPair : portals) {
        auto& portal = portalPair.second;
        if (portal.entryX == x && portal.entryY == y) {
            return &portal;
        }
    }
    return nullptr;
}

void ChessBoard::applyPortalTeleportation(int& x, int& y, const std::string& color) {
    Portal* portal = getPortalAt(x, y);
    if (portal) {
        if (portal->cooldown == 0) {
            bool allowed = false;
            for (const auto& allowedColor : portal->allowed_colors) {
                if (allowedColor == color) {
                    allowed = true;
                    break;
                }
            }
            if (allowed) {
                movePiece(x, y, portal->exitX, portal->exitY);
                x = portal->exitX;
                y = portal->exitY;
                portal->cooldown += 1;
            }
        }
    }
}

void ChessBoard::updatePortalsCooldown() {
    for (auto& portalPair : portals) {
        auto& portal = portalPair.second;
        if (portal.cooldown > 0) {
            portal.cooldown--;
        }
    }
}

