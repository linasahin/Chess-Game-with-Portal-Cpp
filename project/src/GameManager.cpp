#include "GameManager.hpp"
#include <iostream>
#include <sstream>

GameManager::GameManager(const GameConfig& config) {
    board = std::make_unique<ChessBoard>();
    board->initializeFromConfig(config);
    validator = std::make_unique<MoveValidator>(board.get());
    currentTurn = "white";
    turnCount = 0;
    maxTurns = config.game_settings.turn_limit;
}

void GameManager::startGame() {
    std::string input;
    std::cout << "Game started! Enter commands: move x1 y1 x2 y2, display, undo, quit\n";
    while (turnCount < maxTurns && std::getline(std::cin, input)) {
        handleCommand(input);
        board->updatePortalsCooldown();
    }
    std::cout << "Game ended after " << turnCount << " turns.\n";
}

void GameManager::handleCommand(const std::string& command) {
    if (command == "display") {
        board->displayBoard();
        return;
    }
    if (command == "quit") {
        std::exit(0);
    }
    if (command == "undo") {
        undoMove();
        return;
    }
    if (command.rfind("move", 0) == 0) {
        std::istringstream iss(command);
        std::string cmd;
        int x1, y1, x2, y2;
        iss >> cmd >> x1 >> y1 >> x2 >> y2;
        if (validator->isValidMove(x1, y1, x2, y2, currentTurn)) {
            ChessPiece* movedPiece = board->getPieceAt(x1, y1);
            ChessPiece* capturedPiece = board->getPieceAt(x2, y2);

            moveHistory.push(MoveRecord(
                x1, y1, x2, y2,
                *movedPiece,
                capturedPiece ? std::optional<ChessPiece>(*capturedPiece) : std::nullopt
            ));

            Portal* portal = board->getPortalAt(x2, y2);
            if (portal && portal->cooldown == 1) {
                cooldownManager.addCooldown(portal->id, portal->cooldown);
            }

            if (capturedPiece && capturedPiece->special_abilities.count("royal") && capturedPiece->special_abilities.at("royal")) {
                std::cout << currentTurn << " wins by capturing the royal piece!\n";
                std::exit(0);
            }

            std::cout << "Move accepted.\n";
            currentTurn = (currentTurn == "white") ? "black" : "white";
            turnCount++;
        } else {
            std::cout << "Invalid move for " << currentTurn << ".\n";
        }
        return;
    }
    std::cout << "Unknown command.\n";
}

void GameManager::undoMove() {
    if (moveHistory.empty()) {
        std::cout << "No moves to undo.\n";
        return;
    }
    MoveRecord lastMove = moveHistory.top();
    moveHistory.pop();
    board->movePiece(lastMove.toX, lastMove.toY, lastMove.fromX, lastMove.fromY);
    if (lastMove.capturedPiece.has_value()) {
        board->placePiece(lastMove.toX, lastMove.toY, lastMove.capturedPiece.value());
    }
    currentTurn = (currentTurn == "white") ? "black" : "white";
    --turnCount;
    std::cout << "Undo successful.\n";
}
