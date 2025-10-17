#include "ConditionalEffect.h"
#include "Player.h"
#include "InPlayArea.h"
#include "ChampionCard.h"
#include <iostream>

ConditionalEffect::ConditionalEffect(ResourceType resType, int valuePerUnit, 
                                     ConditionType condType, Faction faction, bool includeSelf)
    : Effect(valuePerUnit), 
      m_resourceType(resType), 
      m_conditionType(condType),
      m_faction(faction),
      m_includeSelf(includeSelf) {}

void ConditionalEffect::apply(Player& player, Turn& turn) {
    int count = countCondition(player);
    int totalValue = getValue() * count;
    
    if (totalValue == 0) {
        std::cout << player.getName() << " : Aucun bonus conditionnel (0 éléments)." << std::endl;
        return;
    }
    
    // Appliquer l'effet selon le type de ressource
    switch (m_resourceType) {
        case ResourceType::Gold:
            turn.addGold(totalValue);
            std::cout << player.getName() << " gagne " << totalValue 
                      << " d'Or (+" << getValue() << " × " << count << ")" << std::endl;
            break;
            
        case ResourceType::Combat:
            turn.addCombat(totalValue);
            std::cout << player.getName() << " gagne " << totalValue 
                      << " de Combat (+" << getValue() << " × " << count << ")" << std::endl;
            break;
            
        case ResourceType::Health:
            player.heal(totalValue);
            std::cout << player.getName() << " gagne " << totalValue 
                      << " PV (+" << getValue() << " × " << count << ")" << std::endl;
            break;
    }
}

int ConditionalEffect::countCondition(Player& player) const {
    InPlayArea& playArea = player.getPlayArea();
    int count = 0;
    
    switch (m_conditionType) {
        case ConditionType::ChampionCount: {
            // Compter tous les champions en jeu
            count = static_cast<int>(playArea.getChampionCount());
            break;
        }
        
        case ConditionType::GuardCount: {
            // Compter tous les gardes en jeu
            std::vector<ChampionCard>& champions = playArea.getChampions();
            for (const auto& champion : champions) {
                if (champion.isGuard()) {
                    count++;
                }
            }
            break;
        }
        
        case ConditionType::FactionCardCount: {
            // Compter toutes les cartes de la faction spécifiée
            std::vector<Card*>& cards = playArea.getCards();
            for (const auto& card : cards) {
                if (card->getFaction() == m_faction) {
                    count++;
                }
            }
            
            std::vector<ChampionCard>& champions = playArea.getChampions();
            for (const auto& champion : champions) {
                if (champion.getFaction() == m_faction) {
                    count++;
                }
            }
            break;
        }
        
        case ConditionType::OtherChampionCount: {
            // Compter les AUTRES champions (exclut la carte qui active l'effet)
            count = static_cast<int>(playArea.getChampionCount());
            if (!m_includeSelf && count > 0) {
                count--; // Exclure la carte elle-même
            }
            break;
        }
        
        case ConditionType::OtherGuardCount: {
            // Compter les AUTRES gardes
            std::vector<ChampionCard>& champions = playArea.getChampions();
            for (const auto& champion : champions) {
                if (champion.isGuard()) {
                    count++;
                }
            }
            if (!m_includeSelf && count > 0) {
                count--; // Exclure la carte elle-même si c'est un garde
            }
            break;
        }
    }
    
    return count;
}

Effect* ConditionalEffect::clone() const {
    return new ConditionalEffect(m_resourceType, getValue(), m_conditionType, 
                                 m_faction, m_includeSelf);
}

std::string ConditionalEffect::getName() const {
    std::string name = "ConditionalEffect(";
    
    // Type de ressource
    switch (m_resourceType) {
        case ResourceType::Gold: name += "Gold"; break;
        case ResourceType::Combat: name += "Combat"; break;
        case ResourceType::Health: name += "Health"; break;
    }
    
    name += ", +" + std::to_string(getValue()) + " per ";
    
    // Type de condition
    switch (m_conditionType) {
        case ConditionType::ChampionCount: name += "Champion"; break;
        case ConditionType::GuardCount: name += "Guard"; break;
        case ConditionType::FactionCardCount: name += "Faction Card"; break;
        case ConditionType::OtherChampionCount: name += "Other Champion"; break;
        case ConditionType::OtherGuardCount: name += "Other Guard"; break;
    }
    
    name += ")";
    return name;
}
