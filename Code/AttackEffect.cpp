#include "AttackEffect.h"
#include "Player.h"
#include <iostream>

void AttackEffect::apply(Player& target, Player& owner) {
    std::cout << owner.getName() << " inflige " << m_value << " points de dégâts à " << target.getName() << "." << std::endl;
    int health = target.getHealth();
    target.setHealth(health - m_value);
}
