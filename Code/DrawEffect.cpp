#include "DrawEffect.h"
#include "Player.h"
#include "Turn.h"

DrawEffect::DrawEffect(int value) : Effect(value) {}

void DrawEffect::apply(Player& player, Turn& turn) {
    std::cout << "On a tant de point d'attaque"<<turn.getCombatReserve()<<std::endl;
    for (int i = 0; i < Effect::getValue(); ++i) {
        player.getDeck().draw();
    }
}

Effect* DrawEffect::clone() const {
    return new DrawEffect(*this);
}

std::string DrawEffect::getName() const {return "DrawEffect";}
