#include "DiscardPile.h"
#include "Deck.h"
#include <iostream>

DiscardPile::DiscardPile(std::vector<Card*> cards):m_cards(cards){
    std::cout << "Constructeur DiscardPile" << std::endl;
}

DiscardPile::DiscardPile() {
    std::cout << "Défausse créée" << std::endl;
}

DiscardPile::~DiscardPile() {
    std::cout << "Destructeur Défausse (" << m_cards.size() << " cartes)" << std::endl;
    // Supprimer les cartes restantes détenues par la défausse
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
}

// Constructeur de copie (copie superficielle des pointeurs)
DiscardPile::DiscardPile(const DiscardPile& other) 
    : m_cards(other.m_cards) {
    std::cout << "Constructeur copie DiscardPile (" << m_cards.size() << " cartes)" << std::endl;
}

// Opérateur d'affectation copie
DiscardPile& DiscardPile::operator=(const DiscardPile& other) {
    if (this != &other) {
        // Nettoyer les cartes existantes
        for (auto card : m_cards) {
            delete card;
        }
        m_cards.clear();
        
        // Copie superficielle des pointeurs
        m_cards = other.m_cards;
    }
    std::cout << "Opérateur affectation copie DiscardPile" << std::endl;
    return *this;
}

// Constructeur de déplacement
DiscardPile::DiscardPile(DiscardPile&& other) noexcept 
    : m_cards(std::move(other.m_cards)) {
    // Le vecteur de l'autre est maintenant vide (move du vector)
    std::cout << "Constructeur déplacement DiscardPile (" << m_cards.size() << " cartes)" << std::endl;
}

// Opérateur d'affectation déplacement
DiscardPile& DiscardPile::operator=(DiscardPile&& other) noexcept {
    if (this != &other) {
        // Nettoyer nos cartes
        for (auto card : m_cards) {
            delete card;
        }
        m_cards.clear();
        
        // Prendre les cartes de l'autre
        m_cards = std::move(other.m_cards);
    }
    std::cout << "Opérateur affectation déplacement DiscardPile" << std::endl;
    return *this;
}
void DiscardPile::add(Card* card){
    m_cards.push_back(card);
}
bool DiscardPile::isEmpty() const {
    return m_cards.empty();
}

size_t DiscardPile::size() const {
    return m_cards.size();
}

void DiscardPile::clear() {
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
    std::cout << "Défausse vidée" << std::endl;
}

bool DiscardPile::removeCard(Card* card) {
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        if (*it == card) {
            m_cards.erase(it);
            std::cout << "Carte retirée de la défausse: " << card->getName() << std::endl;
            return true;
        }
    }
    return false;
}

Deck DiscardPile::reshuffleIntoDeck() {
    Deck newDeck(std::move(m_cards));
    newDeck.shuffle();
    m_cards.clear();

    std::cout << "Défausse remélangée en deck de " << newDeck.size() << " cartes" << std::endl;
    return newDeck;
}
