#include "ConfigReader.hpp"
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
#include <stdexcept>

bool isValidPosition(int x, int y, int boardSize) {
    return x >= 0 && x < boardSize && y >= 0 && y < boardSize;
}

bool isValidColor(const std::string& color) {
    return color == "white" || color == "black";
}

bool loadConfig(const std::string& filename, GameConfig& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    json j = json::parse(file);

    config.game_settings = j.at("game_settings").get<GameSettings>();
    config.pieces = j.at("pieces").get<std::vector<ChessPiece>>();
    config.custom_pieces = j.at("custom_pieces").get<std::vector<ChessPiece>>();
    config.portals = j.at("portals").get<std::vector<Portal>>();

    int boardSize = 8;

    for (const auto& piece : config.pieces) {
        for (const auto& posEntry : piece.positions) {
            const std::string& color = posEntry.first;
            if (!isValidColor(color)) {
                throw std::runtime_error("Invalid color: " + color);
            }
            for (const auto& pos : posEntry.second) {
                if (!isValidPosition(pos.x, pos.y, boardSize)) {
                    throw std::runtime_error("Invalid piece position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
                }
            }
        }
    }

    for (const auto& piece : config.custom_pieces) {
        for (const auto& posEntry : piece.positions) {
            const std::string& color = posEntry.first;
            if (!isValidColor(color)) {
                throw std::runtime_error("Invalid color in custom piece: " + color);
            }
            for (const auto& pos : posEntry.second) {
                if (!isValidPosition(pos.x, pos.y, boardSize)) {
                    throw std::runtime_error("Invalid custom piece position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
                }
            }
        }
    }

    for (const auto& portal : config.portals) {
        if (!isValidPosition(portal.entryX, portal.entryY, boardSize)) {
            throw std::runtime_error("Invalid portal entry position: (" + std::to_string(portal.entryX) + ", " + std::to_string(portal.entryY) + ")");
        }
        if (!isValidPosition(portal.exitX, portal.exitY, boardSize)) {
            throw std::runtime_error("Invalid portal exit position: (" + std::to_string(portal.exitX) + ", " + std::to_string(portal.exitY) + ")");
        }
        for (const auto& color : portal.allowed_colors) {
            if (!isValidColor(color)) {
                throw std::runtime_error("Invalid allowed color in portal: " + color);
            }
        }
    }

    return true;
}
