#include "SacrificeEffect.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>


SacrificeEffect::SacrificeEffect(int value) : Effect(value) {}

Effect* SacrificeEffect::clone() const {
    return new SacrificeEffect(*this);
}

void SacrificeEffect::apply(Player& player, Turn& turn) {
    std::cout << player.getName() << " sacrifie " << turn.getCombatReserve() << " carte(s) de " << std::endl;
    for (int i = 0; i < Effect::getValue(); ++i) {
        std::cout<< "SacrificeEffect: Sacrificing card " << (i + 1) << " of " << Effect::getValue() << std::endl;
    }
}

std::string SacrificeEffect::getName() const {return "SacrificeEffect";}

int SacrificeEffect::getValue(){return Effect::getValue();}

Effect* SacrificeEffect::getOption1() const { return nullptr; }
Effect* SacrificeEffect::getOption2() const { return nullptr; }
const ResourceType* SacrificeEffect::getResourceType() const { return nullptr; }
const ConditionType* SacrificeEffect::getConditionType() const { return nullptr; }
bool SacrificeEffect::getIsOptional() const { return false; }
const std::string* SacrificeEffect::getCardTypeFilter() const { return nullptr; }
int SacrificeEffect::getCount() const { return 0; }
int SacrificeEffect::getMaxCount() const { return 0; }
Effect* SacrificeEffect::getBonusEffect() const { return nullptr; }