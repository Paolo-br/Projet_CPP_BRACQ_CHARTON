#ifndef __GOLDEFFECT_H
#define __GOLDEFFECT_H

#include "Effect.h"
#include "Turn.h"

class GoldEffect : public Effect {
public:
    GoldEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    int getValue();
};

#endif
