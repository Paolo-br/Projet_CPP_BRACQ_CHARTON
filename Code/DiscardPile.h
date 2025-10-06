#ifndef __DISCARDPILE_H
#define __DISCARDPILE_H

#include <iostream>
#include <list>
#include "Card.h"
class DiscardPile {
    std::list<Card> m_cards;
    public:
    DiscardPile(std::list<Card> cards);
    ~DiscardPile();
    void add(Card card);
    void clear();
    std::list<Card> getCards() { return m_cards; }
};


#endif