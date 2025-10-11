#ifndef HEAL_EFFECT_H
#define HEAL_EFFECT_H

#include "Effect.h"

class HealEffect : public Effect {
private:
    int m_value;
public:
    HealEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
};

#endif