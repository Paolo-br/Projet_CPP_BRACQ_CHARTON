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

    // RÈGLE DES 5 OBLIGATOIRE à cause des raw pointers
    ~ActionCard() override;
    ActionCard(const ActionCard& other);
    ActionCard& operator=(const ActionCard& other);
    ActionCard(ActionCard&& other) noexcept;
    ActionCard& operator=(ActionCard&& other) noexcept;


    std::vector<Effect*> getEffects() const { return m_effects; }
    std::string getName() override;

    // Implémentation des méthodes virtuelles pures
    std::string getType() const override { return "Action"; }
    void executeEffects(Player& player, Turn& turn) override;
    void play(Player& player, Player& opponent) override;
};
#endif