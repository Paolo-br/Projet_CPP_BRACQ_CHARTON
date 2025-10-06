#ifndef __ACTIONCARD_H
#define __ACTIONCARD_H
#include "Card.h"
#include "Effect.h"
#include <vector>

class ActionCard : public Card {
private:
    std::vector<Effect*> m_effects;

public:
    ActionCard(const std::string& name, int cost, Faction faction, const std::string& type,
               const std::vector<Effect*>& effects);
    ~ActionCard();

    void play(Player& owner, Player& opponent) override;
};

#endif
 