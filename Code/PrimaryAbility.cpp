#include "PrimaryAbility.h"
#include "Player.h"
#include <iostream>

PrimaryAbility::PrimaryAbility() {
    std::cout<< "Abilité primaire crée" << std::endl;
}
PrimaryAbility::~PrimaryAbility() {
    std::cout<< "Abilité primaire détruite" << std::endl;
}
void PrimaryAbility::trigger(Player& owner, Player& opponent) {
    std::cout<< "Abilité primaire déclenchée" << std::endl;
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}