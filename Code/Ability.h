#ifndef __ABILITY_H
#define __ABILITY_H

#include <vector>
#include <iostream>

class Player;
class Effect;
class Turn;

class Ability {
    protected:
    std::vector<Effect*> m_effs;
    public:
    Ability();
    Ability(std::vector<Effect*> effs);
    virtual ~Ability()=default;
    int getValue()const;
    virtual void trigger(Player& Owner, Turn& turn);
    virtual std::vector<Effect*> getEffect() const;
    virtual std::string getName() const;
    virtual Ability* clone() const = 0;

};
#endif