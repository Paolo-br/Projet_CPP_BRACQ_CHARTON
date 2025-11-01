#ifndef __CONDITIONALEFFECT_H
#define __CONDITIONALEFFECT_H

#include "Effect.h"
#include "../Turn.h"
#include "../Faction.h"
#include "../ResourceType.h"
#include "../ConditionType.h"
#include <string>


class ConditionalEffect : public Effect {
private:
    ResourceType m_resourceType;    
    ConditionType m_conditionType;  
    Faction m_faction;              
    bool m_includeSelf;             

public:
    // Constructeur 
    ConditionalEffect(ResourceType resType, int valuePerUnit, ConditionType condType, 
                     Faction faction = Faction::None, bool includeSelf = true);
    
    void apply(Player& player, Turn& turn) override;
    Effect* clone() const override;
    std::string getName() const override;
    
   
    int countCondition(Player& player) const;
    
    // Getters
    const ResourceType* getResourceType() const override { return &m_resourceType; }
    const ConditionType* getConditionType() const { return &m_conditionType; }
    Faction getFaction() const { return m_faction; }
    bool getIncludeSelf() const { return m_includeSelf; }
    
    Effect* getOption1() const override;
    Effect* getOption2() const override;
    bool getIsOptional() const override;
    const std::string* getCardTypeFilter() const override;
    int getCount() const override;
    int getMaxCount() const override;
    Effect* getBonusEffect() const override;
};

#endif
