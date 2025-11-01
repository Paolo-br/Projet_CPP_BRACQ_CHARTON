#include "ActivateAbility.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>

ActivateAbility::ActivateAbility() {
    std::cout<< "Abilité activable crée" << std::endl;
}

ActivateAbility::ActivateAbility(std::vector<Effect*> effs):Ability(effs) {
    std::cout<< "Abilité activable crée" << std::endl;
}

ActivateAbility::~ActivateAbility() {
    std::cout<< "Abilité activable détruite" << std::endl;
}

void ActivateAbility::trigger(Player& owner, Turn& turn) {
    std::cout<< "Abilité activable déclenchée" << std::endl;
    
    // Appliquer tous les effets de cette capacité
    for (auto& effect : m_effs) {
        if (effect) {
            effect->apply(owner, turn);
        }
    }
}

std::string ActivateAbility::getName() const{return "ActivateAbility";}

std::vector<Effect*> ActivateAbility::getEffect() const {
    return m_effs;
}

ActivateAbility* ActivateAbility::clone() const {
    std::vector<Effect*> clonedEffects;
    for (const auto& effect : m_effs) {
        clonedEffects.push_back(effect->clone());
    }
    return new ActivateAbility(clonedEffects);
}