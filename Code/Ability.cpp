#include "Ability.h"
#include "Player.h"
#include <iostream>

Ability::Ability() {
    std::cout<< "Abilité crée" << std::endl;
}

Ability::~Ability() {
    std::cout<< "Abilité détruite" << std::endl;
}
