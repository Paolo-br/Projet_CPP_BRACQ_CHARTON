#include "ActivateAbility.h"
#include "Player.h"
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
void ActivateAbility::trigger(Player& owner, Player& opponent) {
    std::cout<< "Abilité activable déclenchée" << std::endl;
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}

std::vector<Effect*> ActivateAbility::getEffect() const {
    return m_effs;
}