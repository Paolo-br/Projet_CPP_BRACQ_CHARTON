#ifndef __GOLDEFFECT_H
#define __GOLDEFFECT_H

#include "Effect.h"

class GoldEffect : public Effect {
public:
    GoldEffect(int value) : Effect(value) {}
    void apply(Player& target, Player& owner) override;
};

#endif
