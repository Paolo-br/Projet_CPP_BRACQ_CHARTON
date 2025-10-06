#ifndef __SACRIFICEEFFECT_H
#define __SACRIFICEEFFECT_H

#include "Effect.h"

class SacrificeEffect : public Effect {
public:
    SacrificeEffect(int value) : Effect(value) {}
    void apply(Player& target, Player& owner) override;
};

#endif
