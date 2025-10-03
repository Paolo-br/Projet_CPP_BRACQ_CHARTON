#ifndef __ABILITY_H
#define __ABILITY_H

class Player;

class Ability {
    public:
    Ability();
    virtual ~Ability();
    virtual void trigger(Player& Owner, Player& opponent)=0;

};
#endif