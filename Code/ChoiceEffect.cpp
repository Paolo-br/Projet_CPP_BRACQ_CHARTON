#include "ChoiceEffect.h"
#include "Player.h"
#include "Turn.h"
#include <iostream>

ChoiceEffect::ChoiceEffect(Effect* option1, const std::string& desc1,
                           Effect* option2, const std::string& desc2)
    : Effect(0), m_option1(option1), m_option2(option2), 
      m_description1(desc1), m_description2(desc2) {
    std::cout << "ChoiceEffect créé" << std::endl;
}

ChoiceEffect::~ChoiceEffect() {
    std::cout << "Destructeur ChoiceEffect" << std::endl;
    delete m_option1;
    delete m_option2;
}

// Constructeur de copie
ChoiceEffect::ChoiceEffect(const ChoiceEffect& other)
    : Effect(other), 
      m_option1(other.m_option1 ? other.m_option1->clone() : nullptr),
      m_option2(other.m_option2 ? other.m_option2->clone() : nullptr),
      m_description1(other.m_description1),
      m_description2(other.m_description2) {
}

// Opérateur d'affectation copie
ChoiceEffect& ChoiceEffect::operator=(const ChoiceEffect& other) {
    if (this != &other) {
        Effect::operator=(other);
        
        delete m_option1;
        delete m_option2;
        
        m_option1 = other.m_option1 ? other.m_option1->clone() : nullptr;
        m_option2 = other.m_option2 ? other.m_option2->clone() : nullptr;
        m_description1 = other.m_description1;
        m_description2 = other.m_description2;
    }
    return *this;
}

// Constructeur de déplacement
ChoiceEffect::ChoiceEffect(ChoiceEffect&& other) noexcept
    : Effect(std::move(other)),
      m_option1(other.m_option1),
      m_option2(other.m_option2),
      m_description1(std::move(other.m_description1)),
      m_description2(std::move(other.m_description2)) {
    other.m_option1 = nullptr;
    other.m_option2 = nullptr;
}

// Opérateur d'affectation déplacement
ChoiceEffect& ChoiceEffect::operator=(ChoiceEffect&& other) noexcept {
    if (this != &other) {
        Effect::operator=(std::move(other));
        
        delete m_option1;
        delete m_option2;
        
        m_option1 = other.m_option1;
        m_option2 = other.m_option2;
        m_description1 = std::move(other.m_description1);
        m_description2 = std::move(other.m_description2);
        
        other.m_option1 = nullptr;
        other.m_option2 = nullptr;
    }
    return *this;
}

void ChoiceEffect::apply(Player& player, Turn& turn) {
    std::cout << "\n=== CHOIX ===" << std::endl;
    std::cout << "Joueur: " << player.getName() << std::endl;
    std::cout << "Choisissez une option:" << std::endl;
    std::cout << "1. " << m_description1 << std::endl;
    std::cout << "2. " << m_description2 << std::endl;
    
    int choice;
    std::cout << "Votre choix (1 ou 2): ";
    std::cin >> choice;
    
    while (choice != 1 && choice != 2) {
        std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
        std::cin >> choice;
    }
    
    if (choice == 1) {
        std::cout << "Vous avez choisi: " << m_description1 << std::endl;
        m_option1->apply(player, turn);
    } else {
        std::cout << "Vous avez choisi: " << m_description2 << std::endl;
        m_option2->apply(player, turn);
    }
}

std::string ChoiceEffect::getName() const {
    return "ChoiceEffect";
}

ChoiceEffect* ChoiceEffect::clone() const {
    return new ChoiceEffect(*this);
}
