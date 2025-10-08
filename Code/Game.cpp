#include "Game.h"
#include <iostream>

// Constructeur
Game::Game() : market(), settings(), currentTurn() {}

// Ajout d’un joueur
void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

// Démarrage de la partie
void Game::start() {
    std::cout << "\n=== Démarrage de la partie ===" << std::endl;

    if (players.size() < 2) {
        std::cerr << "Erreur : il faut au moins 2 joueurs pour commencer !" << std::endl;
        return;
    }

    // Initialisation des joueurs
    for (auto& player : players) {
        std::cout << "Initialisation du joueur : " << player.getName() << std::endl;
        player.setHealth(50);   
        player.setGold(0);      
        // TODO : initialiser le deck de base ici si pas déjà fait
    }

    // Initialisation du marché
    std::cout << "\nInitialisation du marché..." << std::endl;
    market.initializeBaseSet();

    // Premier tour
    std::cout << "\nLe joueur " << players[0].getName() << " commence la partie !" << std::endl;
    currentTurn = Turn(players[0]); // commence avec le joueur 1
}

// Exécution d’un tour complet
void Game::playTurn() {
    if (players.empty()) {
        std::cerr << "Erreur : aucun joueur n’a été ajouté." << std::endl;
        return;
    }

    Player& activePlayer = currentTurn.getCurrentPlayer();
    std::cout << "\n--- Tour du joueur : " << activePlayer.getName() << " ---" << std::endl;

    // PHASE 1 : Main phase (jouer cartes, acheter, etc.)
    currentTurn.nextPhase();
    std::cout << "[Phase principale] Le joueur joue ses cartes..." << std::endl;
    // TODO : appeler du style activePlayer.playCards() 

    // PHASE 2 : Discard + Draw
    std::cout << "[Phase de défausse et pioche]" << std::endl;
    // TODO : activePlayer.discardHand(); activePlayer.draw(5);

    // Vérifier la fin de partie après le tour
    if (checkEndCondition()) {
        endGame();
        return;
    }

    // Passer au joueur suivant
    advanceTurn();
}

// Passage au joueur suivant
void Game::advanceTurn() {
    static size_t turnIndex = 0;
    turnIndex = (turnIndex + 1) % players.size();
    currentTurn = Turn(players[turnIndex]);
    std::cout << "\n>>> Prochain tour : " << currentTurn.getCurrentPlayer().getName() << " <<<" << std::endl;
}

// Fin de la partie
void Game::endGame() {
    std::cout << "\n=== Fin de la partie ===" << std::endl;

    Player* winner = nullptr;
    int maxHealth = -1;

    for (auto& p : players) {
        if (p.getHealth() > maxHealth) {
            maxHealth = p.getHealth();
            winner = &p;
        }
    }

    if (winner) {
        std::cout << "Vainqueur : " << winner->getName()
                  << " avec " << winner->getHealth() << " PV !" << std::endl;
    }
    else {
        std::cout << "Match nul !" << std::endl;
    }
}

// Vérifie les conditions de fin de partie
bool Game::checkEndCondition() const {
    int aliveCount = 0;
    for (const auto& p : players) {
        if (p.getHealth() > 0) aliveCount++;
    }
    return aliveCount <= 1; // fin si 1 joueur restant
}

// === Getters ===
std::vector<Player>& Game::getPlayers() { return players; }
Market& Game::getMarket() { return market; }
GameSettings& Game::getSettings() { return settings; }
