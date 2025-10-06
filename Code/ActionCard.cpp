#include "ActionCard.h"
#include <iostream>

ActionCard::ActionCard(const std::string& name, int cost, Faction faction, const std::string& type,
                       const std::vector<Effect*>& effects)
    : Card(name, cost, faction, type), m_effects(effects) {}

ActionCard::~ActionCard() {
    for (auto e : m_effects) delete e; // cleanup si ActionCard possède les effets
}

void ActionCard::play(Player& owner, Player& opponent) {
    for (auto e : m_effects) {
        e->apply(opponent, owner); // applique l'effet
    }
}
