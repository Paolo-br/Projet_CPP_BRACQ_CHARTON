#ifndef __DRAWEFFECT_H
#define __DRAWEFFECT_H

#include "Effect.h"

class DrawEffect : public Effect {
public:
    DrawEffect(int value) : Effect(value) {}
    void apply(Player& target, Player& owner) override;
};

#endif
