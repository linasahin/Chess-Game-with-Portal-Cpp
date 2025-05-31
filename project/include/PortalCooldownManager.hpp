#pragma once

#include "Portal.hpp"
#include <queue>
#include <memory>

struct CooldownEntry {
    std::string portalId;
    int remainingTurns;

    CooldownEntry(const std::string& id, int cooldown)
        : portalId(id), remainingTurns(cooldown) {}
};

class PortalCooldownManager {
private:
    std::queue<CooldownEntry> cooldownQueue;

public:
    void addCooldown(const std::string& portalId, int cooldown);
    void updateCooldowns();
    bool isInCooldown(const std::string& portalId) const;
};
