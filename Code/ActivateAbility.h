#ifndef __ACTIVATEABILITY_H
#define __ACTIVATEABILITY_H

#include "Ability.h"
#include <vector>
#include <iostream>


class Player;
class ActivateAbility : public Ability {
    public:
    ActivateAbility();
    ActivateAbility(std::vector<Effect*> effs);
    ~ActivateAbility();
    void trigger(Player& owner, Player& opponent) override;
    std::vector<Effect*> getEffect() const override;

};
#endif