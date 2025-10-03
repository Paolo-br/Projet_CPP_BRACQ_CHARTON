#ifndef __DECK_H
#define __DECK_H
#include <iostream>
#include <random>

#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <random>
#include "Card.h"


class Deck {
    std::list<Card> m_cards;
    public:
    Deck() = default;
    Deck(const std::list<Card>& cards);
    ~Deck();
    void shuffle(std::list<Card>& lst);
    std::list<Card> getCards();
    Card draw();
    void addCard(Card& card); //Est fait lors de l'achat d'une carte
};
#endif