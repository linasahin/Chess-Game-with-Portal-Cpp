#pragma once

#include "ChessBoard.hpp"
#include "MoveValidator.hpp"
#include "MoveRecord.hpp"
#include "PortalCooldownManager.hpp"
#include <memory>
#include <stack>
#include <string>

class GameManager {
private:
    std::unique_ptr<ChessBoard> board;
    std::unique_ptr<MoveValidator> validator;
    std::stack<MoveRecord> moveHistory;
    PortalCooldownManager cooldownManager;

    std::string currentTurn;
    int turnCount;
    int maxTurns;

public:
    GameManager(const GameConfig& config);

    void startGame();
    void handleCommand(const std::string& command);
    void undoMove();
};
