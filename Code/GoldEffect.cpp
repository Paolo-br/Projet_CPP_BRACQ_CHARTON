#include "GoldEffect.h"
#include "Player.h"
#include <iostream>


GoldEffect::GoldEffect(int value) : Effect(value) {}

void GoldEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " gagne " << Effect::getValue() << " pièces d'or." << std::endl;
    int gold = player.getGold();
    player.setGold(gold + Effect::getValue());
    turn.addGold(Effect::getValue());
}

Effect* GoldEffect::clone() const {
    return new GoldEffect(*this);
}

std::string GoldEffect::getName() const { return "GoldEffect";}
int GoldEffect::getValue() {return Effect::getValue();}