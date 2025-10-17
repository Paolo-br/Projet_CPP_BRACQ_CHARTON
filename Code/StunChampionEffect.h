#ifndef __STUNCHAMPIONEFFECT_H
#define __STUNCHAMPIONEFFECT_H

#include "Effect.h"
#include "Turn.h"

class StunChampionEffect : public Effect {
public:
    StunChampionEffect();
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
};

#endif
