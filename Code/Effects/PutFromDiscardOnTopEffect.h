#ifndef __PUTFROMDISCARDONTOPEFFECT_H
#define __PUTFROMDISCARDONTOPEFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui permet de placer une carte de la défausse sur le dessus du deck
 */
class PutFromDiscardOnTopEffect : public Effect {
private:
    bool m_optional; // Si l'effet est optionnel 

public:
    PutFromDiscardOnTopEffect(bool optional = true);
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
    bool getIsOptional() const override { return m_optional; }
    
    Effect* getOption1() const override;
    Effect* getOption2() const override;
    const ResourceType* getResourceType() const override;
    const ConditionType* getConditionType() const override;
    const std::string* getCardTypeFilter() const override;
    int getCount() const override;
    int getMaxCount() const override;
    Effect* getBonusEffect() const override;
};

#endif
