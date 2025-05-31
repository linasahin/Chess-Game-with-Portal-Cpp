#pragma once

#include <map>
#include <string>
#include <vector>

struct Position {
    int x, y;
};

struct ChessPiece {
    std::string type;
    std::map<std::string, int> movement_int;
    std::map<std::string, bool> movement_bool;
    std::map<std::string, bool> special_abilities;
    std::map<std::string, std::vector<Position>> positions;
};

#include "json.hpp"

inline void from_json(const nlohmann::json& j, Position& pos) {
    j.at("x").get_to(pos.x);
    j.at("y").get_to(pos.y);
}

inline void from_json(const nlohmann::json& j, ChessPiece& p) {
    j.at("type").get_to(p.type);
    j.at("movement_int").get_to(p.movement_int);
    j.at("movement_bool").get_to(p.movement_bool);
    j.at("special_abilities").get_to(p.special_abilities);
    j.at("positions").get_to(p.positions);
}
