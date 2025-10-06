#ifndef __ACTIVATEABILITY_H
#define __ACTIVATEABILITY_H

#include "Ability.h"

class Player;
class ActivateAbility : public Ability {
    public:
    ActivateAbility();
    ~ActivateAbility();
    void trigger(Player& owner, Player& opponent) override;

};
#endif