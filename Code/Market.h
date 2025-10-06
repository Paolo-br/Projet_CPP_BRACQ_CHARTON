#ifndef __MARKET_H
#define __MARKET_H
#include <ostream>
#include <list>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
class Market{
    std::list<Card> m_visibleCards;
    Deck m_marketDeck;
    public:
    Market();
    Market(std::list<Card> visibleCards, Deck marketDeck);
    ~Market();
    void addCard(Card card);
    void buyCard(Player& p, Card card);
};
#endif 