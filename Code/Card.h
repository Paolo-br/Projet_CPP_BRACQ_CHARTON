#ifndef __CARD_H
#define __CARD_H
#include "Faction.h"
#include "Player.h"

class Card {
	std::string m_name;
	int m_cost;
    Faction m_faction;
    std::string m_type;

	public:
	Card(std::string name, int cost, Faction faction, std::string type){}
	~Card() {}
	virtual std::string getName();
	virtual int getCost();
    virtual Faction getFaction();
    virtual std::string getType();
    virtual void setName();
	virtual void setCost();
    virtual void setFaction();
    virtual void setType();
    virtual void play(Player owner, Player opponent); // à réfléchir si on initialise opponent à null	
};
#endif