#include "SacrificeEffect.h"
#include "Player.h"
#include "Turn.h"
#include <iostream>


SacrificeEffect::SacrificeEffect(int value) : m_value(value) {}

Effect* SacrificeEffect::clone() const {
    return new SacrificeEffect(*this);
}

void SacrificeEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " sacrifie " << turn.getCombatReserve() << " carte(s) de " << std::endl;
    for (int i = 0; i < m_value; ++i) {
        std::cout<< "SacrificeEffect: Sacrificing card " << (i + 1) << " of " << m_value << std::endl;
    }
}
