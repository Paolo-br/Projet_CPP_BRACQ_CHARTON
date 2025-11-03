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
#include "../CardsType/Card.h"


class Deck {
    std::vector<Card*> m_cards;

    public:
     // RÈGLE DES 0 - Pas besoin de destructeur/copie personnalisés
    Deck();
    Deck(const std::vector<Card*>& cards);
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);
    Deck(std::vector<Card*>&& cards);
    Deck(Deck&& other) noexcept;
    Deck& operator=(Deck&& other) noexcept;
    ~Deck();
    void shuffle();
    std::vector<Card*> getCards();
    Card* draw();
    void addCard(Card* card); //Est fait lors de l'achat d'une carte
    void addCardOnTop(Card* card); // Ajoute une carte sur le dessus du deck
    bool isEmpty() const;
    size_t size() const;
    void clear();
    bool removeCard(Card* card);
};
#endif