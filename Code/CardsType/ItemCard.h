#ifndef __ITEMCARD_H
#define __ITEMCARD_H
#include "Card.h"
#include "../Effects/Effect.h"
#include "../Abilities/Ability.h"
#include "../Utils.h"
#include <vector>

class ItemCard : public Card {
private:
    std::vector<Effect*> m_effects;
    std::vector<Ability*> m_abilities;   // Pour Sacrifice abilities principalement

public:

    ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
                   const std::vector<Effect*>& effects,
                   const std::vector<Ability*>& abilities = {});


    // RÈGLE DES 5 - OBLIGATOIRE à cause des raw pointers

    ~ItemCard() override;
    ItemCard(const ItemCard& other);                    // Constructeur copie
    ItemCard& operator=(const ItemCard& other);         // Opérateur affectation copie  
    ItemCard(ItemCard&& other) noexcept;                // Constructeur déplacement
    ItemCard& operator=(ItemCard&& other) noexcept;     // Opérateur affectation déplacement


    // Implémentation des méthodes virtuelles pures
    std::string getName() const override;
    void executeEffects(Player& player, Turn& turn) override;
    std::tuple<int,int> display(int row,int col) override;

    // Autres méthodes
    std::vector<Effect*> getEffect() const override { return m_effects; }
    std::vector<Ability*> getAbilities() const override { return m_abilities; }
    void play(Player& owner, Player& opponent) override;
    
    // Vérification des abilities
    bool hasAllyAbility() const override;
    bool hasSacrificeAbility() const override;
    Card* clone() const override { return new ItemCard(*this); }
};
#endif

