#include "GoldEffect.h"
#include "Player.h"
#include <iostream>


GoldEffect::GoldEffect(int value) : m_value(value) {}

void GoldEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " gagne " << m_value << " pièces d'or." << std::endl;
    int gold = player.getGold();
    player.setGold(gold + m_value);
    turn.addGold(m_value);
}

Effect* GoldEffect::clone() const {
    return new GoldEffect(*this);
}