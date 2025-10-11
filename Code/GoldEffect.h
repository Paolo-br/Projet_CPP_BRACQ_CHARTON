#ifndef __GOLDEFFECT_H
#define __GOLDEFFECT_H

#include "Effect.h"
#include "Turn.h"

class GoldEffect : public Effect {
    int m_value;
public:
    GoldEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
};

#endif
