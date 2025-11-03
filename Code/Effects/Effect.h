#ifndef __EFFECT_H
#define __EFFECT_H


#include <iostream>
#include "../ResourceType.h"
#include "../ConditionType.h"

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
    virtual Effect* getOption1() const=0;
    virtual Effect* getOption2() const=0;
    virtual const ResourceType* getResourceType() const=0;
    virtual const ConditionType* getConditionType() const=0;
    virtual bool getIsOptional() const=0;
    virtual const std::string* getCardTypeFilter() const=0;
    virtual int getCount() const=0;
    virtual int getMaxCount() const=0;
    virtual Effect* getBonusEffect() const=0;
};

#endif
