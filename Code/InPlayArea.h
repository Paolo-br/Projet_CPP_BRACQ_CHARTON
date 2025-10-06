#ifndef __INPLAYAREA_H
#define __INPLAYAREA_H

#include <list> 
#include <iostream>
#include "Card.h"
class InPlayArea {
    std::list<Card> m_cards;
    public:
    InPlayArea(std::list<Card> cards);
    ~InPlayArea();
    void add(Card card);
    void clear();
};

#endif