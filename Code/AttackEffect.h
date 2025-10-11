#ifndef __ATTACKEFFECT_H
#define __ATTACKEFFECT_H

#include "Effect.h"
#include "Turn.h"
class AttackEffect : public Effect {
    int m_value; // Valeur des dégâts d'attaque
public:
    AttackEffect(int value);
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
};

#endif
