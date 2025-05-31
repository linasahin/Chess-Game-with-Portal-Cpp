#include "PortalCooldownManager.hpp"

void PortalCooldownManager::addCooldown(const std::string& portalId, int cooldown) {
    cooldownQueue.push(CooldownEntry(portalId, cooldown));
}

void PortalCooldownManager::updateCooldowns() {
    int n = cooldownQueue.size();
    for (int i = 0; i < n; ++i) {
        CooldownEntry entry = cooldownQueue.front();
        cooldownQueue.pop();
        entry.remainingTurns--;
        if (entry.remainingTurns > 0) {
            cooldownQueue.push(entry);
        }
    }
}

bool PortalCooldownManager::isInCooldown(const std::string& portalId) const {
    std::queue<CooldownEntry> temp = cooldownQueue;
    while (!temp.empty()) {
        if (temp.front().portalId == portalId) {
            return true;
        }
        temp.pop();
    }
    return false;
}
