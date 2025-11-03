#ifndef __DISCARDPILE_H
#define __DISCARDPILE_H

#include <iostream>
#include <list>
#include <vector>
#include "../CardsType/Card.h"

class Deck;

class DiscardPile {
    std::vector<Card*> m_cards;

    public:
    DiscardPile();
    DiscardPile(std::vector<Card*> cards);
    ~DiscardPile();
    
    // RÈGLE DES 5
    DiscardPile(const DiscardPile& other);              // Constructeur de copie
    DiscardPile& operator=(const DiscardPile& other);   // Opérateur d'affectation copie
    DiscardPile(DiscardPile&& other) noexcept;          // Constructeur de déplacement
    DiscardPile& operator=(DiscardPile&& other) noexcept; // Opérateur d'affectation déplacement
    void add(Card* card);
    void clear();
    std::vector<Card*> getCards() { return m_cards; }
    const std::vector<Card*>& getCards() const { return m_cards; } // Version const
    bool removeCard(Card* card); // Retirer une carte spécifique
    bool isEmpty() const;
    size_t size() const;
    Deck reshuffleIntoDeck();
};


#endif