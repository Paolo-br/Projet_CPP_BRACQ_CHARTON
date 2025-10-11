#include "Turn.h"
#include <iostream>

Turn::Turn() : currentPlayer(nullptr), phase(Phase::MAIN), goldReserve(0), combatReserve(0) {}

Turn::Turn(Player& player) : currentPlayer(&player), phase(Phase::MAIN), goldReserve(0), combatReserve(0) {}

// 1. Destructeur
Turn::~Turn() {
    std::cout << "Destructeur Turn" << std::endl;
    // Pas de delete car currentPlayer est géré ailleurs
}

// 2. Constructeur de copie
Turn::Turn(const Turn& other)
    : currentPlayer(other.currentPlayer), phase(other.phase),
      goldReserve(other.goldReserve), combatReserve(other.combatReserve) {
    std::cout << "Constructeur copie Turn" << std::endl;
}

// 3. Opérateur d'affectation copie
Turn& Turn::operator=(const Turn& other) {
    std::cout << "Opérateur affectation copie Turn" << std::endl;
    
    if (this != &other) {
        currentPlayer = other.currentPlayer;
        phase = other.phase;
        goldReserve = other.goldReserve;
        combatReserve = other.combatReserve;
    }
    return *this;
}

// 4. Constructeur de déplacement
Turn::Turn(Turn&& other) noexcept
    : currentPlayer(other.currentPlayer), phase(other.phase),
      goldReserve(other.goldReserve), combatReserve(other.combatReserve) {
    std::cout << "Constructeur déplacement Turn" << std::endl;
    
    // Mettre l'autre objet dans un état valide
    other.currentPlayer = nullptr;
    other.phase = Phase::MAIN;
    other.goldReserve = 0;
    other.combatReserve = 0;
}

// 5. Opérateur d'affectation déplacement
Turn& Turn::operator=(Turn&& other) noexcept {
    std::cout << "Opérateur affectation déplacement Turn" << std::endl;
    
    if (this != &other) {
        currentPlayer = other.currentPlayer;
        phase = other.phase;
        goldReserve = other.goldReserve;
        combatReserve = other.combatReserve;
        
        // Mettre l'autre objet dans un état valide
        other.currentPlayer = nullptr;
        other.phase = Phase::MAIN;
        other.goldReserve = 0;
        other.combatReserve = 0;
    }
    return *this;
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
    goldReserve = 0;
    combatReserve = 0;
}

void Turn::addGold(int amount) {
    goldReserve += amount;
}

void Turn::addCombat(int amount) {
    combatReserve += amount;
}

int Turn::getGoldReserve() {
    return goldReserve;
}

int Turn::getCombatReserve(){
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