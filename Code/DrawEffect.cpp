#include "DrawEffect.h"
#include "Player.h"
#include <iostream>

void DrawEffect::apply(Player& target, Player& owner) {
    std::cout << owner.getName() << " fait piocher " << m_value << " carte(s) à " << target.getName() << "." << std::endl;
    for (int i = 0; i < m_value; ++i) {
        target.drawCard(target.getDeck().draw());
    }
}
