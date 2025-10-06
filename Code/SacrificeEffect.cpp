#include "SacrificeEffect.h"
#include "Player.h"
#include <iostream>

void SacrificeEffect::apply(Player& target, Player& owner) {
    std::cout << owner.getName() << " sacrifie " << m_value << " carte(s) de " << target.getName() << "." << std::endl;
    for (int i = 0; i < m_value; ++i) {
        std::cout<< "SacrificeEffect: Sacrificing card " << (i + 1) << " of " << m_value << std::endl;
    }
}
