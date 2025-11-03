#ifndef __PUTCHAMPIONFROMDISCARDONTOPEFFECT_H
#define __PUTCHAMPIONFROMDISCARDONTOPEFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui permet de placer un Champion de la défausse sur le dessus du deck
 * Utilisé spécifiquement pour Varrick, the Necromancer
 */
class PutChampionFromDiscardOnTopEffect : public Effect {
public:
    PutChampionFromDiscardOnTopEffect();
    
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
