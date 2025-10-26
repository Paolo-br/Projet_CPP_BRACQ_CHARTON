#include "Turn.h"
#include <iostream>

Turn::Turn() : phase(Phase::MAIN), goldReserve(0), combatReserve(0), opponent(nullptr),
               nextCardGoesOnTop(false), nextActionGoesOnTop(false), nextCardGoesInHand(false) {
    factionsPlayedThisTurn.clear();
    allyAbilitiesTriggeredThisTurn.clear();
}


void Turn::nextPhase() {
    switch (phase) {
        case Phase::MAIN:
            phase = Phase::DISCARD;
            std::cout << "Phase de Défausse" << std::endl;
            break;
        case Phase::DISCARD:
            phase = Phase::DRAW;
            std::cout << "Phase de Pioche" << std::endl;
            break;
        case Phase::DRAW:
            phase = Phase::MAIN;
            std::cout << "Nouveau tour - Phase Principale" << std::endl;
            break;
    }
}

Phase Turn::getPhase() const {
    return phase;
}

void Turn::reset() {
    phase = Phase::MAIN;
    goldReserve = 0;
    combatReserve = 0;
    factionsPlayedThisTurn.clear();
    allyAbilitiesTriggeredThisTurn.clear();
    nextCardGoesOnTop = false;
    nextActionGoesOnTop = false;
    nextCardGoesInHand = false;
}

void Turn::addGold(int amount) {
    goldReserve += amount;
}

void Turn::addCombat(int amount) {
    combatReserve += amount;
}

int Turn::getGoldReserve() const {
    return goldReserve;
}

int Turn::getCombatReserve() const {
    return combatReserve;
}

void Turn::spendGold(int amount) {
    if (amount <= goldReserve) {
        goldReserve -= amount;
    }
}

void Turn::spendCombat(int amount) {
    if (amount <= combatReserve) {
        combatReserve -= amount;
    }
}

void Turn::clearReserves() {
    goldReserve = 0;
    combatReserve = 0;
}

// Gestion de l'adversaire
void Turn::setOpponent(Player* opp) {
    opponent = opp;
}

Player* Turn::getOpponent() const {
    return opponent;
}

bool Turn::hasOpponent() const {
    return opponent != nullptr;
}

// Gestion des factions jouées (pour capacités Alliées)
void Turn::addFactionPlayed(Faction faction) {
    if (faction != Faction::None) {
        factionsPlayedThisTurn.insert(faction);
        std::cout << "  → Faction " << factionToString(faction) << " jouée ce tour" << std::endl;
    }
}

bool Turn::hasFactionBeenPlayed(Faction faction) const {
    return factionsPlayedThisTurn.find(faction) != factionsPlayedThisTurn.end();
}

void Turn::clearFactionsPlayed() {
    factionsPlayedThisTurn.clear();
}

int Turn::getFactionCount(Faction faction) const {
    return factionsPlayedThisTurn.count(faction);
}

// Gestion des capacités Alliées déjà déclenchées
void Turn::markAllyAbilityTriggered(Faction faction) {
    if (faction != Faction::None) {
        allyAbilitiesTriggeredThisTurn.insert(faction);
        std::cout << "  → Capacités Alliées " << factionToString(faction) << " marquées comme déclenchées" << std::endl;
    }
}

bool Turn::hasAllyAbilityBeenTriggered(Faction faction) const {
    return allyAbilitiesTriggeredThisTurn.find(faction) != allyAbilitiesTriggeredThisTurn.end();
}

void Turn::clearAllyAbilitiesTriggered() {
    allyAbilitiesTriggeredThisTurn.clear();
}

// Gestion des effets Guild de manipulation du deck
void Turn::setNextCardGoesOnTop(bool value) {
    nextCardGoesOnTop = value;
}

void Turn::setNextActionGoesOnTop(bool value) {
    nextActionGoesOnTop = value;
}

void Turn::setNextCardGoesInHand(bool value) {
    nextCardGoesInHand = value;
}

bool Turn::getNextCardGoesOnTop() const {
    return nextCardGoesOnTop;
}

bool Turn::getNextActionGoesOnTop() const {
    return nextActionGoesOnTop;
}

bool Turn::getNextCardGoesInHand() const {
    return nextCardGoesInHand;
}

void Turn::resetAcquireFlags() {
    nextCardGoesOnTop = false;
    nextActionGoesOnTop = false;
    nextCardGoesInHand = false;
}
