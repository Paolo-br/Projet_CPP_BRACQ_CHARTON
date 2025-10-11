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
    m_cards.clear();
    std::cout << "Défausse vidée" << std::endl;
}

Deck DiscardPile::reshuffleIntoDeck() {
    Deck newDeck(m_cards);
    newDeck.shuffle();
    m_cards.clear();
    
    std::cout << "Défausse remélangée en deck de " << newDeck.size() << " cartes" << std::endl;
    return newDeck;
}
