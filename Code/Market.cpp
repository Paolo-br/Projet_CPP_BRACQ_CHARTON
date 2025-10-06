#include "Market.h"

Market::Market(std::list<Card> visibleCards, Deck marketDeck):m_visibleCards(visibleCards),m_marketDeck(marketDeck){
    std::cout << "Constructeur Market" << std::endl;
}
Market::Market() {
    std::cout << "Constructeur Market par défaut" << std::endl;
}

Market::~Market(){}

void Market::addCard(Card card){m_visibleCards.push_back(card);}

void Market::buyCard(Player& player, Card card){
    if(player.getGold()>card.getCost()){
        player.addCardDiscard(card);
    }
    else{
        std::cout <<"La carte ne peut pas être acheté" << std::endl;
    }
}