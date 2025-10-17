#ifndef __PREPARECHAMPIONEFFECT_H
#define __PREPARECHAMPIONEFFECT_H

#include "Effect.h"
#include "Turn.h"

class PrepareChampionEffect : public Effect {
public:
    PrepareChampionEffect();
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
};

#endif
