#ifndef __PRIMARYABILITY_H
#define __PRIMARYABILITY_H

#include "Ability.h"
#include <vector>
#include <iostream>

class Player;

class PrimaryAbility : public Ability {
    public:
    PrimaryAbility(std::vector<Effect*> effs);
    PrimaryAbility();
    ~PrimaryAbility();
    void trigger(Player& owner, Turn& turn) override;
    std::vector<Effect*> getEffect() const override;
    std::string getName() const override;
    PrimaryAbility* clone() const override;

};
#endif