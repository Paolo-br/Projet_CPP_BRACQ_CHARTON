#ifndef __SACRIFICEABILITY_H
#define __SACRIFICEABILITY_H
#include "Player.h"
#include "Ability.h"

class SacrificeAbility : public Ability {
    public:
    SacrificeAbility() {}
    ~SacrificeAbility() {}
    void trigger(Player Owner, Player opponent) override {}

};
