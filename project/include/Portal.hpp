#pragma once

#include <string>
#include <vector>

struct Portal {
    std::string id;
    int entryX, entryY;
    int exitX, exitY;
    std::vector<std::string> allowed_colors;
    int cooldown = 0;
};

#include "json.hpp"

inline void from_json(const nlohmann::json& j, Portal& p) {
    j.at("id").get_to(p.id);
    j.at("entryX").get_to(p.entryX);
    j.at("entryY").get_to(p.entryY);
    j.at("exitX").get_to(p.exitX);
    j.at("exitY").get_to(p.exitY);
    j.at("allowed_colors").get_to(p.allowed_colors);
}
