#include "Deck.h"
#include <iostream>
#include "../CardsType/Card.h"
#include <list>
#include <algorithm>  
#include <random> 

Deck::Deck() {}
Deck::Deck(const std::vector<Card*>& cards) : m_cards(cards) { 
    std::cout << "Deck créé avec " << cards.size() << " cartes" << std::endl;
}

Deck::~Deck() {
    std::cout << "Destructeur Deck (" << m_cards.size() << " cartes)" << std::endl;
    // Supprimer toutes les cartes restantes détenues par le deck
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
}

void Deck::shuffle() {
    if (m_cards.empty()) {
        std::cout << "Avertissement: tentative de mélanger un deck vide" << std::endl;
        return;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_cards.begin(), m_cards.end(), g);
    
    std::cout << "Deck mélangé (" << m_cards.size() << " cartes)" << std::endl;
}

std::vector<Card*> Deck::getCards() {
    return m_cards;
}

Card* Deck::draw() {
    if (m_cards.empty()) {
        throw std::out_of_range("Le deck est vide, impossible de piocher une carte.");
    }
    
    Card* topCard = m_cards.front();
    m_cards.erase(m_cards.begin()); 
    
    std::cout << "Carte piochée: " << topCard->getName() 
              << " (reste " << m_cards.size() << " cartes)" << std::endl;
    
    return topCard;
}

void Deck::addCard(Card* card) {
    m_cards.push_back(card);
}

void Deck::addCardOnTop(Card* card) {
    m_cards.insert(m_cards.begin(), card); // Insère au début (dessus du deck)
    std::cout << "Carte ajoutée sur le dessus du deck: " << card->getName() << std::endl;
}

bool Deck::isEmpty() const {
    return m_cards.empty();
}

size_t Deck::size() const {
    return m_cards.size();
}

void Deck::clear() {
    // Supprimer les pointeurs détenus puis vider
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
    std::cout << "Deck vidé" << std::endl;
}

bool Deck::removeCard(Card* card) {
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        if (*it == card) { 
            m_cards.erase(it);
            std::cout << "Carte retirée du deck: " << card->getName() << std::endl;
            return true;
        }
    }
    return false;
}


