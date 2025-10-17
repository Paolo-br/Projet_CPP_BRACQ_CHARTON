#ifndef SACRIFICE_EFFECT_H
#define SACRIFICE_EFFECT_H

#include "Effect.h"

class SacrificeEffect : public Effect {
public:
    SacrificeEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    int getValue();
};

#endif