#include "SacrificeAbility.h"
#include "Player.h"
#include "Turn.h"
#include <iostream>

SacrificeAbility::SacrificeAbility() {
    std::cout << "Abilité de sacrifice créée" << std::endl;
}

SacrificeAbility::~SacrificeAbility() {
    std::cout << "Abilité de sacrifice détruite" << std::endl;
}

void SacrificeAbility::trigger(Player& owner, Turn& turn) {
    std::cout << "Abilité de sacrifice déclenchée" << std::endl;
    
    // Appliquer tous les effets de cette capacité
    for (auto& effect : m_effs) {
        if (effect) {
            effect->apply(owner, turn);
        }
    }
}

std::string SacrificeAbility::getName() const {return "SacrificeAbility";}

std::vector<Effect*> SacrificeAbility::getEffect() const {return m_effs;}

SacrificeAbility* SacrificeAbility::clone() const {
    std::vector<Effect*> clonedEffects;
    for (const auto& effect : m_effs) {
        clonedEffects.push_back(effect->clone());
    }
    return new SacrificeAbility(clonedEffects);
}