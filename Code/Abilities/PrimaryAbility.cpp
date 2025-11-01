#include "PrimaryAbility.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>

PrimaryAbility::PrimaryAbility() {
    std::cout<< "Abilité primaire crée" << std::endl;
}

PrimaryAbility::PrimaryAbility(std::vector<Effect*> effs):Ability(effs) {
    std::cout<< "Abilité primaire crée" << std::endl;
} 
PrimaryAbility::~PrimaryAbility() {
    std::cout<< "Abilité primaire détruite" << std::endl;
}
void PrimaryAbility::trigger(Player& owner, Turn& turn) {
    std::cout<< "Abilité primaire déclenchée" << std::endl;
    
    // Appliquer tous les effets de cette capacité
    for (auto& effect : m_effs) {
        if (effect) {
            effect->apply(owner, turn);
        }
    }
}

std::string PrimaryAbility::getName() const {return "PrimaryAbility";}

std::vector<Effect*> PrimaryAbility::getEffect() const { return m_effs;}

PrimaryAbility* PrimaryAbility::clone() const {
    std::vector<Effect*> clonedEffects;
    for (const auto& effect : m_effs) {
        clonedEffects.push_back(effect->clone());
    }
    return new PrimaryAbility(clonedEffects);
}