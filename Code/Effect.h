#ifndef __EFFECT_H
#define __EFFECT_H

#include <iostream>

class Player; 

class Effect {
protected:
    int m_value; 

public:

    Effect(int value);
    virtual ~Effect();


    int getValue() const;
    void setValue(int value);


    virtual void apply(Player& target, Player& owner) = 0;
};

#endif
