#include "Game.h"
#include <iostream>

Game::Game() : market(), settings(), currentTurn() {}

void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

void Game::start() {
    std::cout << "Démarrage de la partie..." << std::endl;

    // Initialisation des joueurs
    for (auto& player : players) {
        // setup initial (deck de base, PV etc.)
        std::cout << "Initialisation du joueur: " << player.getName() << std::endl;
    }

    // Initialisation du marché
    std::cout << "Initialisation du marché..." << std::endl;

    // Premier tour
    if (!players.empty()) {
        currentTurn = Turn(players[0]); // commence avec le joueur 1
    }
}

void Game::playTurn() {
    std::cout << "Tour du joueur: " << currentTurn.getCurrentPlayer().getName() << std::endl;

    // Ici tu enchaînes les phases MAIN / DISCARD / DRAW via currentTurn
    currentTurn.nextPhase();

    // à compléter avec logique du tour (jouer cartes, acheter, attaquer, etc.)
}

void Game::endGame() {
    std::cout << "Fin de la partie !" << std::endl;
    // Ici tu peux afficher le vainqueur
}

std::vector<Player>& Game::getPlayers() {
    return players;
}

Market& Game::getMarket() {
    return market;
}

GameSettings& Game::getSettings() {
    return settings;
}
