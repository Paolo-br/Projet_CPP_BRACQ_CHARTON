#ifndef __DISCARDOPPONENTEFFECT_H
#define __DISCARDOPPONENTEFFECT_H

#include "Effect.h"
#include "Turn.h"

class DiscardOpponentEffect : public Effect {
public:
    DiscardOpponentEffect(int cardCount = 1);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
};

#endif
