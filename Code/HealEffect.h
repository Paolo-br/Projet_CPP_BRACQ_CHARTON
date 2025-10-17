#ifndef HEAL_EFFECT_H
#define HEAL_EFFECT_H

#include "Effect.h"

class HealEffect : public Effect {
public:
    HealEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    int getValue();
};

#endif