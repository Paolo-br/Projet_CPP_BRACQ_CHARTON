#include "SacrificeEffect.h"
#include "Player.h"
#include "Turn.h"
#include <iostream>


SacrificeEffect::SacrificeEffect(int value) : Effect(value) {}

Effect* SacrificeEffect::clone() const {
    return new SacrificeEffect(*this);
}

void SacrificeEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " sacrifie " << turn.getCombatReserve() << " carte(s) de " << std::endl;
    for (int i = 0; i < Effect::getValue(); ++i) {
        std::cout<< "SacrificeEffect: Sacrificing card " << (i + 1) << " of " << Effect::getValue() << std::endl;
    }
}

std::string SacrificeEffect::getName() const {return "SacrificeEffect";}

int SacrificeEffect::getValue(){return Effect::getValue();}