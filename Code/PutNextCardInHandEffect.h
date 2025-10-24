#ifndef __PUTNEXTCARDINHANDEFFECT_H
#define __PUTNEXTCARDINHANDEFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui fait que la prochaine carte acquise va directement en main au lieu de la défausse
 */
class PutNextCardInHandEffect : public Effect {
public:
    PutNextCardInHandEffect();
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
};

#endif
