#include "AttackEffect.h"
#include "Player.h"

#include <iostream>


AttackEffect::AttackEffect(int value) : m_value(value) {}

void AttackEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " gagne " << m_value << " points de dégâts "<< std::endl;
    turn.addCombat(m_value);

}

Effect* AttackEffect::clone() const {
    return new AttackEffect(m_value);
}