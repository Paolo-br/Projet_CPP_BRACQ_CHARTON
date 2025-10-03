#include "GameSettings.h"

GameSettings::GameSettings() : godMode(false) {}

void GameSettings::enableGodMode() {
    godMode = true;
}

void GameSettings::disableGodMode() {
    godMode = false;
}

bool GameSettings::isGodModeEnabled() const {
    return godMode;
}
