#ifndef __ITEMCARD_H
#define __ITEMCARD_H
#include "Card.h"
#include "Effect.h"
#include <vector>

class ItemCard : public Card {
private:
    std::string m_type;
    std::vector<Effect*> m_effects;
    

public:

    ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
                   const std::vector<Effect*>& effects);


    // RÈGLE DES 5 - OBLIGATOIRE à cause des raw pointers

    ~ItemCard() override;
    ItemCard(const ItemCard& other);                    // Constructeur copie
    ItemCard& operator=(const ItemCard& other);         // Opérateur affectation copie  
    ItemCard(ItemCard&& other) noexcept;                // Constructeur déplacement
    ItemCard& operator=(ItemCard&& other) noexcept;     // Opérateur affectation déplacement


    // Implémentation des méthodes virtuelles pures
    std::string getType() const override { return m_type; }
    std::string getName() override;
    void executeEffects(Player& player, Turn& turn) override;

    // Autres méthodes
    std::vector<Effect*> getEffects() const { return m_effects; }
    void play(Player& owner, Player& opponent) override;
};
#endif
