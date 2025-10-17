#include "Ability.h"
#include "Player.h"
#include "Effect.h"
#include "Turn.h"
#include <iostream>

Ability::Ability() {
    std::cout<< "Abilité crée" << std::endl;
}
Ability::Ability(std::vector<Effect*> effs):m_effs(effs) {
    std::cout<< "Abilité crée" << std::endl;
}

void Ability::trigger(Player& Owner, Turn& turn){
    std::cout << Owner.getName() << std::endl;
    std::cout << turn.getCombatReserve() << std::endl;
}
std::vector<Effect*> Ability::getEffect() const {return m_effs;}


std::string Ability::getName() const {return "Ability";}