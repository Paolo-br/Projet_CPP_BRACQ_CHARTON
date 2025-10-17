#ifndef __HAND_H
#define __HAND_H
#include <iostream>
#include <list>
#include <vector>
#include "Card.h"

class Hand {
    std::vector<Card*> m_cards;
    public:
     // RÈGLE DES 0 - Pas besoin de destructeur/copie personnalisés
    Hand();
    Hand(std::vector<Card*> cards);
    ~Hand();
    void add(Card* card);
    Card* draw();
    bool remove(Card* card);
    bool isEmpty() const;
    size_t size() const;
    void clear();
    std::vector<Card*> getCards() const;

    Card* getCardAt(int index);
    const Card* getCardAt(int index) const;
    Card* removeCardAt(int index);
    bool contains(Card* card);
};

#endif