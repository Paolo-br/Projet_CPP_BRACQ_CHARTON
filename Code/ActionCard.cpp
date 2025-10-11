#include "ActionCard.h"
#include "Turn.h"
#include <iostream>

// Constructeur
ActionCard::ActionCard(const std::string& name, int cost, Faction faction, const std::string& type,
                       const std::vector<Effect*>& effects)
    : Card(name, cost, faction, type), m_effects(effects) {
    std::cout << "ActionCard créée: " << name << std::endl;
}

// 1. Destructeur - Nettoie tous les effets
ActionCard::~ActionCard() {
    std::cout << "Destructeur ActionCard: "<< std::endl;
    for (Effect* effect : m_effects) {
        delete effect;
    }
    m_effects.clear();
}

// 2. Constructeur de copie (COPIE PROFONDE)
ActionCard::ActionCard(const ActionCard& other)
    : Card(other) { // Appel au constructeur copie de Card
    std::cout << "Constructeur copie ActionCard"<< std::endl;
    
    // COPIE PROFONDE des effets
    for (Effect* effect : other.m_effects) {
        // Pour l'instant, on fait une copie simple (à améliorer)
        m_effects.push_back(effect); 
    }
}

// 3. Opérateur d'affectation copie
ActionCard& ActionCard::operator=(const ActionCard& other) {
    std::cout << "Opérateur affectation copie ActionCard:" << std::endl;
    
    if (this != &other) {
        // Appel à l'opérateur d'affectation de Card
        Card::operator=(other);
        
        // Nettoyer les effets existants
        for (Effect* effect : m_effects) {
            delete effect;
        }
        m_effects.clear();
        
        // COPIE PROFONDE des effets
        for (Effect* effect : other.m_effects) {
            m_effects.push_back(effect);
        }
    }
    return *this;
}

// 4. Constructeur de déplacement
ActionCard::ActionCard(ActionCard&& other) noexcept
    : Card(std::move(other)), // Appel au constructeur déplacement de Card
      m_effects(std::move(other.m_effects)) {
    std::cout << "Constructeur déplacement ActionCard: "<< std::endl;
    
    // Vider les effets de l'autre objet
    other.m_effects.clear();
}

// 5. Opérateur d'affectation déplacement
ActionCard& ActionCard::operator=(ActionCard&& other) noexcept {
    std::cout << "Opérateur affectation déplacement ActionCard: " << std::endl;
    
    if (this != &other) {
        // Appel à l'opérateur d'affectation déplacement de Card
        Card::operator=(std::move(other));
        
        // Nettoyer les effets existants
        for (Effect* effect : m_effects) {
            delete effect;
        }
        
        // Transférer les effets
        m_effects = std::move(other.m_effects);
        other.m_effects.clear();
    }
    return *this;
}

void ActionCard::play(Player& player, Player& opponent) {
        std::cout<<"Joueur "<<player.getName()<<" joue sur"<<opponent.getName()<<std::endl;

}

void ActionCard::executeEffects(Player& player, Turn& turn) {
    std::cout << "Effets de " << this->getName() << ":" << std::endl;
    for (auto& effect : m_effects) {
        effect->apply(player, turn);
    }
}

std::string ActionCard::getName() {
    return Card::getName();  
}