#ifndef __HAND_H
#define __HAND_H
#include <iostream>
#include <list>
#include <vector>
#include "../CardsType/Card.h"

class Hand {
    std::vector<Card*> m_cards;
    public:
    Hand();
    Hand(std::vector<Card*> cards);
    ~Hand();
    
    // RÈGLE DES 5
    Hand(const Hand& other);              // Constructeur de copie
    Hand& operator=(const Hand& other);   // Opérateur d'affectation copie
    Hand(Hand&& other) noexcept;          // Constructeur de déplacement
    Hand& operator=(Hand&& other) noexcept; // Opérateur d'affectation déplacement
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