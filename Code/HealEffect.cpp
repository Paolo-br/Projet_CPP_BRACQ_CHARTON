#include "HealEffect.h"
#include "Player.h"
#include <iostream>

void HealEffect::apply(Player& target, Player& owner) {
    std::cout << owner.getName() << " soigne " << m_value << " points de vie pour " << target.getName() << "." << std::endl;
    int health = target.getHealth();
    target.setHealth(health + m_value);
}
