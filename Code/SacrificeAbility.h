#ifndef __SACRIFICE_ABILITY_H
#define __SACRIFICE_ABILITY_H

#include "Ability.h"
#include <vector>
#include <iostream>

class SacrificeAbility : public Ability {
    public:
    SacrificeAbility();
    SacrificeAbility(std::vector<Effect*> effs):Ability(effs){}
    ~SacrificeAbility();
    void trigger(Player& owner, Turn& turn) override;
    std::vector<Effect*> getEffect() const override;
    std::string getName() const override;
    SacrificeAbility* clone() const override;
};

#endif
