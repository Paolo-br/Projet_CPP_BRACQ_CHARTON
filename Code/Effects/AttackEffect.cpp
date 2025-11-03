#include "AttackEffect.h"
#include "../Player.h"

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

Effect* AttackEffect::getOption1() const { return nullptr; }
Effect* AttackEffect::getOption2() const { return nullptr; }
const ResourceType* AttackEffect::getResourceType() const { return nullptr; }
const ConditionType* AttackEffect::getConditionType() const { return nullptr; }
bool AttackEffect::getIsOptional() const { return false; }
const std::string* AttackEffect::getCardTypeFilter() const { return nullptr; }
int AttackEffect::getCount() const { return 0; }
int AttackEffect::getMaxCount() const { return 0; }
Effect* AttackEffect::getBonusEffect() const { return nullptr; }