#pragma once

#include "ChessPiece.hpp"
#include "Portal.hpp"
#include "ConfigReader.hpp"
#include <map>
#include <string>

class ChessBoard {
private:
    std::map<std::pair<int, int>, ChessPiece> boardMap;
    std::map<std::string, Portal> portals;

public:
    void initializeFromConfig(const GameConfig& config);
    void displayBoard();
    ChessPiece* getPieceAt(int x, int y);
    void movePiece(int fromX, int fromY, int toX, int toY);
    void placePiece(int x, int y, const ChessPiece& piece);
    void applyPortalTeleportation(int& x, int& y, const std::string& color);
    Portal* getPortalAt(int x, int y);
    void updatePortalsCooldown();
};
