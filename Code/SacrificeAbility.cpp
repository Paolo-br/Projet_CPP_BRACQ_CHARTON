#include "Player.h"
#include <iostream>
#include "SacrificeAbility.h"

SacrificeAbility::SacrificeAbility() {
    std::cout<< "Abilité de sacrifice crée" << std::endl;
}
SacrificeAbility::~SacrificeAbility() {
    std::cout<< "Abilité de sacrifice détruite" << std::endl;
}
void SacrificeAbility::trigger(Player Owner, Player opponent) {
    std::cout<< "Abilité de sacrifice déclenchée" << std::endl;
}