#ifndef __CARD_H
#define __CARD_H
#include <string>
#include "Faction.h"

class Turn; // déclaration anticipée

class Player; // déclaration anticipée

class Card {
	std::string m_name;
	int m_cost;
    Faction m_faction;
    std::string m_type;

	public:
	Card(const std::string name, int cost, Faction faction,const std::string type);
	virtual ~Card()=default; // Règle des 0 - pas de gestion manuelle
    


	virtual std::string getName() const;
	virtual int getCost() const;
    virtual Faction getFaction() const;
    virtual std::string getType() const;
    virtual void setName(std::string name);
	virtual void setCost(int cost);
    virtual void setFaction(Faction faction);
    virtual void setType(std::string type);
    virtual void play(Player& owner, Player& opponent); // à réfléchir si on initialise opponent à null	
    bool operator==(const Card& other) const;
    
    virtual void executeEffects(Player& player, Turn& turn) = 0;
    virtual bool hasAllyAbility() const { return false; }
    virtual bool hasSacrificeAbility() const { return false; }
   
};
#endif