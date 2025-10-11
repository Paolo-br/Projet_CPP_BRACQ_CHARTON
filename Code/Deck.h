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
    std::vector<Card*> m_cards;

    public:
     // RÈGLE DES 0 - Pas besoin de destructeur/copie personnalisés
    Deck();
    Deck(const std::vector<Card*>& cards);
    ~Deck();
    void shuffle();
    std::vector<Card*> getCards();
    Card* draw();
    void addCard(Card* card); //Est fait lors de l'achat d'une carte
    bool isEmpty() const;
    size_t size() const;
    void clear();
    bool removeCard(Card* card);
};
#endif