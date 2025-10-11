#include "ItemCard.h"
#include "Player.h"
#include "Turn.h"

#include <iostream>

ItemCard::ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
                   const std::vector<Effect*>& effects)
    : Card(name, cost, faction, type), m_effects(effects) {}


// 1. Destructeur - Nettoie tous les effets
ItemCard::~ItemCard() {
    std::cout << "Destructeur ItemCard: " << this->getName() << std::endl;
    for (Effect* effect : m_effects) {
        delete effect;
    }
    m_effects.clear();
}

// 2. Constructeur de copie (COPIE PROFONDE)
ItemCard::ItemCard(const ItemCard& other)
    : Card(other), m_type(other.m_type) {
    for (auto effect : other.m_effects) {
        m_effects.push_back(effect->clone());
    }
}

// 3. Opérateur d'affectation copie
ItemCard& ItemCard::operator=(const ItemCard& other) {
    if (this != &other) {
        Card::operator=(other);
        m_type = other.m_type;
        for (auto effect : m_effects) {
            delete effect;
        }
        m_effects.clear();
        for (auto effect : other.m_effects) {
            m_effects.push_back(effect->clone());
        }
    }
    return *this;
}


// 4. Constructeur de déplacement
ItemCard::ItemCard(ItemCard&& other) noexcept
    : Card(std::move(other)), m_type(std::move(other.m_type)), m_effects(std::move(other.m_effects)) {
    other.m_effects.clear();
}


// 5. Opérateur d'affectation déplacement
ItemCard& ItemCard::operator=(ItemCard&& other) noexcept {
    if (this != &other) {
        Card::operator=(std::move(other));
        m_type = std::move(other.m_type);
        m_effects = std::move(other.m_effects);
        other.m_effects.clear();
    }
    return *this;
}

void ItemCard::executeEffects(Player& player, Turn& turn) {
    for (auto effect : m_effects) {
        effect->apply(player, turn);
    }
}


void ItemCard::play(Player& owner, Player& opponent) {
    std::cout<<"Joueur "<<owner.getName()<<" joue sur"<<opponent.getName()<<std::endl;

}

std::string ItemCard::getName() {
    return Card::getName();  
}