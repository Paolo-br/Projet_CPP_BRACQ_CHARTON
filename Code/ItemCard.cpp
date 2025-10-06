#include "ItemCard.h"

ItemCard::ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
                   const std::vector<Effect*>& effects)
    : Card(name, cost, faction, type), m_effects(effects) {}

ItemCard::~ItemCard() {
    for (auto e : m_effects) delete e;
}

void ItemCard::play(Player& owner, Player& opponent) {
    for (auto e : m_effects)
        e->apply(opponent, owner);
}
