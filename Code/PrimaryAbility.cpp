#include "PrimaryAbility.h"
#include "Player.h"
#include <iostream>

PrimaryAbility::PrimaryAbility() {
    std::cout<< "Abilité primaire crée" << std::endl;
}
PrimaryAbility::~PrimaryAbility() {
    std::cout<< "Abilité primaire détruite" << std::endl;
}
void PrimaryAbility::trigger(Player& Owner, Player& opponent) {
    std::cout<< "Abilité primaire déclenchée" << std::endl;
}