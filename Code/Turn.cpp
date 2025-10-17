#include "Turn.h"
#include <iostream>

Turn::Turn() : phase(Phase::MAIN), goldReserve(0), combatReserve(0) {}


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