#include "Game.h"
#include "Player.h"
#include "Market.h"
#include "Turn.h"
#include "GameSettings.h"
#include "Card.h"
#include "ActionCard.h"
#include "ItemCard.h"
#include "ChampionCard.h"

#include <iostream>

// Constructeur
Game::Game() 
    : m_players(), m_market(), m_settings(), m_currentTurn(),
      m_currentPlayerIndex(0), m_gameStarted(false), m_gameEnded(false) {}

// 1. Destructeur
Game::~Game() {
    std::cout << "Destructeur Game" << std::endl;
}

// 2. Constructeur copie
Game::Game(const Game& other)
    : m_players(other.m_players), m_market(other.m_market),
      m_settings(other.m_settings), m_currentTurn(other.m_currentTurn),
      m_currentPlayerIndex(other.m_currentPlayerIndex),
      m_gameStarted(other.m_gameStarted), m_gameEnded(other.m_gameEnded) {
    std::cout << "Constructeur copie Game" << std::endl;
}

// 3. Opérateur affectation copie
Game& Game::operator=(const Game& other) {
    if (this != &other) {
        m_players = other.m_players;
        m_market = other.m_market;
        m_settings = other.m_settings;
        m_currentTurn = other.m_currentTurn;
        m_currentPlayerIndex = other.m_currentPlayerIndex;
        m_gameStarted = other.m_gameStarted;
        m_gameEnded = other.m_gameEnded;
    }
    std::cout << "Opérateur affectation copie Game" << std::endl;
    return *this;
}

// 4. Constructeur déplacement
Game::Game(Game&& other) noexcept
    : m_players(std::move(other.m_players)),
      m_market(std::move(other.m_market)),
      m_settings(std::move(other.m_settings)),
      m_currentTurn(std::move(other.m_currentTurn)),
      m_currentPlayerIndex(other.m_currentPlayerIndex),
      m_gameStarted(other.m_gameStarted),
      m_gameEnded(other.m_gameEnded) {
    other.m_currentPlayerIndex = 0;
    other.m_gameStarted = false;
    other.m_gameEnded = false;
    std::cout << "Constructeur déplacement Game" << std::endl;
}

// 5. Opérateur affectation déplacement
Game& Game::operator=(Game&& other) noexcept {
    if (this != &other) {
        m_players = std::move(other.m_players);
        m_market = std::move(other.m_market);
        m_settings = std::move(other.m_settings);
        m_currentTurn = std::move(other.m_currentTurn);
        m_currentPlayerIndex = other.m_currentPlayerIndex;
        m_gameStarted = other.m_gameStarted;
        m_gameEnded = other.m_gameEnded;
        
        other.m_currentPlayerIndex = 0;
        other.m_gameStarted = false;
        other.m_gameEnded = false;
    }
    std::cout << "Opérateur affectation déplacement Game" << std::endl;
    return *this;
}


void Game::addPlayer(const Player& player) {
    if (!m_gameStarted) {
        m_players.push_back(player);
        std::cout << "Joueur " << player.getName() << " ajouté à la partie." << std::endl;
    } else {
        std::cerr << "Impossible d'ajouter un joueur : la partie a déjà commencé." << std::endl;
    }
}



// Démarrage de la partie
void Game::start() {
    std::cout << "\n=== DÉMARRAGE DE LA PARTIE HERO REALMS ===" << std::endl;

    if (m_players.size() < 2) {
        std::cerr << "Erreur : il faut au moins 2 joueurs pour commencer !" << std::endl;
        return;
    }

    // Initialisation des joueurs selon les règles
    for (size_t i = 0; i < m_players.size(); ++i) {
        Player& player = m_players[i];
        std::cout << "Initialisation de " << player.getName() << std::endl;
        player.setHealth(50); 
        player.initializeStarterDeck();  
        // Distribution des mains de départ selon les règles
        if (i == 0) {
            // Premier joueur : 3 cartes
            player.drawCards(3);
        } else {
            // Autres joueurs : 5 cartes
            player.drawCards(5);
        }
        std::cout << "• " << player.getName() << " : " << player.getHealth() << " PV" << std::endl;
    }

    // Initialisation du marché
    std::cout << "\nInitialisation du marché..." << std::endl;
    m_market.initializeBaseSet();

    // Premier tour
    m_gameStarted = true;
    m_currentPlayerIndex = 0;
    m_currentTurn = Turn();  // Initialiser le tour (pas besoin de passer le joueur)
    
    std::cout << "\nLa partie commence ! " << m_players[m_currentPlayerIndex].getName() << " joue en premier." << std::endl;
    std::cout << "==========================================" << std::endl;
    displayGameState();
}







// Exécution d’un tour complet
void Game::playTurn() {
    if (!m_gameStarted || m_gameEnded) {
        std::cerr << "La partie n'est pas en cours." << std::endl;
        return;
    }

    Player& activePlayer =  getCurrentPlayer();
    std::cout << "\n--- Tour du joueur : " << activePlayer.getName() << " ---" << std::endl;

    // PHASE 1 : Phase Principale
    std::cout << "\n--- PHASE PRINCIPALE ---" << std::endl;
    mainPhase();

    // PHASE 2 : Phase de Défausse
    std::cout << "\n--- PHASE DE DÉFAUSSE ---" << std::endl;
    discardPhase();

    // PHASE 3 : Phase de Pioche
    std::cout << "\n--- PHASE DE PIOCHE ---" << std::endl;
    drawPhase();

    // Vérifier la fin de partie
    if (checkEndCondition()) {
        endGame();
        return;
    }

    // Passer au joueur suivant
    advanceTurn();
}





void Game::mainPhase() {
    Player& activePlayer = getCurrentPlayer();
    m_mainPhaseActive = true;

    //Mon petit rappel car j'ai aucune mémoire:
    // Le joueur peut effectuer ces actions dans n'importe quel ordre :
    // 1. Jouer des cartes de sa main
    // 2. Activer des capacités de ses cartes en jeu
    // 3. Utiliser l'Or pour acquérir des cartes
    // 4. Utiliser le Combat pour attaquer
    
 std::cout << "\nPHASE PRINCIPALE - " << activePlayer.getName() << std::endl;
    std::cout << "Ressources disponibles: " << m_currentTurn.getGoldReserve() << " d'Or et " 
              << m_currentTurn.getCombatReserve() << " de combat " << std::endl;

    // Le joueur peut effectuer des actions tant qu'il le souhaite pendant la phase principale
    while (m_mainPhaseActive && !activePlayer.isEliminated()) {
        displayMainPhaseOptions();
        
        int choice;
        std::cout << "Choisissez une action: ";
        std::cin >> choice;
        
        if (choice == 0) {
            // Fin de la phase principale
            m_mainPhaseActive = false;
            std::cout << "Fin de la phase principale." << std::endl;
        } else {
            handleMainPhaseChoice(choice);
        }
        
        // Vérifier si un joueur a été éliminé
        if (checkEndCondition()) {
            m_mainPhaseActive = false;
            break;
        }
    }
}

void Game::displayMainPhaseOptions() {
    Player& activePlayer = getCurrentPlayer();
    
    std::cout << "\n--- OPTIONS PHASE PRINCIPALE ---" << std::endl;
    std::cout << "1. Jouer une carte de ma main (" << activePlayer.getHand().size() << " cartes)" << std::endl;
    std::cout << "2. Activer une capacité de Champion" << std::endl;
    std::cout << "3. Utiliser une capacité Allié" << std::endl;
    std::cout << "4. Sacrifier une carte" << std::endl;
    std::cout << "5. Acheter des cartes du marché (" << m_currentTurn.getGoldReserve() << "d'OR disponibles)" << std::endl;
    std::cout << "6. Attaquer (" << m_currentTurn.getCombatReserve() << "de Combat disponibles)" << std::endl;
    std::cout << "0. Terminer la phase principale" << std::endl;
}

void Game::handleMainPhaseChoice(int choice) {
    switch (choice) {
        case 1:
            playCardsPhase();
            break;
        case 2:
            //activateAbilitiesPhase();
            break;
        case 3:
            //useAllyAbilitiesPhase();
            break;
        case 4:
            //sacrificeCardsPhase();
            break;
        case 5:
            acquireCardsPhase();
            break;
        case 6:
            combatPhase();
            break;
        default:
            std::cout << "Option invalide!" << std::endl;
            break;
    }
}

void Game::playCardFromHand(int handIndex) {
    Player& activePlayer = getCurrentPlayer();
    Hand& hand = activePlayer.getHand();

    if (handIndex < 0 || handIndex >= static_cast<int>(hand.size())) {
        std::cout << "Index de carte invalide!" << std::endl;
        return;
    }

    Card* card = hand.getCardAt(handIndex);
    if (!card) {
        std::cout << "Erreur: Carte introuvable!" << std::endl;
        return;
    }

    std::cout << activePlayer.getName() << " joue: " << card->getName() << std::endl;

    // Appliquer les effets de la carte
    card->executeEffects(activePlayer, m_currentTurn);

    // Gérer le type de carte avec dynamic_cast
    if (auto* actionCard = dynamic_cast<ActionCard*>(card)) {
        // C'est une Action - va en zone de jeu temporaire
        activePlayer.addCardToPlayArea(actionCard);
        std::cout << actionCard->getName() << " (Action) est maintenant en jeu." << std::endl;

    } else if (auto* itemCard = dynamic_cast<ItemCard*>(card)) {
        // C'est un Objet - va en zone de jeu temporaire
        activePlayer.addCardToPlayArea(itemCard);
        std::cout << itemCard->getName() << " (Objet) est maintenant en jeu." << std::endl;

    } else if (auto* championCard = dynamic_cast<ChampionCard*>(card)) {
        // C'est un Champion - reste en jeu
        activePlayer.addChampionToPlayArea(*championCard);
        std::cout << championCard->getName() << " rejoint vos Champions!" << std::endl;

    } else {
        // Type inconnu (ne devrait pas arriver si toutes les cartes sont bien typées)
        std::cout << "Type de carte inconnu: " << card->getName() << std::endl;
    }

    // Retirer la carte de la main
    hand.removeCardAt(handIndex);
}


void Game::playCardsPhase() {
    Player& activePlayer = getCurrentPlayer();
    Hand& hand = activePlayer.getHand();
    
    if (hand.isEmpty()) {
        std::cout << "Votre main est vide!" << std::endl;
        return;
    }
    
    std::cout << "\n--- JOUER UNE CARTE ---" << std::endl;
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << i + 1 << ". " <<hand.getCardAt(i)->getName() << " - " 
                  << hand.getCardAt(i)->getType() << std::endl;
    }
    std::cout << "0. Retour" << std::endl;
    
    int choice;
    std::cout << "Choisissez une carte à jouer: ";
    std::cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(hand.size())) {
        playCardFromHand(choice - 1);
    }
}




void Game::combatPhase() {
    if (m_currentTurn.getCombatReserve() <= 0) {
        std::cout << "Vous n'avez pas de Combat à utiliser!" << std::endl;
        return;
    }

    std::cout << "\n--- PHASE DE COMBAT ---" << std::endl;
    std::cout << "Combat disponible: " << m_currentTurn.getCombatReserve() << "⚔️" << std::endl;

    // Afficher les cibles possibles
    for (size_t i = 0; i < m_players.size(); ++i) {
        if (&m_players[i] != &getCurrentPlayer() && !m_players[i].isEliminated()) {
            std::cout << i + 1 << ". " << m_players[i].getName()
                      << " (" << m_players[i].getHealth() << " PV)";

            if (m_players[i].hasGuardInPlay()) {
                std::cout << " [PROTÉGÉ PAR UN GARDE]";
            }
            std::cout << std::endl;

            // Afficher les Champions de ce joueur
            std::vector<ChampionCard> champions = m_players[i].getPlayArea().getChampions();
            for (size_t j = 0; j < champions.size(); ++j) {
                std::cout << "   " << (j + 1) << ". " << champions[j].getName()
                          << " (" << champions[j].getDefense() << " défense)";
                if (champions[j].isGuard()) {
                    std::cout << " [GARDE]";
                }
                std::cout << std::endl;
            }
        }
    }
    std::cout << "0. Retour" << std::endl;

    int choice;
    std::cout << "Choisissez une cible: ";
    std::cin >> choice;

    if (choice == 0) return;

    // Gérer l'attaque
    if (choice > 0 && choice <= static_cast<int>(m_players.size())) {
        Player& targetPlayer = m_players[choice - 1];
        if (targetPlayer.hasGuardInPlay()) {
            std::cout << "Vous devez d'abord assommer le Garde!" << std::endl;
            // Logique pour cibler le Garde
        } else {
            int combatUsed;
            std::cout << "Combien de Combat utiliser? ";
            std::cin >> combatUsed;
            if (combatUsed <= m_currentTurn.getCombatReserve()) {
                m_currentTurn.spendCombat(combatUsed);
                targetPlayer.takeDamage(combatUsed);
                std::cout << "Attaque réussie! " << targetPlayer.getName()
                          << " a maintenant " << targetPlayer.getHealth() << " PV." << std::endl;
            } else {
                std::cout << "Pas assez de Combat!" << std::endl;
            }
        }
    }
}


void Game::acquireCardsPhase() {
    if (m_currentTurn.getGoldReserve() <= 0) {
        std::cout << "Vous n'avez pas d'Or à dépenser!" << std::endl;
        return;
    }
    
    std::cout << "\n--- ACHAT DE CARTES ---" << std::endl;
    std::cout << "Or disponible: " << m_currentTurn.getGoldReserve() << "💰" << std::endl;
    m_market.displayMarket();
    
    std::cout << "0. Retour" << std::endl;
    
    int choice;
    std::cout << "Choisissez une carte à acheter: ";
    std::cin >> choice;
    
    if (choice > 0 && choice <= m_market.getVisibleCardsCount()) {
        acquireCardFromMarket(choice - 1);
    }
}

void Game::acquireCardFromMarket(int marketIndex) {
    Player& activePlayer = getCurrentPlayer();
    auto availableCards = m_market.getVisibleCards();

    if (marketIndex < 0 || marketIndex >= static_cast<int>(availableCards.size())) {
        std::cout << "Index de marché invalide!" << std::endl;
        return;
    }

    Card* card = availableCards[marketIndex];
    int cost = card->getCost();

    if (m_currentTurn.getGoldReserve() >= cost) {
        m_currentTurn.spendGold(cost);
        activePlayer.acquireCard(card);
        m_market.removeCardFromMarket(card);
        std::cout << activePlayer.getName() << " acquiert: " << card->getName() << std::endl;
    } else {
        std::cout << "Or insuffisant! Coût: " << cost << "💰, Vous avez: "
                  << m_currentTurn.getGoldReserve() << "💰" << std::endl;
    }
}


void Game::discardPhase() {
    Player& activePlayer = getCurrentPlayer();
    
    // 1. Perdre tout l'Or et Combat restants
    m_currentTurn.clearReserves();
    
    // 2. Défausser tous les Objets et Actions en jeu
    // (Les Champions restent en jeu)
    
    // 3. Défausser toute la main
    activePlayer.discardHand();
    
    // 4. Mobiliser tous les Champions
    activePlayer.mobilizeChampions();
    
    std::cout << activePlayer.getName() << " défausse sa main et mobilise ses Champions." << std::endl;
}

void Game::drawPhase() {
    Player& activePlayer = getCurrentPlayer();
    
    // Piocher 5 cartes
    activePlayer.drawCards(5);
    
    std::cout << activePlayer.getName() << " pioche 5 cartes." << std::endl;
    
    // Fin du tour
    std::cout << "Fin du tour de " << activePlayer.getName() << std::endl;
}



// Passage au joueur suivant
void Game::advanceTurn() {
    // Passer au joueur suivant en utilisant m_currentPlayerIndex
    m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.size();
    
    // Reset le tour pour le nouveau joueur
    m_currentTurn.reset();
    
    std::cout << "\n>>> Prochain tour : " << getCurrentPlayer().getName() << " <<<" << std::endl;
}

// Fin de la partie
void Game::endGame() {
    std::cout << "\n=== FIN DE LA PARTIE ===" << std::endl;
    m_gameEnded = true;
    
    Player* winner = getWinner();
    if (winner) {
        std::cout << "VAINQUEUR : " << winner->getName() 
                  << " avec " << winner->getHealth() << " PV ! 🎉" << std::endl;
    } else {
        std::cout << "Match nul !" << std::endl;
    }
    
    displayGameState();
}

// Vérifie les conditions de fin de partie
bool Game::checkEndCondition() const {
    int aliveCount = 0;
    for (const auto& player : m_players) {
        if (!player.isEliminated()) {
            aliveCount++;
        }
    }
    return aliveCount <= 1; // Fin si 1 joueur ou moins reste
}

Player* Game::getWinner() const {
    Player* winner = nullptr;
    for (const auto& player : m_players) {
        if (!player.isEliminated()) {
            if (winner == nullptr || player.getHealth() > winner->getHealth()) {
                winner = const_cast<Player*>(&player);
            }
        }
    }
    return winner;
}


void Game::displayGameState() const {
    std::cout << "\n=== ÉTAT DE LA PARTIE ===" << std::endl;
    for (const auto& player : m_players) {
        player.displayStatus();
    }
}

// Getters
std::vector<Player>& Game::getPlayers() { return m_players; }
Market& Game::getMarket() { return m_market; }
GameSettings& Game::getSettings() { return m_settings; }
Turn& Game::getCurrentTurn() { return m_currentTurn; }
Player& Game::getCurrentPlayer() { return m_players[m_currentPlayerIndex]; }
Player& Game::getNextPlayer() {
    int nextIndex = (m_currentPlayerIndex + 1) % m_players.size();
    return m_players[nextIndex];
}
bool Game::isGameOver() const { return m_gameEnded; }