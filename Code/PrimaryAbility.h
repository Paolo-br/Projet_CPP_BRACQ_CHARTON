#ifndef __PRIMARYABILITY_H
#define __PRIMARYABILITY_H
#include "Player.h"
#include "Ability.h"

class PrimaryAbility : public Ability {
    public:
    PrimaryAbility() {}
    ~PrimaryAbility() {}
    void trigger(Player Owner, Player opponent) override {}

};
#endif