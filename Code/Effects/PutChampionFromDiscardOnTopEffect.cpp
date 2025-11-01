#include "PutChampionFromDiscardOnTopEffect.h"
#include "../Player.h"
#include "../Turn.h"
#include "../Cards/DiscardPile.h"
#include "../Cards/Deck.h"
#include "../CardsType/Card.h"
#include "../CardsType/ChampionCard.h"
#include <iostream>
#include <limits>
#include <vector>

PutChampionFromDiscardOnTopEffect::PutChampionFromDiscardOnTopEffect()
    : Effect(0) {
}

void PutChampionFromDiscardOnTopEffect::apply(Player& player, Turn& turn) {
    (void)turn;
    
    DiscardPile& discard = player.getDiscardPile();
    
    if (discard.isEmpty()) {
        std::cout << player.getName() << " n'a aucune carte dans sa défausse." << std::endl;
        return;
    }
    
    // Filtrer pour ne garder que les Champions
    std::vector<Card*> champions;
    const std::vector<Card*>& allCards = discard.getCards();
    
    for (Card* card : allCards) {
        // Vérifier si c'est un Champion (on peut utiliser dynamic_cast ou vérifier le type)
        if (ChampionCard* champion = dynamic_cast<ChampionCard*>(card)) {
            champions.push_back(champion);
        }
    }
    
    if (champions.empty()) {
        std::cout << player.getName() << " n'a aucun Champion dans sa défausse." << std::endl;
        return;
    }
    
    // Afficher les Champions de la défausse
    std::cout << "\n=== CHAMPIONS DANS LA DÉFAUSSE DE " << player.getName() << " ===" << std::endl;
    for (size_t i = 0; i < champions.size(); ++i) {
        ChampionCard* champion = dynamic_cast<ChampionCard*>(champions[i]);
        if (champion) {
            std::cout << "[" << (i + 1) << "] " << champion->getName() 
                      << " (Défense: " << champion->getDefense() << ")" << std::endl;
        }
    }
    
    int choice;
    while (true) {
        std::cout << "Choisissez un Champion à placer sur votre deck: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide!" << std::endl;
            continue;
        }
        
        if (choice > 0 && choice <= static_cast<int>(champions.size())) {
            Card* selectedChampion = champions[choice - 1];
            
            // Retirer le Champion de la défausse
            discard.removeCard(selectedChampion);
            
            // Placer le Champion sur le dessus du deck
            player.getDeck().addCardOnTop(selectedChampion);
            
            std::cout << "→ " << selectedChampion->getName() 
                      << " placé sur le dessus du deck de " << player.getName() << "!" << std::endl;
            return;
        }
        
        std::cout << "Choix invalide!" << std::endl;
    }
}

Effect* PutChampionFromDiscardOnTopEffect::clone() const {
    return new PutChampionFromDiscardOnTopEffect(*this);
}

std::string PutChampionFromDiscardOnTopEffect::getName() const {
    return "PutChampionFromDiscardOnTopEffect";
}

Effect* PutChampionFromDiscardOnTopEffect::getOption1() const { return nullptr; }
Effect* PutChampionFromDiscardOnTopEffect::getOption2() const { return nullptr; }
const ResourceType* PutChampionFromDiscardOnTopEffect::getResourceType() const { return nullptr; }
const ConditionType* PutChampionFromDiscardOnTopEffect::getConditionType() const { return nullptr; }
bool PutChampionFromDiscardOnTopEffect::getIsOptional() const { return false; }
const std::string* PutChampionFromDiscardOnTopEffect::getCardTypeFilter() const { return nullptr; }
int PutChampionFromDiscardOnTopEffect::getCount() const { return 0; }
int PutChampionFromDiscardOnTopEffect::getMaxCount() const { return 0; }
Effect* PutChampionFromDiscardOnTopEffect::getBonusEffect() const { return nullptr; }