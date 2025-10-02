#ifndef __ABILITY_H
#define __ABILITY_H
#include "Player.h"

class Ability {
    public:
    Ability() {}
    ~Ability() {}
    virtual void trigger(Player Owner, Player opponent) {}

};
#endif