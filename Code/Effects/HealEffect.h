#ifndef HEAL_EFFECT_H
#define HEAL_EFFECT_H

#include "Effect.h"

class HealEffect : public Effect {
public:
    HealEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    int getValue();
    
    Effect* getOption1() const override;
    Effect* getOption2() const override;
    const ResourceType* getResourceType() const override;
    const ConditionType* getConditionType() const override;
    bool getIsOptional() const override;
    const std::string* getCardTypeFilter() const override;
    int getCount() const override;
    int getMaxCount() const override;
    Effect* getBonusEffect() const override;
};

#endif