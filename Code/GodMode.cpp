#include "GodMode.h"
#include "CardsType/Card.h"
#include "Cards/Deck.h"
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
                std::cout << "Entrée invalide ! Veuillez entrer un nombre." << std::endl;
                continue;
            }
            
            // Ignorer le reste de la ligne
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

GodMode::GodMode() : m_isActive(false) {}

void GodMode::activate() {
    m_isActive = true;
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            GOD MODE ACTIVÉ                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Le God Mode est maintenant actif !" << std::endl;
    std::cout << "• Mettre tous les joueurs à 1 PV" << std::endl;
    std::cout << "• Acheter depuis toute la pioche du marché" << std::endl;
    std::cout << "• Les cartes achetées vont directement en main" << std::endl;
}

void GodMode::deactivate() {
    m_isActive = false;
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            GOD MODE DÉSACTIVÉ                            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Le God Mode est désactivé. Retour aux règles normales." << std::endl;
}

void GodMode::toggle() {
    if (m_isActive) {
        deactivate();
    } else {
        activate();
    }
}

bool GodMode::isActive() const {
    return m_isActive;
}

void GodMode::setAllPlayersToOneHP(std::vector<Player>& players) {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║       MISE À 1 PV DE TOUS LES JOUEURS                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    
    for (auto& player : players) {
        if (!player.isEliminated()) {
            int oldHealth = player.getHealth();
            player.setHealth(1);
            std::cout << "• " << player.getName() << ": " << oldHealth << " PV → 1 PV" << std::endl;
        }
    }
    
    std::cout << "\nTous les joueurs ont été mis à 1 PV !" << std::endl;
}

void GodMode::buyFromFullDeck(Player& player, Market& market, Turn& turn) {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          ACHAT DEPUIS LA PIOCHE COMPLÈTE                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    
    Deck& marketDeck = market.getMarketDeck();
    std::vector<Card*> allCards = marketDeck.getCards();
    
    if (allCards.empty()) {
        std::cout << "La pioche du marché est vide !" << std::endl;
        return;
    }
    
    std::cout << "Or disponible: " << turn.getGoldReserve() << std::endl;
    std::cout << "\n═══════════════ PIOCHE COMPLÈTE DU MARCHÉ ═════════════════" << std::endl;
    std::cout << "Total de cartes: " << allCards.size() << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════" << std::endl;
    
    // Afficher toutes les cartes de la pioche avec indices
    for (size_t i = 0; i < allCards.size(); ++i) {
        Card* card = allCards[i];
        std::cout << "[" << (i + 1) << "] " << card->getName() 
                  << " - Coût: " << card->getCost() << " Or";
        
        if (card->getFaction() != Faction::None) {
            std::cout << " (" << factionToString(card->getFaction()) << ")";
        }
        
        std::cout << " - " << card->getType();
        std::cout << std::endl;
        
        // Afficher les cartes par groupes de 10 pour faciliter la lecture
        if ((i + 1) % 10 == 0 && i + 1 < allCards.size()) {
            std::cout << "───────────────────────────────────────────────────────────" << std::endl;
        }
    }
    
    std::cout << "═══════════════════════════════════════════════════════════" << std::endl;
    std::cout << "[0] Retour" << std::endl;
    
    int choice = readChoice("\nChoisissez une carte à acheter: ");
    
    if (choice == 0) {
        return;
    }
    
    if (choice < 1 || choice > static_cast<int>(allCards.size())) {
        std::cout << "Choix invalide !" << std::endl;
        return;
    }
    
    Card* selectedCard = allCards[choice - 1];
    int cost = selectedCard->getCost();
    
    // Vérifier si le joueur a assez d'Or
    if (turn.getGoldReserve() < cost) {
        std::cout << "Or insuffisant ! Coût: " << cost 
                  << " Or | Vous avez: " << turn.getGoldReserve() << " Or" << std::endl;
        return;
    }
    
    // Dépenser l'Or
    turn.spendGold(cost);
    
    // Retirer la carte de la pioche du marché
    marketDeck.removeCard(selectedCard);
    
    // Ajouter la carte DIRECTEMENT dans la main du joueur (spécifique God Mode)
    player.getHand().add(selectedCard);
    
    std::cout << "\n✓ " << player.getName() << " achète " << selectedCard->getName() 
              << " depuis la pioche complète !" << std::endl;
    std::cout << "→ La carte va DIRECTEMENT dans votre main (God Mode)" << std::endl;
    std::cout << "Or restant: " << turn.getGoldReserve() << std::endl;
    
    // Remplir le marché si nécessaire (car on a retiré une carte de la pioche)
    market.refillMarket();
}

void GodMode::displayMenu(std::vector<Player>& players, Market& market, Turn& turn) {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                    MENU GOD MODE                          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "État: " << (m_isActive ? "ACTIVÉ" : "DÉSACTIVÉ") << std::endl;
    std::cout << "───────────────────────────────────────────────────────────" << std::endl;
    std::cout << "[1] " << (m_isActive ? "Désactiver" : "Activer") << " le God Mode" << std::endl;
    std::cout << "[2] Mettre tous les joueurs à 1 PV" << std::endl;
    std::cout << "[3] Acheter depuis toute la pioche du marché" << std::endl;
    std::cout << "[0] Retour au jeu" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════" << std::endl;
    
    int choice = readChoice("Votre choix: ");
    
    switch (choice) {
        case 0:
            return;
            
        case 1:
            toggle();
            break;
            
        case 2:
            if (m_isActive) {
                setAllPlayersToOneHP(players);
            } else {
                std::cout << "Le God Mode doit être activé pour utiliser cette fonction !" << std::endl;
            }
            break;
            
        case 3:
            if (m_isActive) {
                // Déterminer le joueur actuel (on pourrait passer ça en paramètre)
                std::cout << "\nPour quel joueur acheter?" << std::endl;
                for (size_t i = 0; i < players.size(); ++i) {
                    std::cout << "[" << (i + 1) << "] " << players[i].getName();
                    if (players[i].isEliminated()) {
                        std::cout << " (ÉLIMINÉ)";
                    }
                    std::cout << std::endl;
                }
                std::cout << "[0] Annuler" << std::endl;
                
                int playerChoice = readChoice("Choisissez un joueur: ");
                if (playerChoice > 0 && playerChoice <= static_cast<int>(players.size())) {
                    Player& selectedPlayer = players[playerChoice - 1];
                    if (!selectedPlayer.isEliminated()) {
                        buyFromFullDeck(selectedPlayer, market, turn);
                    } else {
                        std::cout << "Ce joueur est éliminé !" << std::endl;
                    }
                }
            } else {
                std::cout << "Le God Mode doit être activé pour utiliser cette fonction !" << std::endl;
            }
            break;
            
        default:
            std::cout << "Choix invalide !" << std::endl;
            break;
    }
    
    // Afficher le menu à nouveau si on n'a pas choisi de retourner
    if (choice != 0) {
        std::cout << "\nAppuyez sur [Entrée] pour continuer..." << std::endl;
        std::cin.get();
        displayMenu(players, market, turn);
    }
}
