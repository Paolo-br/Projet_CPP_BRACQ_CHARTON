#ifndef __CONDITIONALEFFECT_H
#define __CONDITIONALEFFECT_H

#include "Effect.h"
#include "Turn.h"
#include "Faction.h"
#include <string>

// Types de ressources affectées
enum class ResourceType {
    Gold,       
    Combat,     
    Health      
};

// Types de conditions pour compter
enum class ConditionType {
    ChampionCount,          
    GuardCount,             
    FactionCardCount,       
    OtherChampionCount,     
    OtherGuardCount         
};

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
    ResourceType getResourceType() const { return m_resourceType; }
    ConditionType getConditionType() const { return m_conditionType; }
    Faction getFaction() const { return m_faction; }
    bool getIncludeSelf() const { return m_includeSelf; }
};

#endif
