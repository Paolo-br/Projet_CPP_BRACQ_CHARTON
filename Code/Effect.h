#ifndef __EFFECT_H
#define __EFFECT_H


#include <iostream>

class Turn;
class Player; 

class Effect {
    int m_value; 

public:

    virtual ~Effect() = default;
    int getValue() const;
    void setValue(int value);
    
    virtual void apply(Player& player, Turn& turn) = 0;
    virtual Effect* clone() const = 0;
};

#endif
