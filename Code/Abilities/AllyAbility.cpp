#include "AllyAbility.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>

AllyAbility::AllyAbility() {
    std::cout<< "Abilité d'allié crée" << std::endl;
}
AllyAbility::AllyAbility(std::vector<Effect*> effs):Ability(effs) {
    std::cout<< "Abilité activable crée" << std::endl;
}

AllyAbility::~AllyAbility() {
    std::cout<< "Abilité d'allié détruite" << std::endl;
}
std::vector<Effect*> AllyAbility::getEffect() const {return m_effs;}

void AllyAbility::trigger(Player& owner, Turn& turn) {
    std::cout<< "Abilité d'allié déclenchée" << std::endl;
    
    // Appliquer tous les effets de cette capacité
    for (auto& effect : m_effs) {
        if (effect) {
            effect->apply(owner, turn);
        }
    }
}

std::string AllyAbility::getName() const{return "AllyAbility";}

AllyAbility* AllyAbility::clone() const {
    std::vector<Effect*> clonedEffects;
    for (const auto& effect : m_effs) {
        clonedEffects.push_back(effect->clone());
    }
    return new AllyAbility(clonedEffects);
}