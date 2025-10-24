#ifndef __PUTFROMDISCARDONTOPEFFECT_H
#define __PUTFROMDISCARDONTOPEFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui permet de placer une carte de la défausse sur le dessus du deck
 */
class PutFromDiscardOnTopEffect : public Effect {
private:
    bool m_optional; // Si l'effet est optionnel 

public:
    PutFromDiscardOnTopEffect(bool optional = true);
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
    bool isOptional() const { return m_optional; }
};

#endif
