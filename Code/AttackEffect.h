#ifndef __ATTACKEFFECT_H
#define __ATTACKEFFECT_H

#include "Effect.h"
#include "Turn.h"
class AttackEffect : public Effect {
public:
    AttackEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    int getValue();

};

#endif
