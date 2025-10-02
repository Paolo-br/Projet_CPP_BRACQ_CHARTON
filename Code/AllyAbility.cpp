#include "AllyAbility.h"
#include "Player.h"
#include <iostream>

AllyAbility::AllyAbility() {
    std::cout<< "Abilité d'allié crée" << std::endl;
}
AllyAbility::~AllyAbility() {
    std::cout<< "Abilité d'allié détruite" << std::endl;
}
void AllyAbility::trigger(Player Owner, Player opponent) {
    std::cout<< "Abilité d'allié déclenchée" << std::endl;
}