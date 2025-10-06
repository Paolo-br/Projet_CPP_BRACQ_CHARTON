#ifndef __ITEMCARD_H
#define __ITEMCARD_H
#include "Card.h"
#include "Effect.h"
#include <vector>

class ItemCard : public Card {
private:
    std::vector<Effect*> m_effects;

public:
    ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
             const std::vector<Effect*>& effects);
    ~ItemCard();

    void play(Player& owner, Player& opponent) override;
};
#endif
