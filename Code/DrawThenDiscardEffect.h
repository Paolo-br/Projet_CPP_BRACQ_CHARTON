#ifndef DRAW_THEN_DISCARD_EFFECT_H
#define DRAW_THEN_DISCARD_EFFECT_H

#include "Effect.h"

class Player;
class Turn;

/**
 * Effet qui fait piocher puis défausser des cartes
 * Utilisé pour : "Draw X cards then discard Y cards" ou "You may draw a card. If you do, discard a card"
 */
class DrawThenDiscardEffect : public Effect {
private:
    int m_drawCount;      // Nombre de cartes à piocher
    int m_discardCount;   // Nombre de cartes à défausser
    bool m_optional;      // Si l'effet est optionnel ("may")
    
public:
    DrawThenDiscardEffect(int drawCount, int discardCount, bool optional = false);
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
    // Getters
    int getDrawCount() const { return m_drawCount; }
    int getDiscardCount() const { return m_discardCount; }
    bool isOptional() const { return m_optional; }
};

#endif
