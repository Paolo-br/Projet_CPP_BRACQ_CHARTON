#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include <string>
#include <list>
#include "Deck.h"
#include "Card.h"
#include"Hand.h"
#include "DiscardPile.h"

class Player {
private:
    std::string m_name;
    int m_health;
    int m_gold;
    Deck m_deck;
    Hand m_hand;
    DiscardPile m_discardPile;

public:
    Player(const std::string& name, int health, int gold, const Deck& deck,
           const std::list<Card>& hand, const std::list<Card>& discardPile);
    ~Player();

    std::string getName() const;
    int getHealth() const;
    int getGold() const;
    Deck& getDeck();
    DiscardPile& getDiscardPile();
    Hand& getHand();


    void setName(const std::string& name);
    void setHealth(int health);
    void setGold(int gold);

    void addCardDeck(Card& card);
    void addCardDiscard(Card& card);
    void discard(const Card& card);
    void drawCard(const Card& card);
    void sacrifice(const Card& card);
    void buyCard(Card& card);
};

#endif
