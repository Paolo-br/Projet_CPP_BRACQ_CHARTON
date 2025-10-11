#include "AllyAbility.h"
#include "Player.h"
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

void AllyAbility::trigger(Player& owner, Player& opponent) {
    std::cout<< "Abilité d'allié déclenchée" << std::endl;
        std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}