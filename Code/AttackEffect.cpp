#include "AttackEffect.h"
#include "Player.h"

#include <iostream>


AttackEffect::AttackEffect(int value) : Effect(value) {}

void AttackEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " gagne " << Effect::getValue() << " points de dégâts "<< std::endl;
    turn.addCombat(Effect::getValue());

}

Effect* AttackEffect::clone() const {
    return new AttackEffect(Effect::getValue());
}

std::string AttackEffect::getName() const {return "AttackEffect";}

int AttackEffect::getValue() {return Effect::getValue();}