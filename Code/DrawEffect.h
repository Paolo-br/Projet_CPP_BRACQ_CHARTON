#ifndef DRAW_EFFECT_H
#define DRAW_EFFECT_H

#include "Effect.h"

class DrawEffect : public Effect {
private:
    int m_value;
public:
    DrawEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
};

#endif