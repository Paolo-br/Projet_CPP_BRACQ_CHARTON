#include "ActivateAbility.h"
#include "Player.h"
#include <iostream>

ActivateAbility::ActivateAbility() {
    std::cout<< "Abilité activable crée" << std::endl;
}
ActivateAbility::~ActivateAbility() {
    std::cout<< "Abilité activable détruite" << std::endl;
}
void ActivateAbility::trigger(Player Owner, Player opponent) {
    std::cout<< "Abilité activable déclenchée" << std::endl;
}