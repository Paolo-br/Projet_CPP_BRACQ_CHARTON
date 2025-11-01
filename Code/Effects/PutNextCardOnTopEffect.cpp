#include "PutNextCardOnTopEffect.h"
#include "../Player.h"
#include "../Turn.h"
#include <iostream>

PutNextCardOnTopEffect::PutNextCardOnTopEffect(const std::string& cardTypeFilter)
    : Effect(0), m_cardTypeFilter(cardTypeFilter) {
}

void PutNextCardOnTopEffect::apply(Player& player, Turn& turn) {
    (void)player;
    
    if (m_cardTypeFilter == "Action") {
        turn.setNextActionGoesOnTop(true);
        std::cout << "→ La prochaine carte ACTION acquise ira sur le dessus de votre deck!" << std::endl;
    } else {
        turn.setNextCardGoesOnTop(true);
        std::cout << "→ La prochaine carte acquise ira sur le dessus de votre deck!" << std::endl;
    }
}

Effect* PutNextCardOnTopEffect::clone() const {
    return new PutNextCardOnTopEffect(*this);
}

std::string PutNextCardOnTopEffect::getName() const {
    return "PutNextCardOnTopEffect";
}

Effect* PutNextCardOnTopEffect::getOption1() const { return nullptr; }
Effect* PutNextCardOnTopEffect::getOption2() const { return nullptr; }
const ResourceType* PutNextCardOnTopEffect::getResourceType() const { return nullptr; }
const ConditionType* PutNextCardOnTopEffect::getConditionType() const { return nullptr; }
bool PutNextCardOnTopEffect::getIsOptional() const { return false; }
int PutNextCardOnTopEffect::getCount() const { return 0; }
int PutNextCardOnTopEffect::getMaxCount() const { return 0; }
Effect* PutNextCardOnTopEffect::getBonusEffect() const { return nullptr; }