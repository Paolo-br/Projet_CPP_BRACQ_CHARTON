#ifndef __PRIMARYABILITY_H
#define __PRIMARYABILITY_H

#include "Ability.h"

class Player;

class PrimaryAbility : public Ability {
    public:
    PrimaryAbility() {}
    ~PrimaryAbility() {}
    void trigger(Player& Owner, Player& opponent) override;

};
#endif