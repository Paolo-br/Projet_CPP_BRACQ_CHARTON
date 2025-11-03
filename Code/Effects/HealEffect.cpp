#include "HealEffect.h"
#include "../Player.h"
#include "../Turn.h"

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

Effect* HealEffect::getOption1() const { return nullptr; }
Effect* HealEffect::getOption2() const { return nullptr; }
const ResourceType* HealEffect::getResourceType() const { return nullptr; }
const ConditionType* HealEffect::getConditionType() const { return nullptr; }
bool HealEffect::getIsOptional() const { return false; }
const std::string* HealEffect::getCardTypeFilter() const { return nullptr; }
int HealEffect::getCount() const { return 0; }
int HealEffect::getMaxCount() const { return 0; }
Effect* HealEffect::getBonusEffect() const { return nullptr; }