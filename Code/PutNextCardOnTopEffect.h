#ifndef __PUTNEXTCARDONTOPEFFECT_H
#define __PUTNEXTCARDONTOPEFFECT_H

#include "Effect.h"
#include <string>

class Player;
class Turn;

/**
 * Effet qui fait que la prochaine carte acquise va sur le dessus du deck au lieu de la défausse
 */
class PutNextCardOnTopEffect : public Effect {
private:
    std::string m_cardTypeFilter; // "Action", "Any" pour filtrer le type de carte

public:
    PutNextCardOnTopEffect(const std::string& cardTypeFilter = "Any");
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
    std::string getCardTypeFilter() const { return m_cardTypeFilter; }
};

#endif
