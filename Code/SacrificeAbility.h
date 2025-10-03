#ifndef __SACRIFICE_ABILITY_H
#define __SACRIFICE_ABILITY_H

#include "Ability.h"

class SacrificeAbility : public Ability {
    public:
    SacrificeAbility();
    ~SacrificeAbility();
    void trigger(Player& owner, Player& opponent) override;
};

#endif
