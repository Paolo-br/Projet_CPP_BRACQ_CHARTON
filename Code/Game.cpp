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
#include <limits>

// Fonction utilitaire pour lire un choix de manière sécurisée
namespace {
    int readChoice(const std::string& prompt = "Votre choix: ") {
        int choice;
        while (true) {
            std::cout << prompt;
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "❌ Entrée invalide ! Veuillez entrer un nombre." << std::endl;
                continue;
            }
            
            // Ignorer le reste de la ligne
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

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

    Player& activePlayer = getCurrentPlayer();
    Player& opponent = getNextPlayer(); // Récupère l'adversaire
    
    // Définir l'adversaire pour ce tour (pour les effets qui ciblent l'adversaire)
    m_currentTurn.setOpponent(&opponent);
    
    std::cout << "\n--- Tour du joueur : " << activePlayer.getName() << " ---" << std::endl;
    std::cout << "    (Adversaire: " << opponent.getName() << ")" << std::endl;

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
        
        int choice = readChoice("Choisissez une action: ");
        
        if (choice == 0) {
            // Fin de la phase principale
            m_mainPhaseActive = false;
            std::cout << "\n✓ Fin de la phase principale." << std::endl;
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
    InPlayArea& playArea = activePlayer.getPlayArea();
    
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║       QUE VOULEZ-VOUS FAIRE ?                 ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    
    // État actuel
    std::cout << "📊 État: ";
    std::cout << "Main: " << activePlayer.getHand().size() << " | ";
    std::cout << "💰: " << m_currentTurn.getGoldReserve() << " | ";
    std::cout << "⚔️: " << m_currentTurn.getCombatReserve() << " | ";
    std::cout << "♟️: " << playArea.getChampionCount() << std::endl;
    std::cout << "───────────────────────────────────────────────" << std::endl;
    
    // Options
    std::cout << "[1] 🎴 Jouer une carte de ma main";
    if (activePlayer.getHand().isEmpty()) {
        std::cout << " (Vide)";
    } else {
        std::cout << " (" << activePlayer.getHand().size() << ")";
    }
    std::cout << std::endl;
    
    std::cout << "[2] ⚡ Activer un Champion";
    if (playArea.getChampionCount() == 0) {
        std::cout << " (Aucun)";
    }
    std::cout << std::endl;
    
    std::cout << "[3] 🤝 Utiliser une capacité Alliée" << std::endl;
    std::cout << "[4] 💀 Sacrifier une carte" << std::endl;
    
    std::cout << "[5] 🛒 Acheter au marché";
    if (m_currentTurn.getGoldReserve() == 0) {
        std::cout << " (Pas d'Or)";
    } else {
        std::cout << " (" << m_currentTurn.getGoldReserve() << " 💰)";
    }
    std::cout << std::endl;
    
    std::cout << "[6] ⚔️  Attaquer";
    if (m_currentTurn.getCombatReserve() == 0) {
        std::cout << " (Pas de Combat)";
    } else {
        std::cout << " (" << m_currentTurn.getCombatReserve() << " ⚔️)";
    }
    std::cout << std::endl;
    
    std::cout << "[7] 📚 Voir ma défausse (" << activePlayer.getDiscardPile().size() << " cartes)" << std::endl;
    std::cout << "[8] 💀 Voir ma Zone de Sacrifice (" << activePlayer.getSacrificeZone().size() << " cartes)" << std::endl;
    std::cout << "[9] 👁️  Voir la défausse d'un adversaire" << std::endl;
    
    std::cout << "───────────────────────────────────────────────" << std::endl;
    std::cout << "[0] Terminer mon tour" << std::endl;
    std::cout << "═══════════════════════════════════════════════" << std::endl;
}

void Game::handleMainPhaseChoice(int choice) {
    switch (choice) {
        case 1:
            playCardsPhase();
            break;
        case 2:
            activateAbilitiesPhase();
            break;
        case 3:
            useAllyAbility("");  // Sera demandé interactivement
            break;
        case 4:
            sacrificeCard("");  // Sera demandé interactivement
            break;
        case 5:
            acquireCardsPhase();
            break;
        case 6:
            combatPhase();
            break;
        case 7:
            viewDiscardPile();
            break;
        case 8:
            viewSacrificeZone();
            break;
        case 9:
            viewOpponentDiscardPile();
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
    
    // Enregistrer la faction jouée pour les capacités Alliées
    Faction cardFaction = card->getFaction();
    if (cardFaction != Faction::None) {
        bool wasAlreadyPlayed = m_currentTurn.hasFactionBeenPlayed(cardFaction);
        m_currentTurn.addFactionPlayed(cardFaction);
        
        // Si c'est la 2ème+ carte de cette faction ET que les capacités Allié n'ont pas encore été déclenchées
        if (!wasAlreadyPlayed) {
            std::cout << "  → Première carte " << factionToString(cardFaction) << " jouée ce tour" << std::endl;
        } else if (!m_currentTurn.hasAllyAbilityBeenTriggered(cardFaction)) {
            std::cout << "  → 🤝 DÉCLENCHEMENT DES CAPACITÉS ALLIÉES " << factionToString(cardFaction) << "!" << std::endl;
            triggerAllyAbilities(cardFaction);
            // Marquer que les capacités Allié de cette faction ont été déclenchées
            m_currentTurn.markAllyAbilityTriggered(cardFaction);
        } else {
            std::cout << "  → 2+ cartes " << factionToString(cardFaction) << " en jeu (capacités Allié déjà déclenchées ce tour)" << std::endl;
        }
    }

    // Appliquer les effets principaux de la carte
    card->executeEffects(activePlayer, m_currentTurn);

    // Gérer le type de carte avec dynamic_cast
    if (auto* actionCard = dynamic_cast<ActionCard*>(card)) {
        // C'est une Action - va en zone de jeu temporaire
        activePlayer.addCardToPlayArea(actionCard);
        std::cout << "→ " << actionCard->getName() << " (Action) entre en jeu" << std::endl;
        
        // Vérifier les capacités Alliées
        if (actionCard->hasAllyAbility()) {
            std::cout << "  💡 Cette carte a une capacité Alliée" << std::endl;
        }

    } else if (auto* itemCard = dynamic_cast<ItemCard*>(card)) {
        // C'est un Objet - va en zone de jeu temporaire
        activePlayer.addCardToPlayArea(itemCard);
        std::cout << itemCard->getName() << "entre en jeu" << std::endl;

    } else if (auto* championCard = dynamic_cast<ChampionCard*>(card)) {
        // C'est un Champion - reste en jeu
        championCard->play(activePlayer, getNextPlayer());
        activePlayer.addChampionToPlayArea(*championCard);
        
        // Vérifier les capacités
        if (championCard->hasActivateAbility()) {
            std::cout << "  ⚡ Capacité d'activation disponible (activable ce tour)" << std::endl;
        }
        if (championCard->hasAllyAbility()) {
            std::cout << "  💡 Capacité Alliée disponible" << std::endl;
        }

    } else {
        // Type inconnu (ne devrait pas arriver si toutes les cartes sont bien typées)
        std::cout << "Type de carte inconnu: " << card->getName() << std::endl;
    }

    // Retirer la carte de la main
    hand.removeCardAt(handIndex);
    
    // Afficher l'état des ressources après avoir joué la carte
    std::cout << "Or: " << m_currentTurn.getGoldReserve() 
              << " | Combat: " << m_currentTurn.getCombatReserve() << std::endl;

}


void Game::playCardsPhase() {
    Player& activePlayer = getCurrentPlayer();
    Hand& hand = activePlayer.getHand();
    
    if (hand.isEmpty()) {
        std::cout << "\nVotre main est vide!" << std::endl;
        return;
    }
    
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           VOTRE MAIN                          ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    

    // Afficher avec les fonctions de raph
    for (size_t i = 0; i < hand.size(); ++i) {
        Card* card = hand.getCardAt(i);        
        std::cout <<card->getName()<< std::endl;
    }
     
    std::cout << "[0] ← Retour" << std::endl;
    
    int choice = readChoice("Choisissez une carte à jouer: ");
    
    if (choice > 0 && choice <= static_cast<int>(hand.size())) {
        playCardFromHand(choice - 1);
    } else if (choice != 0) {
        std::cout << "❌ Choix invalide!" << std::endl;
    }
}




void Game::combatPhase() {
    if (m_currentTurn.getCombatReserve() <= 0) {
        std::cout << "Vous n'avez pas de Combat à utiliser!" << std::endl;
        return;
    }

    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            PHASE DE COMBAT                    ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    std::cout << "Combat disponible: " << m_currentTurn.getCombatReserve() <<std::endl;

    // Afficher les adversaires et leurs champions
    std::cout << "CIBLES DISPONIBLES:" << std::endl;
    
    for (size_t i = 0; i < m_players.size(); ++i) {
        if (&m_players[i] != &getCurrentPlayer() && !m_players[i].isEliminated()) {
            Player& target = m_players[i];
            
            // Afficher le joueur
            std::cout << "\n[" << (i + 1) << "] 👤 " << target.getName()
                      << " - " << target.getHealth() << " PV";
            
            if (target.hasGuardInPlay()) {
                std::cout << " [PROTÉGÉ]";
            }
            std::cout << std::endl;

            // Afficher les Champions de ce joueur avec les codes de raph
            std::vector<ChampionCard>& champions = target.getPlayArea().getChampions();
            if (!champions.empty()) {
                std::cout << "  Champions:" << std::endl;
                for (size_t j = 0; j < champions.size(); ++j) {
                    ChampionCard& champion = champions[j];
                    std::cout << champion.getName() << std::endl;
                }
            }
        }
    }
    
    std::cout << "\n[0] ← Retour" << std::endl;

    int playerChoice;
    std::cout << "\nChoisissez un adversaire à attaquer: ";
    std::cin >> playerChoice;

    if (playerChoice == 0) return;
    
    if (playerChoice < 1 || playerChoice > static_cast<int>(m_players.size())) {
        std::cout << "Choix invalide!" << std::endl;
        return;
    }

    Player& targetPlayer = m_players[playerChoice - 1];
    
    if (&targetPlayer == &getCurrentPlayer()) {
        std::cout << "Vous ne pouvez pas vous attaquer vous-même!" << std::endl;
        return;
    }
    
    if (targetPlayer.isEliminated()) {
        std::cout << "Ce joueur est déjà éliminé!" << std::endl;
        return;
    }

    // Vérifier s'il y a des Gardes
    bool hasGuard = targetPlayer.hasGuardInPlay();
    std::vector<ChampionCard>& champions = targetPlayer.getPlayArea().getChampions();
    
    // Si pas de champions, attaquer directement le joueur
    if (champions.empty()) {
        int combatUsed;
        std::cout << "\n Attaque sur " << targetPlayer.getName() << std::endl;
        std::cout << "Combien de Combat utiliser? (Max: " 
                  << m_currentTurn.getCombatReserve() << "): ";
        std::cin >> combatUsed;
        
        if (combatUsed > 0 && combatUsed <= m_currentTurn.getCombatReserve()) {
            m_currentTurn.spendCombat(combatUsed);
            targetPlayer.takeDamage(combatUsed);
            std::cout << "Attaque réussie! " << targetPlayer.getName()
                      << " perd " << combatUsed << " PV → " 
                      << targetPlayer.getHealth() << " PV restants" << std::endl;
        } else {
            std::cout << "Quantité de Combat invalide!" << std::endl;
        }
        return;
    }
    
    // S'il y a des Gardes, le joueur ne peut pas être attaqué directement
    if (hasGuard) {
        std::cout << targetPlayer.getName() 
                  << " est protégé par un GARDE!" << std::endl;
        std::cout << "Vous devez d'abord assommer les Gardes!\n" << std::endl;
    }
    
    // Afficher les champions attaquables
    std::cout << "Choisissez un Champion à attaquer:" << std::endl;
    for (size_t i = 0; i < champions.size(); ++i) {
        ChampionCard& champion = champions[i];
        if (!champion.isStunned()) {
            // Si des Gardes existent, afficher les Gardes
            if (hasGuard && !champion.isGuard()) {
                continue; // Sauter les non-Gardes
            }
            
            std::cout << (i + 1) << ". " << champion.getName()
                      << " (" << champion.getRemainingDefense() << " Def)";
            if (champion.isGuard()) {
                std::cout << " [GARDE]";
            }
            std::cout << std::endl;
        }
    }
    
    // Option d'attaquer le joueur si pas de Garde
    if (!hasGuard) {
        std::cout << "P. Attaquer " << targetPlayer.getName() 
                  << " directement (" << targetPlayer.getHealth() << " PV)" << std::endl;
    }
    
    std::cout << "0. Retour" << std::endl;
    
    int targetChoice;
    std::cout << "Votre choix: ";
    std::cin >> targetChoice;
    
    if (targetChoice == 0) return;
    
    // Attaquer un Champion
    if (targetChoice > 0 && targetChoice <= static_cast<int>(champions.size())) {
        ChampionCard& targetChampion = champions[targetChoice - 1];
        
        if (targetChampion.isStunned()) {
            std::cout << "Ce Champion est déjà assommé!" << std::endl;
            return;
        }
        
        // Si des Gardes existent, on ne peut cibler que des Gardes
        if (hasGuard && !targetChampion.isGuard()) {
            std::cout << "❌ Vous ne pouvez pas cibler " << targetChampion.getName() 
                      << " ! Des Champions Gardes protègent les autres champions." << std::endl;
            std::cout << "Vous devez d'abord assommer tous les Gardes!" << std::endl;
            return;
        }
        
        int combatUsed;
        std::cout << "\nAttaque sur " << targetChampion.getName() 
                  << " (Def: " << targetChampion.getRemainingDefense() << ")" << std::endl;
        std::cout << "Combien de Combat utiliser? (Max: " 
                  << m_currentTurn.getCombatReserve() << "): ";
        std::cin >> combatUsed;
        
        if (combatUsed > 0 && combatUsed <= m_currentTurn.getCombatReserve()) {
            m_currentTurn.spendCombat(combatUsed);
            targetChampion.takeDamage(combatUsed);
            
            if (targetChampion.isStunned()) {
                std::cout << targetChampion.getName() 
                          << " est ASSOMMÉ et va en défausse!" << std::endl;
                targetPlayer.stunChampion(targetChampion);
            } else {
                std::cout << targetChampion.getName() 
                          << " encaisse " << combatUsed << " dégâts" << std::endl;
            }
        } else {
            std::cout << "Quantité de Combat invalide!" << std::endl;
        }
    }
}

void Game::viewDiscardPile() {
    Player& activePlayer = getCurrentPlayer();
    DiscardPile& discard = activePlayer.getDiscardPile();
    
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          📚 PILE DE DÉFAUSSE                  ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    std::cout << "Joueur: " << activePlayer.getName() << std::endl;
    std::cout << "Nombre de cartes: " << discard.size() << std::endl;
    std::cout << "───────────────────────────────────────────────" << std::endl;
    
    if (discard.isEmpty()) {
        std::cout << "La défausse est vide." << std::endl;
    } else {
        std::cout << "\nCartes dans la défausse:" << std::endl;
        std::vector<Card*> cards = discard.getCards();
        for (size_t i = 0; i < cards.size(); ++i) {
            Card* card = cards[i];
            if (card) {
                std::cout << "  [" << (i + 1) << "] " << card->getName();
                
                // Afficher la faction si elle existe
                if (card->getFaction() != Faction::None) {
                    std::cout << " (" << factionToString(card->getFaction()) << ")";
                }
                
                // Afficher le type de carte
                std::cout << " - " << card->getType();
                std::cout << std::endl;
            }
        }
    }
    
    std::cout << "───────────────────────────────────────────────" << std::endl;
    std::cout << "Appuyez sur [Entrée] pour revenir au menu..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void Game::viewSacrificeZone() {
    Player& activePlayer = getCurrentPlayer();
    activePlayer.viewSacrificeZone();
    
    std::cout << "\nAppuyez sur [Entrée] pour revenir au menu..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void Game::viewOpponentDiscardPile() {
    // Afficher la liste des adversaires
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║    CONSULTER LA DÉFAUSSE D'UN ADVERSAIRE      ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    
    std::vector<int> opponentIndices;
    int displayIndex = 1;
    
    // modifier avec affichage raph
    for (size_t i = 0; i < m_players.size(); ++i) {
        if (static_cast<int>(i) != m_currentPlayerIndex) {
            Player& opponent = m_players[i];
            std::cout << "[" << displayIndex << "] " << opponent.getName()
                      << " - Défausse: " << opponent.getDiscardPile().size() << " cartes";
            if (opponent.isEliminated()) {
                std::cout << " (ÉLIMINÉ)";
            }
            std::cout << std::endl;
            opponentIndices.push_back(i);
            displayIndex++;
        }
    }
    
    std::cout << "[0] Retour" << std::endl;
    
    int choice;
    std::cout << "\nChoisissez un adversaire: ";
    std::cin >> choice;
    
    if (choice == 0) return;
    
    if (choice > 0 && choice <= static_cast<int>(opponentIndices.size())) {
        Player& selectedOpponent = m_players[opponentIndices[choice - 1]];
        DiscardPile& discard = selectedOpponent.getDiscardPile();
        
        std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
        std::cout << "║          📚 PILE DE DÉFAUSSE                  ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
        std::cout << "Joueur: " << selectedOpponent.getName() << std::endl;
        std::cout << "Nombre de cartes: " << discard.size() << std::endl;
        std::cout << "───────────────────────────────────────────────" << std::endl;
        
        if (discard.isEmpty()) {
            std::cout << "La défausse est vide." << std::endl;
        } else {
            std::cout << "\nCartes dans la défausse:" << std::endl;
            std::vector<Card*> cards = discard.getCards();
            for (size_t i = 0; i < cards.size(); ++i) {
                Card* card = cards[i];
                if (card) {
                    std::cout << "  [" << (i + 1) << "] " << card->getName();
                    
                    // Afficher la faction si elle existe
                    if (card->getFaction() != Faction::None) {
                        std::cout << " (" << factionToString(card->getFaction()) << ")";
                    }
                    
                    // Afficher le type de carte
                    std::cout << " - " << card->getType();
                    std::cout << std::endl;
                }
            }
        }
        
        std::cout << "───────────────────────────────────────────────" << std::endl;
        std::cout << "Appuyez sur [Entrée] pour revenir au menu..." << std::endl;
        std::cin.ignore();
        std::cin.get();
    } else {
        std::cout << "Choix invalide!" << std::endl;
    }
}

void Game::acquireCardsPhase() {
    if (m_currentTurn.getGoldReserve() <= 0) {
        std::cout << "Vous n'avez pas d'Or à dépenser!" << std::endl;
        return;
    }
    
    std::cout << "\n--- ACHAT DE CARTES ---" << std::endl;
    std::cout << "Or disponible: " << m_currentTurn.getGoldReserve() << std::endl;
    m_market.displayMarket();
    
    std::cout << "0. Retour" << std::endl;
    
    int choice = readChoice("Choisissez une carte à acheter: ");
    
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
        activePlayer.acquireCard(card, m_currentTurn);
        m_market.removeCardFromMarket(card);
        m_market.refillMarket(); // Remplir l'emplacement vide du marché
        std::cout << activePlayer.getName() << " acquiert: " << card->getName() << std::endl;
    } else {
        std::cout << "Or insuffisant! Coût: " << cost << " Vous avez: "
                  << m_currentTurn.getGoldReserve() << "Or" << std::endl;
    }
}


void Game::discardPhase() {
    Player& activePlayer = getCurrentPlayer();
    
    std::cout << "\n" << activePlayer.getName() << " - Phase de Défausse:" << std::endl;
    
    // 1. Perdre tout l'Or et Combat restants
    if (m_currentTurn.getGoldReserve() > 0 || m_currentTurn.getCombatReserve() > 0) {
        std::cout << "  • Perte de " << m_currentTurn.getGoldReserve() << " Or et " 
                  << m_currentTurn.getCombatReserve() << " Combat" << std::endl;
        m_currentTurn.clearReserves();
    }
    
    // 2. Défausser tous les Objets et Actions en jeu (pas les Champions)
    InPlayArea& playArea = activePlayer.getPlayArea();
    std::vector<Card*>& cards = playArea.getCards();
    
    if (!cards.empty()) {
        std::cout << "  • Défausse de " << cards.size() << " carte(s) en jeu" << std::endl;
        for (Card* card : cards) {
            if (card) {
                activePlayer.discardCard(card);
            }
        }
        playArea.clear(); // Vider la zone de jeu (sauf Champions)
    }
    
    // 3. Défausser toute la main
    if (!activePlayer.getHand().isEmpty()) {
        size_t handSize = activePlayer.getHand().size();
        std::cout << "  • Défausse de la main (" << handSize << " carte(s))" << std::endl;
        activePlayer.discardHand();
    }
    
    // 4. Mobiliser tous les Champions
    std::vector<ChampionCard>& champions = playArea.getChampions();
    if (!champions.empty()) {
        std::cout << "  • Mobilisation de " << champions.size() << " Champion(s)" << std::endl;
        activePlayer.mobilizeChampions();
    }
    
    // 5. Réinitialiser les dégâts des Champions
    std::cout << "  • Réinitialisation des dégâts des Champions" << std::endl;
    activePlayer.resetChampionDamage();
    
    std::cout << "Phase de défausse terminée" << std::endl;
}

void Game::drawPhase() {
    Player& activePlayer = getCurrentPlayer();
    
    std::cout << "\n" << activePlayer.getName() << " - Phase de Pioche:" << std::endl;
    
    // Piocher 5 cartes
    std::cout << "  • Pioche de 5 cartes" << std::endl;
    activePlayer.drawCards(5);
    
    // Afficher le nombre de cartes en main
    std::cout << "Main actuelle: " << activePlayer.getHand().size() << " carte(s)" << std::endl;
    
    // Fin du tour
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  FIN DU TOUR DE " << activePlayer.getName();
    // Padding pour aligner
    for (size_t i = activePlayer.getName().length(); i < 26; ++i) {
        std::cout << " ";
    }
    std::cout << "║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
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
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           ÉTAT DE LA PARTIE                   ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    for (const auto& player : m_players) {
        player.displayStatus();
    }
}

// Activation des capacités de Champions
void Game::activateAbilitiesPhase() {
    Player& activePlayer = getCurrentPlayer();
    std::vector<ChampionCard>& champions = activePlayer.getPlayArea().getChampions();
    
    if (champions.empty()) {
        std::cout << "Vous n'avez aucun Champion en jeu!" << std::endl;
        return;
    }
    
    std::cout << "\n--- ACTIVER UN CHAMPION ---" << std::endl;
    bool hasReadyChampion = false;
    
    // Afficher tous les champions avec leur état
    for (size_t i = 0; i < champions.size(); ++i) {
        ChampionCard& champion = champions[i];
        std::cout << "[" << (i + 1) << "] " << champion.getName() 
                  << " (Def: " << champion.getRemainingDefense() << "/" << champion.getDefense() << ")";
        
        if (champion.isStunned()) {
            std::cout << " [ASSOMMÉ]";
        } else if (!champion.getIsTapped()) {
            std::cout << " [MOBILISÉ]";
            hasReadyChampion = true;
        } else {
            std::cout << " [DÉMOBILISÉ]";
        }
        
        if (champion.isGuard()) {
            std::cout << " [GARDE]";
        }
        std::cout << std::endl;
    }
    
    if (!hasReadyChampion) {
        std::cout << "Tous vos Champions sont démobilisés ou assommés!" << std::endl;
        return;
    }
    
    std::cout << "0. Retour" << std::endl;
    
    int choice = readChoice("Choisissez un Champion à activer: ");
    
    if (choice > 0 && choice <= static_cast<int>(champions.size())) {
        ChampionCard& champion = champions[choice - 1];
        if (champion.isReady() && !champion.isStunned()) {
            champion.activateAbility(activePlayer, m_currentTurn);
        } else {
            std::cout << "Ce Champion ne peut pas être activé!" << std::endl;
        }
    }
}

// Déclenche automatiquement les capacités Alliées d'une faction
void Game::triggerAllyAbilities(Faction faction) {
    Player& activePlayer = getCurrentPlayer();
    InPlayArea& playArea = activePlayer.getPlayArea();
    
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  🤝 DÉCLENCHEMENT CAPACITÉS ALLIÉES           ║" << std::endl;
    std::cout << "║     " << factionToString(faction) << std::string(40 - factionToString(faction).length(), ' ') << "║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    
    bool foundAlly = false;
    
    // Vérifier les cartes en jeu (Actions/Items)
    std::vector<Card*>& cardsInPlay = playArea.getCards();
    for (Card* card : cardsInPlay) {
        if (card && card->hasAllyAbility() && card->getFaction() == faction) {
            foundAlly = true;
            std::cout << "→ " << card->getName() << " déclenche sa capacité Alliée!" << std::endl;
            
            // Cast vers ActionCard ou ItemCard pour activer l'AllyAbility
            if (auto* actionCard = dynamic_cast<ActionCard*>(card)) {
                // Trouver et déclencher l'AllyAbility
                for (auto& ability : actionCard->getAbilities()) {
                    if (ability->getName() == "AllyAbility") {
                        ability->trigger(activePlayer, m_currentTurn);
                    }
                }
            } else if (auto* itemCard = dynamic_cast<ItemCard*>(card)) {
                // Trouver et déclencher l'AllyAbility
                for (auto& ability : itemCard->getAbilities()) {
                    if (ability->getName() == "AllyAbility") {
                        ability->trigger(activePlayer, m_currentTurn);
                    }
                }
            }
        }
    }
    
    // Vérifier les Champions
    std::vector<ChampionCard>& champions = playArea.getChampions();
    for (auto& champion : champions) {
        if (champion.hasAllyAbility() && champion.getFaction() == faction) {
            foundAlly = true;
            std::cout << "→ " << champion.getName() << " déclenche sa capacité Alliée!" << std::endl;
            champion.triggerAllyAbility(activePlayer, m_currentTurn);
        }
    }
    
    if (!foundAlly) {
        std::cout << "Aucune capacité Alliée " << factionToString(faction) << " à déclencher" << std::endl;
    }
    std::cout << "═══════════════════════════════════════════════" << std::endl;
}

// Vérifier et proposer l'activation manuelle des capacités Alliées
void Game::checkAndTriggerAllyAbilities() {
    Player& activePlayer = getCurrentPlayer();
    InPlayArea& playArea = activePlayer.getPlayArea();
    
    std::cout << "\n--- VÉRIFICATION CAPACITÉS ALLIÉES ---" << std::endl;
    
    // Parcourir toutes les factions jouées
    for (int f = static_cast<int>(Faction::Imperial); f <= static_cast<int>(Faction::Sauvage); ++f) {
        Faction faction = static_cast<Faction>(f);
        
        if (m_currentTurn.hasFactionBeenPlayed(faction)) {
            std::cout << "Faction " << factionToString(faction) << " jouée ce tour" << std::endl;
            
            // Compter les cartes de cette faction avec Ally ability
            int allyCount = 0;
            for (Card* card : playArea.getCards()) {
                if (card && card->hasAllyAbility() && card->getFaction() == faction) {
                    allyCount++;
                }
            }
            for (auto& champion : playArea.getChampions()) {
                if (champion.hasAllyAbility() && champion.getFaction() == faction) {
                    allyCount++;
                }
            }
            
            if (allyCount > 0) {
                std::cout << "  → " << allyCount << " capacité(s) Alliée(s) disponible(s)" << std::endl;
            }
        }
    }
}

// Utiliser une capacité Allié (activation manuelle)
void Game::useAllyAbility(const std::string& cardName) {
    (void)cardName;  // Pour éviter le warning
    
    std::cout << "\n--- ACTIVATION MANUELLE CAPACITÉS ALLIÉES ---" << std::endl;
    std::cout << "⚠️  Note: Les capacités Alliées se déclenchent automatiquement" << std::endl;
    std::cout << "   quand vous jouez une 2ème carte de la même faction." << std::endl;
    
    // Afficher les factions déjà jouées
    std::cout << "\nFactions jouées ce tour:" << std::endl;
    bool foundFaction = false;
    for (int f = static_cast<int>(Faction::Imperial); f <= static_cast<int>(Faction::Sauvage); ++f) {
        Faction faction = static_cast<Faction>(f);
        if (m_currentTurn.hasFactionBeenPlayed(faction)) {
            std::cout << "  ✓ " << factionToString(faction) << std::endl;
            foundFaction = true;
        }
    }
    
    if (!foundFaction) {
        std::cout << "  (Aucune faction jouée)" << std::endl;
    }
    
    std::cout << "\nAppuyez sur [Entrée] pour continuer..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

// Sacrifier une carte
void Game::sacrificeCard(const std::string& cardName) {
    (void)cardName;  // Pour éviter le warning
    Player& activePlayer = getCurrentPlayer();
    
    std::cout << "\n--- SACRIFIER UNE CARTE ---" << std::endl;
    
    // Lister toutes les cartes sacrifiables
    std::vector<Card*>& cardsInPlay = activePlayer.getPlayArea().getCards();
    std::vector<ChampionCard>& champions = activePlayer.getPlayArea().getChampions();
    
    if (cardsInPlay.empty() && champions.empty()) {
        std::cout << "Vous n'avez aucune carte en jeu à sacrifier!" << std::endl;
        return;
    }
    
    std::cout << "Cartes sacrifiables:" << std::endl;
    
    int index = 1;
    for (Card* card : cardsInPlay) {
        std::cout << index++ << ". " << card->getName();
        if (card->hasSacrificeAbility()) {
            std::cout << " 💀";
        }
        std::cout << std::endl;
    }
    
    for (auto& champion : champions) {
        std::cout << index++ << ". " << champion.getName() << " (Champion)";
        if (champion.hasSacrificeAbility()) {
            std::cout << " 💀";
        }
        std::cout << std::endl;
    }
    
    std::cout << "0. Retour" << std::endl;
    
    int choice = readChoice("Choisissez une carte à sacrifier: ");
    
    if (choice > 0) {
        if (choice <= static_cast<int>(cardsInPlay.size())) {
            // Sacrifier une Action/Item
            Card* card = cardsInPlay[choice - 1];
            std::cout << "Sacrifice de " << card->getName() << std::endl;
            
            // Déclencher la capacité Sacrifier si elle existe
            if (card->hasSacrificeAbility()) {
                std::cout << "→ Activation de la capacité Sacrifier" << std::endl;
                
                // Cast vers ActionCard ou ItemCard pour déclencher la SacrificeAbility
                if (auto* actionCard = dynamic_cast<ActionCard*>(card)) {
                    for (auto& ability : actionCard->getAbilities()) {
                        if (ability->getName() == "SacrificeAbility") {
                            ability->trigger(activePlayer, m_currentTurn);
                        }
                    }
                } else if (auto* itemCard = dynamic_cast<ItemCard*>(card)) {
                    for (auto& ability : itemCard->getAbilities()) {
                        if (ability->getName() == "SacrificeAbility") {
                            ability->trigger(activePlayer, m_currentTurn);
                        }
                    }
                }
            }
            
            // Vérifier si c'est une Gemme de Feu
            if (card->getName() == "Gemme de Feu") {
                std::cout << "→ Gemme de Feu retourne dans la pile Gemmes de Feu" << std::endl;
                // Ajouter la carte à la pile de Gemmes de Feu du marché
                ItemCard* fireGem = dynamic_cast<ItemCard*>(card);
                if (fireGem) {
                    m_market.getFireGems().push_back(fireGem);
                }
            } else {
                // Placer dans la Zone de Sacrifice
                activePlayer.addToSacrificeZone(card);
            }
            
            // Retirer de la zone de jeu
            cardsInPlay.erase(cardsInPlay.begin() + (choice - 1));
            
        } else if (choice <= static_cast<int>(cardsInPlay.size() + champions.size())) {
            // Sacrifier un Champion
            int championIndex = choice - cardsInPlay.size() - 1;
            ChampionCard& champion = champions[championIndex];
            
            std::cout << "Sacrifice de " << champion.getName() << std::endl;
            
            // Déclencher la capacité Sacrifier si elle existe
            if (champion.hasSacrificeAbility()) {
                std::cout << "→ Activation de la capacité Sacrifier" << std::endl;
                champion.triggerSacrificeAbility(activePlayer, m_currentTurn);
            }
            
            // Vérifier si c'est une Gemme de Feu (peu probable pour un Champion)
            if (champion.getName() == "Gemme de Feu") {
                std::cout << "→ Gemme de Feu retourne dans la pile Gemmes de Feu" << std::endl;
                // Normalement, une Gemme de Feu n'est pas un Champion, mais par sécurité
            } else {
                // Placer dans la Zone de Sacrifice (déjà géré dans sacrificeChampion)
                activePlayer.sacrificeChampion(champion);
            }
        }
    }
}

// Validation des attaques
bool Game::canAttackPlayer(const Player& target) const {
    // On ne peut pas attaquer si le joueur a des Gardes mobilisés
    return !target.hasGuardInPlay();
}

bool Game::canTargetChampion(const Player& target, const ChampionCard& champion) const {
    (void)target;  // Pour éviter le warning
    // On peut toujours cibler un Champion (même avec des Gardes)
    // Mais les Gardes doivent être ciblés en priorité
    return !champion.isStunned();
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