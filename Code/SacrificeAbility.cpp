#include "SacrificeAbility.h"
#include "Player.h"
#include <iostream>

SacrificeAbility::SacrificeAbility() {
    std::cout << "Abilité de sacrifice créée" << std::endl;
}

SacrificeAbility::~SacrificeAbility() {
    std::cout << "Abilité de sacrifice détruite" << std::endl;
}

void SacrificeAbility::trigger(Player& owner, Player& opponent) {
    std::cout << "Abilité de sacrifice déclenchée" << std::endl;
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}

std::vector<Effect*> SacrificeAbility::getEffect() const {return m_effs;}