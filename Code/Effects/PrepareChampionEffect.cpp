#include "PrepareChampionEffect.h"
#include "../Player.h"
#include "../InPlayArea.h"
#include "../CardsType/ChampionCard.h"
#include <iostream>
#include <vector>

PrepareChampionEffect::PrepareChampionEffect() : Effect(0) {}

void PrepareChampionEffect::apply(Player& player, Turn& turn) {
    (void)turn; 
    
    std::vector<ChampionCard>& champions = player.getPlayArea().getChampions();
    
    if (champions.empty()) {
        std::cout << "Aucun champion à mobiliser." << std::endl;
        return;
    }
    
    // Afficher les champions démobilisés
    std::cout << "\nChoisissez un champion à mobiliser:" << std::endl;
    int count = 0;
    for (size_t i = 0; i < champions.size(); ++i) {
        if (!champions[i].isReady()) {
            std::cout << (i + 1) << ". " << champions[i].getName() 
                      << " (Démobilisé)" << std::endl;
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "Tous vos champions sont déjà mobilisés !" << std::endl;
        return;
    }
    
    std::cout << "0. Annuler" << std::endl;
    
    int choice;
    std::cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(champions.size())) {
        if (!champions[choice - 1].isReady()) {
            champions[choice - 1].setReady(true);
            std::cout << champions[choice - 1].getName() << " est maintenant mobilisé !" << std::endl;
        } else {
            std::cout << "Ce champion est déjà mobilisé !" << std::endl;
        }
    }
}

Effect* PrepareChampionEffect::clone() const {
    return new PrepareChampionEffect();
}

std::string PrepareChampionEffect::getName() const {
    return "PrepareChampionEffect";
}

Effect* PrepareChampionEffect::getOption1() const { return nullptr; }
Effect* PrepareChampionEffect::getOption2() const { return nullptr; }
const ResourceType* PrepareChampionEffect::getResourceType() const { return nullptr; }
const ConditionType* PrepareChampionEffect::getConditionType() const { return nullptr; }
bool PrepareChampionEffect::getIsOptional() const { return false; }
const std::string* PrepareChampionEffect::getCardTypeFilter() const { return nullptr; }
int PrepareChampionEffect::getCount() const { return 0; }
int PrepareChampionEffect::getMaxCount() const { return 0; }
Effect* PrepareChampionEffect::getBonusEffect() const { return nullptr; }