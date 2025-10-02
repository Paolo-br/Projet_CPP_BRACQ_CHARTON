#ifndef __ALLYABILITY_H
#define __ALLYABILITY_H
#include "Player.h"
#include "Ability.h"

class AllyAbility :public Ability {
    public:
    AllyAbility() {}
    ~AllyAbility() {}
    void trigger(Player Owner, Player opponent) override {}

}
;
#endif