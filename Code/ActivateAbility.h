#ifndef __ACTIVATEABILITY_H
#define __ACTIVATEABILITY_H
#include "Player.h"
#include "Ability.h"

class ActivateAbility : public Ability {
    public:
    ActivateAbility() {}
    ~ActivateAbility() {}
    void trigger(Player Owner, Player opponent) override {}

};