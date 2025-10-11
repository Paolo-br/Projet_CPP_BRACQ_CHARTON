#include "HealEffect.h"
#include "Player.h"
#include "Turn.h"

HealEffect::HealEffect(int value) : m_value(value) {}

void HealEffect::apply(Player& player, Turn& turn) {
    std::cout << "On a tant de point d'attaque"<<turn.getCombatReserve()<<std::endl;
    player.heal(m_value);
}

Effect* HealEffect::clone() const {
    return new HealEffect(*this);
}
