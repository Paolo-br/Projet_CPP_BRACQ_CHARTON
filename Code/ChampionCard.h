#ifndef __CHAMPIONCARD_H
#define __CHAMPIONCARD_H
#include <string>
#include <list>
#include "Faction.h"
#include "Player.h"
#include "Card.h"
#include "Ability.h"

class ChampionCard : public Card{
	int m_defense;
    bool m_isGuard;
    bool m_isTapped;
    std::list<Ability*> m_abilities;

    public:

    ChampionCard(std::string name, int cost, Faction faction, std::string type, int defense, bool isGuard, bool isTapped, std::list<Ability*> abilities);
    ~ChampionCard();
    void defend();
    void activate();
    void sacrifice();
    int getDefense();
    bool getIsGuard();
    bool getIsTapped();
    std::list<Ability*> getAbilities();
    void setDefense(int defense);
    void setIsGuard(bool isGuard);
    void setIsTapped(bool isTapped);
    void setAbilities(std::list<Ability*> abilities);
    void play(Player& owner, Player& opponent) override;

};
#endif