#ifndef __DISCARDOPPONENTEFFECT_H
#define __DISCARDOPPONENTEFFECT_H

#include "Effect.h"
#include "../Turn.h"

class DiscardOpponentEffect : public Effect {
public:
    DiscardOpponentEffect(int cardCount = 1);
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
