#include "GoldEffect.h"
#include "Player.h"
#include <iostream>

void GoldEffect::apply(Player& target, Player& owner) {
    std::cout << owner.getName() << " gagne " << m_value << " pièces d'or." << std::endl;
    int gold = owner.getGold();
    owner.setGold(gold + m_value);
    std::cout << "Opposant : " << target.getName() << std::endl;
}
