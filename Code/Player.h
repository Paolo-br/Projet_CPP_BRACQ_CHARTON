#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Deck.h"
#include "Card.h"

class Player{
    std::string m_name;
    int m_health;
    int m_gold;
    Deck m_deck;
    std::list<Card> m_hand;
    std::list<Card> m_discardPile;
    public:
    Player(std::string name, int health,int gold, Deck deck, std::list<Card> hand, std::list<Card> discardPile);
    ~Player();
    std::string getName();
    int getHealth();
    Deck getDeck();
    std::list<Card> getDiscardPile();
    void setName(std::string name);
    void setHealth(int health);
    void addCardDeck(Card card);
    void discard(Card card);
    void drawCard(Card card);
    void sacrifice(Card card);
    void buyCard(Card card);
};
#endif