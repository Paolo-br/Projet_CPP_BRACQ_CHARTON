#include "Ability.h"
#include "Player.h"
#include "Effect.h"
#include <iostream>

Ability::Ability() {
    std::cout<< "Abilité crée" << std::endl;
}
Ability::Ability(std::vector<Effect*> effs):m_effs(effs) {
    std::cout<< "Abilité crée" << std::endl;
}


std::vector<Effect*> Ability::getEffect() const {return m_effs;}