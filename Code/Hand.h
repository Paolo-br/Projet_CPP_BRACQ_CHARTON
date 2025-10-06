#ifndef __HAND_H
#define __HAND_H
#include <iostream>
#include <list>
#include "Card.h"

class Hand {
    std::list<Card> m_cards;
    public:
    Hand(std::list<Card> cards);
    ~Hand();
    void add(Card card);
    void remove(Card card);
    void show();
};

#endif