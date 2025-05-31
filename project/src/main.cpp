#include "ConfigReader.hpp"
#include "GameManager.hpp"
#include <iostream>

int main() {
    GameConfig config;
    if (!loadConfig("data/chess_pieces.json", config)) {
        std::cerr << "Failed to load configuration.\n";
        return 1;
    }

    GameManager game(config);
    game.startGame();

    return 0;
}
