#pragma once

#include "ChessPiece.hpp"
#include "Portal.hpp"
#include "json.hpp"

struct GameSettings {
    int turn_limit;
};

struct GameConfig {
    GameSettings game_settings;
    std::vector<ChessPiece> pieces;
    std::vector<ChessPiece> custom_pieces;
    std::vector<Portal> portals;
};

bool loadConfig(const std::string& filename, GameConfig& config);

inline void from_json(const nlohmann::json& j, GameSettings& gs) {
    j.at("turn_limit").get_to(gs.turn_limit);
}
