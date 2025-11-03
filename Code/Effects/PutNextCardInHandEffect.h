#ifndef __PUTNEXTCARDINHANDEFFECT_H
#define __PUTNEXTCARDINHANDEFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui fait que la prochaine carte acquise va directement en main au lieu de la défausse
 */
class PutNextCardInHandEffect : public Effect {
public:
    PutNextCardInHandEffect();
    
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
