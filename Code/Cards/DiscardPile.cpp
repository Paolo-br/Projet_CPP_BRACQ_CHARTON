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
    Deck newDeck(m_cards);
    newDeck.shuffle();
    m_cards.clear();
    
    std::cout << "Défausse remélangée en deck de " << newDeck.size() << " cartes" << std::endl;
    return newDeck;
}
