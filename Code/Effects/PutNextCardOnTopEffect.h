#ifndef __PUTNEXTCARDONTOPEFFECT_H
#define __PUTNEXTCARDONTOPEFFECT_H

#include "Effect.h"
#include <string>

class Player;
class Turn;

/**
 * Effet qui fait que la prochaine carte acquise va sur le dessus du deck au lieu de la défausse
 */
class PutNextCardOnTopEffect : public Effect {
private:
    std::string m_cardTypeFilter; // "Action", "Any" pour filtrer le type de carte

public:
    PutNextCardOnTopEffect(const std::string& cardTypeFilter = "Any");
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
    const std::string* getCardTypeFilter() const override { return &m_cardTypeFilter; }
    
    Effect* getOption1() const override;
    Effect* getOption2() const override;
    const ResourceType* getResourceType() const override;
    const ConditionType* getConditionType() const override;
    bool getIsOptional() const override;
    int getCount() const override;
    int getMaxCount() const override;
    Effect* getBonusEffect() const override;
};

#endif
