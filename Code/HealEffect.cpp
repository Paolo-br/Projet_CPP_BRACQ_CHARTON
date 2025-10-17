#include "HealEffect.h"
#include "Player.h"
#include "Turn.h"

HealEffect::HealEffect(int value) : Effect(value) {}

void HealEffect::apply(Player& player, Turn& turn) {
    std::cout << "On a tant de point d'attaque"<<turn.getCombatReserve()<<std::endl;
    player.heal(Effect::getValue());
}

Effect* HealEffect::clone() const {
    return new HealEffect(*this);
}


std::string HealEffect::getName() const { return "HealEffect";}

int HealEffect::getValue(){return Effect::getValue();}