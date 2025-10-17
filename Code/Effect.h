#ifndef __EFFECT_H
#define __EFFECT_H


#include <iostream>

class Turn;
class Player; 

class Effect {
    int m_value; 

public:
    Effect(int value);

    virtual ~Effect() = default;
    int getValue() const;
    void setValue(int value);
    
    virtual void apply(Player& player, Turn& turn);
    virtual std::string getName() const;
    virtual Effect* clone() const = 0;
};

#endif
