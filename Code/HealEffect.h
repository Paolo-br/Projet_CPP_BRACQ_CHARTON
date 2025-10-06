#ifndef __HEALEFFECT_H
#define __HEALEFFECT_H

#include "Effect.h"

class HealEffect : public Effect {
public:
    HealEffect(int value) : Effect(value) {}
    void apply(Player& target, Player& owner) override;
};

#endif
