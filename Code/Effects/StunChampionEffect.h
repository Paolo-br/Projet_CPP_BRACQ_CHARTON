#ifndef __STUNCHAMPIONEFFECT_H
#define __STUNCHAMPIONEFFECT_H

#include "Effect.h"
#include "../Turn.h"

class StunChampionEffect : public Effect {
public:
    StunChampionEffect();
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
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
