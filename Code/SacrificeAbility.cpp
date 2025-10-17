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
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << turn.getGoldReserve() << std::endl;
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