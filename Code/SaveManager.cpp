#include "SaveManager.h"
#include "Game.h"
#include "Player.h"
#include "Turn.h"
#include "CardFactory.h"
#include "CardsType/Card.h"
#include "CardsType/ChampionCard.h"
#include "Cards/Deck.h"
#include "Cards/Hand.h"
#include "Cards/DiscardPile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>

#ifdef _WIN32
#include <direct.h> // pour _mkdir
#endif

SaveManager::SaveManager() : m_saveDirectory(getDefaultSaveDirectory()) {
    // Créer le répertoire de sauvegarde s'il n'existe pas
    #ifdef _WIN32
        _mkdir(m_saveDirectory.c_str());
    #else
        mkdir(m_saveDirectory.c_str(), 0755);
    #endif
}

SaveManager::SaveManager(const std::string& saveDirectory) : m_saveDirectory(saveDirectory) {
    #ifdef _WIN32
        _mkdir(m_saveDirectory.c_str());
    #else
        mkdir(m_saveDirectory.c_str(), 0755);
    #endif
}

std::string SaveManager::getDefaultSaveDirectory() {
    return "saves";
}

std::string SaveManager::getSaveFilePath(int slotNumber) const {
    return m_saveDirectory + "/save_slot_" + std::to_string(slotNumber) + ".sav";
}

std::string SaveManager::getCurrentDateTime() const {
    time_t now = time(0);
    struct tm timeinfo;
    // Utiliser la version sûre adaptée à la plateforme
    #if defined(_WIN32) && defined(_MSC_VER)
        localtime_s(&timeinfo, &now);
    #elif defined(_WIN32)
        #ifdef HAVE_LOCALTIME_S
            localtime_s(&timeinfo, &now);
        #else
        
            struct tm* tmp = std::localtime(&now);
            if (tmp) timeinfo = *tmp;
        #endif
    #elif defined(__unix__) || defined(__APPLE__)
        
        localtime_r(&now, &timeinfo);
    #else
        
        struct tm* tmp = std::localtime(&now);
        if (tmp) timeinfo = *tmp;
    #endif
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", &timeinfo);
    return std::string(buffer);
}

bool SaveManager::saveGame(const Game& game, int slotNumber) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        std::cerr << "Numéro de slot invalide: " << slotNumber << std::endl;
        return false;
    }
    
    std::string filePath = getSaveFilePath(slotNumber);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde: " << filePath << std::endl;
        return false;
    }
    
    try {
        // Header
        file << "HERO_REALMS_SAVE_V1\n";
        file << getCurrentDateTime() << "\n";
        
        // Game state
        const std::vector<Player>& players = const_cast<Game&>(game).getPlayers();
        file << players.size() << "\n";
        
        // Index du joueur actuel
        int currentPlayerIndex = 0;
        for (size_t i = 0; i < players.size(); ++i) {
            if (&players[i] == &const_cast<Game&>(game).getCurrentPlayer()) {
                currentPlayerIndex = i;
                break;
            }
        }
        file << currentPlayerIndex << "\n";
        
        // Turn state
        Turn& turn = const_cast<Game&>(game).getCurrentTurn();
        file << turn.getGoldReserve() << "\n";
        file << turn.getCombatReserve() << "\n";
        
        // Sauvegarder chaque joueur
        for (const Player& player : players) {
            // Informations de base
            file << player.getName() << "\n";
            file << player.getHealth() << "\n";
            file << const_cast<Player&>(player).getGold() << "\n";
            file << player.isEliminated() << "\n";
            
            // Main
            Hand& hand = const_cast<Player&>(player).getHand();
            file << hand.size() << "\n";
            for (size_t i = 0; i < hand.size(); ++i) {
                Card* card = hand.getCardAt(i);
                if (card) {
                    file << card->getName() << "\n";
                }
            }
            
            // Deck
            Deck& deck = const_cast<Player&>(player).getDeck();
            std::vector<Card*> deckCards = deck.getCards();
            file << deckCards.size() << "\n";
            for (Card* card : deckCards) {
                if (card) {
                    file << card->getName() << "\n";
                }
            }
            
            // Discard pile
            DiscardPile& discard = const_cast<Player&>(player).getDiscardPile();
            std::vector<Card*> discardCards = discard.getCards();
            file << discardCards.size() << "\n";
            for (Card* card : discardCards) {
                if (card) {
                    file << card->getName() << "\n";
                }
            }
            
            // Play area (Champions)
            InPlayArea& playArea = const_cast<Player&>(player).getPlayArea();
            std::vector<ChampionCard>& champions = playArea.getChampions();
            file << champions.size() << "\n";
            for (ChampionCard& champion : champions) {
                file << champion.getName() << "\n";
                file << champion.getCurrentDamage() << "\n";
                file << champion.getIsTapped() << "\n";
            }
            
            // Cards in play (non-champions)
            std::vector<Card*>& cardsInPlay = playArea.getCards();
            file << cardsInPlay.size() << "\n";
            for (Card* card : cardsInPlay) {
                if (card) {
                    file << card->getName() << "\n";
                }
            }
            
            // Sacrifice zone
            std::vector<Card*>& sacrificeZone = const_cast<Player&>(player).getSacrificeZone();
            file << sacrificeZone.size() << "\n";
            for (Card* card : sacrificeZone) {
                if (card) {
                    file << card->getName() << "\n";
                }
            }
        }
        
        file.close();
        std::cout << "✓ Partie sauvegardée dans le slot " << slotNumber << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

bool SaveManager::loadGame(Game& game, int slotNumber) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        std::cerr << "Numéro de slot invalide: " << slotNumber << std::endl;
        return false;
    }
    
    std::string filePath = getSaveFilePath(slotNumber);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde: " << filePath << std::endl;
        return false;
    }
    
    try {
        std::string line;
        
        // Vérifier le header
        std::getline(file, line);
        if (line != "HERO_REALMS_SAVE_V1") {
            std::cerr << "Format de sauvegarde invalide" << std::endl;
            file.close();
            return false;
        }
        
        // Date (ignorée pour le chargement)
        std::getline(file, line);
        std::cout << "📅 Partie sauvegardée le: " << line << std::endl;
        
        // Nombre de joueurs
        int playerCount;
        file >> playerCount;
        file.ignore();
        
        // Index du joueur actuel
        int currentPlayerIndex;
        file >> currentPlayerIndex;
        file.ignore();
        
        // Turn state
        int goldReserve, combatReserve;
        file >> goldReserve >> combatReserve;
        file.ignore();
        
    std::cout << "⏳ Chargement de " << playerCount << " joueur(s)..." << std::endl;
    // Collecter les Fire Gems trouvées dans les zones de sacrifice pour les restaurer
    // dans le marché après l'initialisation de celui-ci.
    std::vector<Card*> savedFireGems;
        
        // Charger chaque joueur
        for (int p = 0; p < playerCount; ++p) {
            // Informations de base du joueur
            std::string playerName;
            std::getline(file, playerName);
            
            int health, gold, eliminated;
            file >> health >> gold >> eliminated;
            file.ignore();
            
            std::cout << "  • Chargement de " << playerName << " (" << health << " PV)" << std::endl;
            
            // Créer les structures vides
            Deck deck;
            Hand hand;
            DiscardPile discard;
            
            // Charger la main
            int handSize;
            file >> handSize;
            file.ignore();
            for (int i = 0; i < handSize; ++i) {
                std::string cardName;
                std::getline(file, cardName);
                Card* card = CardFactory::createCard(cardName);
                if (card) {
                    hand.add(card);
                }
            }
            
            // Charger le deck
            int deckSize;
            file >> deckSize;
            file.ignore();
            for (int i = 0; i < deckSize; ++i) {
                std::string cardName;
                std::getline(file, cardName);
                Card* card = CardFactory::createCard(cardName);
                if (card) {
                    deck.addCard(card);
                }
            }
            
            // Charger la défausse
            int discardSize;
            file >> discardSize;
            file.ignore();
            for (int i = 0; i < discardSize; ++i) {
                std::string cardName;
                std::getline(file, cardName);
                Card* card = CardFactory::createCard(cardName);
                if (card) {
                    discard.add(card);
                }
            }
            
            // Créer le joueur
            Player player(playerName, health, deck, hand, discard);
            player.setGold(gold);
            if (eliminated) {
                // Note: Pas de méthode setEliminated, mais le joueur sera éliminé si health <= 0
            }
            
            // Charger les Champions en jeu
            int championsSize;
            file >> championsSize;
            file.ignore();
            for (int i = 0; i < championsSize; ++i) {
                std::string championName;
                std::getline(file, championName);
                int currentDamage, isTapped;
                file >> currentDamage >> isTapped;
                file.ignore();
                
                // Recréer le Champion et le placer dans la défausse
                Card* card = CardFactory::createCard(championName);
                if (card) {
                    discard.add(card);
                    std::cout << "    ⚠️ Champion remis en défausse: " << championName << std::endl;
                }
            }
            
            // Charger les cartes en jeu (non-champions)
            int cardsInPlaySize;
            file >> cardsInPlaySize;
            file.ignore();
            for (int i = 0; i < cardsInPlaySize; ++i) {
                std::string cardName;
                std::getline(file, cardName);
                // Recréer la carte et la placer dans la défausse
                Card* card = CardFactory::createCard(cardName);
                if (card) {
                    discard.add(card);
                    std::cout << "    ⚠️ Carte en jeu remise en défausse: " << cardName << std::endl;
                }
            }
            
            // Charger la zone de sacrifice
            int sacrificeSize;
            file >> sacrificeSize;
            file.ignore();
            for (int i = 0; i < sacrificeSize; ++i) {
                std::string cardName;
                std::getline(file, cardName);
                Card* card = CardFactory::createCard(cardName);
                if (card) {
                    // Si c'est une Fire Gem, on la mettra dans la pile FireGems du marché
                    // après l'initialisation du marché pour respecter la règle.
                    if (card->getName() == "Fire Gem") {
                        savedFireGems.push_back(card);
                    } else {
                        player.addToSacrificeZone(card);
                    }
                }
            }
            
            // Ajouter le joueur au jeu avec std::move pour éviter la copie
            game.addPlayer(std::move(player));
        }
        
        file.close();
        
        // Initialiser le marché
        std::cout << "\n🎮 Initialisation du marché..." << std::endl;
        game.getMarket().initializeBaseSet();

        // Restaurer les Fire Gems sauvegardées en les plaçant dans la pile FireGems du marché
        for (Card* c : savedFireGems) {
            ItemCard* ic = dynamic_cast<ItemCard*>(c);
            if (ic) {
                game.getMarket().getFireGems().push_back(ic);
            } else {
                // si le cast échoue, éviter fuite mémoire en plaçant dans la défausse générale
                game.getPlayers().front().getDiscardPile().add(c);
            }
        }
        
        // Restaurer l'état du tour
        game.getCurrentTurn().setGoldReserve(goldReserve);
        game.getCurrentTurn().setCombatReserve(combatReserve);
        
        // Marquer le jeu comme démarré
        game.markAsStarted();
        
        std::cout << "\n✓ Partie chargée avec succès!" << std::endl;
        std::cout << "⚠️  Note: Les Champions et cartes en jeu ont été remis en défausse" << std::endl;
        std::cout << "   pour simplifier le chargement." << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erreur lors du chargement: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

std::vector<SaveSlot> SaveManager::getSaveSlots() const {
    std::vector<SaveSlot> slots;
    
    for (int i = 1; i <= MAX_SAVE_SLOTS; ++i) {
        slots.push_back(getSaveSlotInfo(i));
    }
    
    return slots;
}

SaveSlot SaveManager::getSaveSlotInfo(int slotNumber) const {
    SaveSlot slot;
    slot.slotNumber = slotNumber;
    slot.isEmpty = true;
    
    std::string filePath = getSaveFilePath(slotNumber);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return slot;
    }
    
    try {
        std::string line;
        
        // Header
        std::getline(file, line);
        if (line != "HERO_REALMS_SAVE_V1") {
            return slot;
        }
        
        // Date
        std::getline(file, slot.saveDate);
        
        // Nombre de joueurs
        int playerCount;
        file >> playerCount;
        file.ignore();
        
        // Index joueur actuel
        int currentPlayerIndex;
        file >> currentPlayerIndex;
        file.ignore();
        
        // Gold et combat
        int gold, combat;
        file >> gold >> combat;
        file.ignore();
        
        // Lire les infos des joueurs
        if (playerCount >= 2) {
            // Joueur 1
            std::getline(file, slot.player1Name);
            file >> slot.player1Health;
            file.ignore();
            
            // Passer les autres données du joueur 1
            int gold1, eliminated1;
            file >> gold1 >> eliminated1;
            file.ignore();
            
            // Passer la main, deck, discard, etc. du joueur 1
            int handSize, deckSize, discardSize, championsSize, cardsInPlaySize, sacrificeSize;
            file >> handSize;
            file.ignore();
            for (int i = 0; i < handSize; ++i) {
                std::getline(file, line);
            }
            
            file >> deckSize;
            file.ignore();
            for (int i = 0; i < deckSize; ++i) {
                std::getline(file, line);
            }
            
            file >> discardSize;
            file.ignore();
            for (int i = 0; i < discardSize; ++i) {
                std::getline(file, line);
            }
            
            file >> championsSize;
            file.ignore();
            for (int i = 0; i < championsSize; ++i) {
                std::getline(file, line); // name
                int def, tapped;
                file >> def >> tapped;
                file.ignore();
            }
            
            file >> cardsInPlaySize;
            file.ignore();
            for (int i = 0; i < cardsInPlaySize; ++i) {
                std::getline(file, line);
            }
            
            file >> sacrificeSize;
            file.ignore();
            for (int i = 0; i < sacrificeSize; ++i) {
                std::getline(file, line);
            }
            
            // Joueur 2
            std::getline(file, slot.player2Name);
            file >> slot.player2Health;
            file.ignore();
            
            slot.currentPlayerName = (currentPlayerIndex == 0) ? slot.player1Name : slot.player2Name;
            slot.isEmpty = false;
        }
        
        file.close();
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la lecture du slot " << slotNumber << ": " << e.what() << std::endl;
    }
    
    return slot;
}

bool SaveManager::isSlotEmpty(int slotNumber) const {
    return getSaveSlotInfo(slotNumber).isEmpty;
}

bool SaveManager::deleteSave(int slotNumber) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        return false;
    }
    
    std::string filePath = getSaveFilePath(slotNumber);
    
    if (remove(filePath.c_str()) == 0) {
        std::cout << "✓ Sauvegarde " << slotNumber << " supprimée" << std::endl;
        return true;
    }
    
    return false;
}

void SaveManager::displaySaveSlots() const {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              SAUVEGARDES DISPONIBLES                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
    
    std::vector<SaveSlot> slots = getSaveSlots();
    
    for (const SaveSlot& slot : slots) {
        std::cout << "\n[Slot " << slot.slotNumber << "] ";
        
        if (slot.isEmpty) {
            std::cout << "─ VIDE ─" << std::endl;
        } else {
            std::cout << "───────────────────────────────────────" << std::endl;
            std::cout << "  Date: " << slot.saveDate << std::endl;
            std::cout << "  " << slot.player1Name << " (" << slot.player1Health << " PV) vs " 
                      << slot.player2Name << " (" << slot.player2Health << " PV)" << std::endl;
            std::cout << "  Tour actuel: " << slot.currentPlayerName << std::endl;
        }
    }
    
    std::cout << "\n════════════════════════════════════════════════════════════" << std::endl;
}
