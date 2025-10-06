#ifndef __ATTACKEFFECT_H
#define __ATTACKEFFECT_H

#include "Effect.h"

class AttackEffect : public Effect {
public:
    AttackEffect(int value) : Effect(value) {}
    void apply(Player& target, Player& owner) override;
};

#endif
