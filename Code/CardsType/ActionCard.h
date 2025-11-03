#ifndef __ACTIONCARD_H
#define __ACTIONCARD_H
#include "Card.h"
#include "../Effects/Effect.h"
#include "../Abilities/Ability.h"
#include <vector>

class ActionCard : public Card {
private:
    std::vector<Effect*> m_effects;      // Effets principaux
    std::vector<Ability*> m_abilities;   // Ally, Sacrifice abilities

public:
    ActionCard(const std::string& name, int cost, Faction faction, const std::string& type,
               const std::vector<Effect*>& effects,
               const std::vector<Ability*>& abilities = {});

    // RÈGLE DES 5 
    ~ActionCard() override;
    ActionCard(const ActionCard& other);
    ActionCard& operator=(const ActionCard& other);
    ActionCard(ActionCard&& other) noexcept;
    ActionCard& operator=(ActionCard&& other) noexcept;


    std::vector<Effect*> getEffects() const { return m_effects; }
    std::vector<Ability*> getAbilities() const override { return m_abilities; }
    std::string getName() const override;

    // Implémentation des méthodes virtuelles pures
    std::string getType() const override { return "Action"; }
    void executeEffects(Player& player, Turn& turn) override;
    void play(Player& player, Player& opponent) override;
    std::tuple<int,int> display(int row,int col) override;
    std::vector<Effect*> getEffect() const override { return m_effects; }
    
    // Vérification des abilities
    bool hasAllyAbility() const override;
    bool hasSacrificeAbility() const override;
    Card* clone() const override { return new ActionCard(*this); }
};
#endif