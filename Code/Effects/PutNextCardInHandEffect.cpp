#include "PutNextCardInHandEffect.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>

PutNextCardInHandEffect::PutNextCardInHandEffect() : Effect(0) {
}

void PutNextCardInHandEffect::apply(Player& player, Turn& turn) {
    (void)player; 
    
    turn.setNextCardGoesInHand(true);
    std::cout << "→ La prochaine carte acquise ira directement dans votre main!" << std::endl;
}

Effect* PutNextCardInHandEffect::clone() const {
    return new PutNextCardInHandEffect(*this);
}

std::string PutNextCardInHandEffect::getName() const {
    return "PutNextCardInHandEffect";
}

Effect* PutNextCardInHandEffect::getOption1() const { return nullptr; }
Effect* PutNextCardInHandEffect::getOption2() const { return nullptr; }
const ResourceType* PutNextCardInHandEffect::getResourceType() const { return nullptr; }
const ConditionType* PutNextCardInHandEffect::getConditionType() const { return nullptr; }
bool PutNextCardInHandEffect::getIsOptional() const { return false; }
const std::string* PutNextCardInHandEffect::getCardTypeFilter() const { return nullptr; }
int PutNextCardInHandEffect::getCount() const { return 0; }
int PutNextCardInHandEffect::getMaxCount() const { return 0; }
Effect* PutNextCardInHandEffect::getBonusEffect() const { return nullptr; }
