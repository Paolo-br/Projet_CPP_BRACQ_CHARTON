#include "DrawEffect.h"
#include "Player.h"
#include "Turn.h"

DrawEffect::DrawEffect(int value) : m_value(value) {}

void DrawEffect::apply(Player& player, Turn& turn) {
    std::cout << "On a tant de point d'attaque"<<turn.getCombatReserve()<<std::endl;
    for (int i = 0; i < m_value; ++i) {
        player.getDeck().draw();
    }
}

Effect* DrawEffect::clone() const {
    return new DrawEffect(*this);
}
