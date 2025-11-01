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
     // RÈGLE DES 0 - Pas besoin de destructeur/copie personnalisés
    DiscardPile();
    DiscardPile(std::vector<Card*> cards);
    ~DiscardPile();
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