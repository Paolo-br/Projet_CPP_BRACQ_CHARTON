#include "OptionalSacrificeEffect.h"
#include "../Player.h"
#include "../Turn.h"
#include "../Cards/Hand.h"
#include "../Cards/DiscardPile.h"
#include "../CardsType/Card.h"
#include <iostream>
#include <vector>
#include <limits>

// Constructeur
OptionalSacrificeEffect::OptionalSacrificeEffect(int count, int maxCount, bool isOptional, Effect* bonusEffect)
    : Effect(count), m_count(count), m_maxCount(maxCount), m_isOptional(isOptional), m_bonusEffect(bonusEffect) {}

// Destructeur
OptionalSacrificeEffect::~OptionalSacrificeEffect() {
    if (m_bonusEffect) {
        delete m_bonusEffect;
        m_bonusEffect = nullptr;
    }
}

// Clone
Effect* OptionalSacrificeEffect::clone() const {
    Effect* clonedBonus = m_bonusEffect ? m_bonusEffect->clone() : nullptr;
    return new OptionalSacrificeEffect(m_count, m_maxCount, m_isOptional, clonedBonus);
}


void OptionalSacrificeEffect::apply(Player& player, Turn& turn) {
    std::cout << "\n--- Effet de Sacrifice Optionnel ---" << std::endl;
    
    if (m_isOptional) {
        std::cout << "Voulez-vous sacrifier des cartes? (o/n): ";
        std::string choice;
        std::cin >> choice;
        if (choice != "o" && choice != "O") {
            std::cout << "Sacrifice annulé." << std::endl;
            return;
        }
    }
    
    // Collecter toutes les cartes disponibles (main + défausse)
    std::vector<Card*> availableCards;
    std::vector<std::string> cardSources; // "main" ou "défausse"
    
    // Ajouter les cartes de la main
    Hand& hand = player.getHand();
    for (size_t i = 0; i < hand.size(); ++i) {
        availableCards.push_back(hand.getCardAt(i));
        cardSources.push_back("main");
    }
    
    // Ajouter les cartes de la défausse
    DiscardPile& discard = player.getDiscardPile();
    const std::vector<Card*>& discardCards = discard.getCards();
    for (Card* card : discardCards) {
        availableCards.push_back(card);
        cardSources.push_back("défausse");
    }
    
    if (availableCards.empty()) {
        std::cout << "Aucune carte disponible à sacrifier." << std::endl;
        return;
    }
    
    // Déterminer le nombre de cartes à sacrifier
    int targetCount = m_maxCount;
    if (m_maxCount > 1) {
        std::cout << "Combien de cartes voulez-vous sacrifier? (0-" << m_maxCount << "): ";
        std::cin >> targetCount;
        
        // Validation
        while (std::cin.fail() || targetCount < 0 || targetCount > m_maxCount) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Choix invalide. Entrez un nombre entre 0 et " << m_maxCount << ": ";
            std::cin >> targetCount;
        }
        
        if (targetCount == 0) {
            std::cout << "Aucune carte sacrifiée." << std::endl;
            return;
        }
    }
    
    // Limiter au nombre de cartes disponibles
    int actualCount = std::min(targetCount, static_cast<int>(availableCards.size()));
    
    // Sacrifier les cartes
    int sacrificedCount = 0;
    for (int i = 0; i < actualCount; ++i) {
        std::cout << "\n--- Sacrifice " << (i + 1) << "/" << actualCount << " ---" << std::endl;
        std::cout << "Cartes disponibles:" << std::endl;
        
        // Afficher les cartes disponibles
        for (size_t j = 0; j < availableCards.size(); ++j) {
            std::cout << (j + 1) << ". " << availableCards[j]->getName() 
                      << " [" << cardSources[j] << "]" << std::endl;
        }
        
        // Choisir une carte
        std::cout << "Choisissez une carte à sacrifier (1-" << availableCards.size() << "): ";
        int choice;
        std::cin >> choice;
        
        // Validation
        while (std::cin.fail() || choice < 1 || choice > static_cast<int>(availableCards.size())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Choix invalide. Choisissez entre 1 et " << availableCards.size() << ": ";
            std::cin >> choice;
        }
        
        // Sacrifier la carte choisie
        int index = choice - 1;
        Card* cardToSacrifice = availableCards[index];
        std::string source = cardSources[index];
        
        std::cout << "→ Sacrifice de " << cardToSacrifice->getName() << " depuis " << source << std::endl;
        
        // Retirer la carte de sa source
        if (source == "main") {
            // Trouver l'index dans la main
            for (size_t k = 0; k < hand.size(); ++k) {
                if (hand.getCardAt(k) == cardToSacrifice) {
                    hand.removeCardAt(k);
                    break;
                }
            }
        } else { // défausse
            discard.removeCard(cardToSacrifice);
        }
        
        // Ajouter à la zone de sacrifice (sauf si c'est une Gemme de Feu)
        if (cardToSacrifice->getName() == "Fire Gem") {
            std::cout << "→ Gemme de Feu retourne dans la pile Gemmes de Feu" << std::endl;
        } else {
            player.addToSacrificeZone(cardToSacrifice);
        }
        
        // Appliquer le bonus si présent
        if (m_bonusEffect) {
            std::cout << "→ Bonus de sacrifice appliqué!" << std::endl;
            m_bonusEffect->apply(player, turn);
        }
        
        // Retirer de la liste des cartes disponibles
        availableCards.erase(availableCards.begin() + index);
        cardSources.erase(cardSources.begin() + index);
        
        sacrificedCount++;
        
        // Vérifier s'il reste des cartes
        if (availableCards.empty()) {
            std::cout << "Plus de cartes disponibles à sacrifier." << std::endl;
            break;
        }
    }
    
    std::cout << "\nTotal: " << sacrificedCount << " carte(s) sacrifiée(s)." << std::endl;
}

// GetName
std::string OptionalSacrificeEffect::getName() const {
    return "OptionalSacrificeEffect";
}

// GetValue
int OptionalSacrificeEffect::getValue() {
    return m_count;
}

Effect* OptionalSacrificeEffect::getOption1() const { return nullptr; }
Effect* OptionalSacrificeEffect::getOption2() const { return nullptr; }
const ResourceType* OptionalSacrificeEffect::getResourceType() const { return nullptr; }
const ConditionType* OptionalSacrificeEffect::getConditionType() const { return nullptr; }
const std::string* OptionalSacrificeEffect::getCardTypeFilter() const { return nullptr; }
