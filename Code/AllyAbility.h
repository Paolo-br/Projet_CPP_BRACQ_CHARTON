#ifndef __ALLYABILITY_H
#define __ALLYABILITY_H

#include "Ability.h"
#include <vector>
#include <iostream>

class Player;

class AllyAbility :public Ability {
    public:
    AllyAbility();
    AllyAbility(std::vector<Effect*> effs);
    ~AllyAbility();
    void trigger(Player& owner, Turn& turn) override;
    std::vector<Effect*> getEffect() const override;
    std::string getName() const override;
    AllyAbility* clone() const override;

}
;
#endif