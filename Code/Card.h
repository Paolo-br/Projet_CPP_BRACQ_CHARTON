#ifndef __CARD_H
#define __CARD_H
#include <string>
#include "Faction.h"

class Player; // déclaration anticipée

class Card {
	std::string m_name;
	int m_cost;
    Faction m_faction;
    std::string m_type;

	public:
	Card(std::string name, int cost, Faction faction, std::string type);
	virtual ~Card();
	virtual std::string getName();
	virtual int getCost();
    virtual Faction getFaction();
    virtual std::string getType();
    virtual void setName(std::string name);
	virtual void setCost(int cost);
    virtual void setFaction(Faction faction);
    virtual void setType(std::string type);
    virtual void play(Player& owner, Player& opponent); // à réfléchir si on initialise opponent à null	
    bool operator==(const Card& other) const;
};
#endif