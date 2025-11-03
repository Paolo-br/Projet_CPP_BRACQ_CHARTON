#include "GoldEffect.h"
#include "../Player.h"
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

Effect* GoldEffect::getOption1() const { return nullptr; }
Effect* GoldEffect::getOption2() const { return nullptr; }
const ResourceType* GoldEffect::getResourceType() const { return nullptr; }
const ConditionType* GoldEffect::getConditionType() const { return nullptr; }
bool GoldEffect::getIsOptional() const { return false; }
const std::string* GoldEffect::getCardTypeFilter() const { return nullptr; }
int GoldEffect::getCount() const { return 0; }
int GoldEffect::getMaxCount() const { return 0; }
Effect* GoldEffect::getBonusEffect() const { return nullptr; }