#ifndef __CHAMPIONCARD_H
#define __CHAMPIONCARD_H
#include "Card.h"
#include "Ability.h"

class ChampionCard : public Card{
	int m_defense;
    bool m_isGuard;
    bool m_isTapped;
    std::list<Ability> m_abilities;

    public:

    ChampionCard(std::string name, int cost, Faction faction, std::string type, int defense, bool isGuard, bool isTapped, std::list<Ability> abilities);
    ~ChampionCard() {};
    void defend();
    void activate();
    void sacrifice();
};
#endif