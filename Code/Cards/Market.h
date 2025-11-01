#ifndef __MARKET_H
#define __MARKET_H
#include <ostream>
#include <list>
#include <vector>
#include "../CardsType/Card.h"
#include "Deck.h"
#include "../Player.h"
#include "../CardsType/ItemCard.h"


class Effect;


class Market{
    std::vector<Card*> m_visibleCards;
    Deck m_marketDeck;
    std::vector<ItemCard*> m_fireGems;     
    std::vector<Card*> m_sacrificeZone; 

     // Template pour ajouter des effets
    template<typename T>
    void addEffect(std::vector<Effect*>& effects, int value);

    public:
    Market();
    Market(std::vector<Card*> visibleCards, Deck marketDeck);
    // RÈGLE DES 5
    ~Market();
    Market(const Market& other);
    Market& operator=(const Market& other);
    Market(Market&& other) noexcept;
    Market& operator=(Market&& other) noexcept;

    void initializeBaseSet();
    void initializeFireGems();
    void addCard(Card* card);
    bool buyCard(Player& player, Card& card, int& goldReserve);
    bool buyFireGem(Player& player, int& goldReserve);
    void removeCardFromMarket(Card* card);

    // Getters
    std::vector<Card*>& getVisibleCards();
    Deck& getMarketDeck();
    std::vector<ItemCard*>& getFireGems();
    std::vector<Card*>& getSacrificeZone();
    int getVisibleCardsCount() const;

    // Utilitaires
    void refillMarket();
    void displayMarket() const;
};
#endif 