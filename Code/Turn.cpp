#include "Turn.h"
#include <iostream>

Turn::Turn() : currentPlayer(nullptr), phase(Phase::MAIN) {}

Turn::Turn(Player& player) : currentPlayer(&player), phase(Phase::MAIN) {}

void Turn::nextPhase() {
    switch (phase) {
        case Phase::MAIN:
            phase = Phase::DISCARD;
            std::cout << "Phase -> DISCARD" << std::endl;
            break;
        case Phase::DISCARD:
            phase = Phase::DRAW;
            std::cout << "Phase -> DRAW" << std::endl;
            break;
        case Phase::DRAW:
            phase = Phase::MAIN;
            std::cout << "Phase -> MAIN (nouveau tour)" << std::endl;
            break;
    }
}

Player& Turn::getCurrentPlayer() const {
    if (currentPlayer == nullptr) {
        throw std::runtime_error("Aucun joueur assigné au tour !");
    }
    return *currentPlayer;
}

Phase Turn::getPhase() const {
    return phase;
}

void Turn::reset(Player& player) {
    currentPlayer = &player;
    phase = Phase::MAIN;
}
