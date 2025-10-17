#include "ActionCard.h"
#include "Turn.h"
#include "Player.h"
#include "AllyAbility.h"
#include "SacrificeAbility.h"
#include <iostream>

// Constructeur
ActionCard::ActionCard(const std::string& name, int cost, Faction faction, const std::string& type,
                       const std::vector<Effect*>& effects,
                       const std::vector<Ability*>& abilities)
    : Card(name, cost, faction, type), m_effects(effects), m_abilities(abilities) {
    std::cout << "ActionCard créée: " << name << std::endl;
}

// 1. Destructeur - Nettoie tous les effets et abilities
ActionCard::~ActionCard() {
    std::cout << "Destructeur ActionCard: "<< std::endl;
    for (Effect* effect : m_effects) {
        delete effect;
    }
    m_effects.clear();
    
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    m_abilities.clear();
}

// 2. Constructeur de copie (COPIE PROFONDE)
ActionCard::ActionCard(const ActionCard& other)
    : Card(other) { // Appel au constructeur copie de Card
    std::cout << "Constructeur copie ActionCard"<< std::endl;
    
    // COPIE PROFONDE des effets
    for (Effect* effect : other.m_effects) {
        m_effects.push_back(effect); 
    }
    
    // COPIE PROFONDE des abilities
    for (Ability* ability : other.m_abilities) {
        m_abilities.push_back(ability);
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
        
        // Nettoyer les abilities existantes
        for (Ability* ability : m_abilities) {
            delete ability;
        }
        m_abilities.clear();
        
        // COPIE PROFONDE des effets
        for (Effect* effect : other.m_effects) {
            m_effects.push_back(effect);
        }
        
        // COPIE PROFONDE des abilities
        for (Ability* ability : other.m_abilities) {
            m_abilities.push_back(ability);
        }
    }
    return *this;
}

// 4. Constructeur de déplacement
ActionCard::ActionCard(ActionCard&& other) noexcept
    : Card(std::move(other)), // Appel au constructeur déplacement de Card
      m_effects(std::move(other.m_effects)),
      m_abilities(std::move(other.m_abilities)) {
    std::cout << "Constructeur déplacement ActionCard: "<< std::endl;
    
    // Vider les vecteurs de l'autre objet
    other.m_effects.clear();
    other.m_abilities.clear();
}

// 5. Opérateur d'affectation déplacement
ActionCard& ActionCard::operator=(ActionCard&& other) noexcept {
    std::cout << "Opérateur affectation déplacement ActionCard: " << std::endl;
    
    if (this != &other) {
        // Appel à l'opérateur d'affectation déplacement de Card
        Card::operator=(std::move(other));
        
        // Nettoyer les effets et abilities existants
        for (Effect* effect : m_effects) {
            delete effect;
        }
        for (Ability* ability : m_abilities) {
            delete ability;
        }
        
        // Transférer les vecteurs
        m_effects = std::move(other.m_effects);
        m_abilities = std::move(other.m_abilities);
        
        other.m_effects.clear();
        other.m_abilities.clear();
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

std::string ActionCard::getName() const {
    return Card::getName();  
}

bool ActionCard::hasAllyAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<AllyAbility*>(ability)) {
            return true;
        }
    }
    return false;
}

bool ActionCard::hasSacrificeAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<SacrificeAbility*>(ability)) {
            return true;
        }
    }
    return false;
}