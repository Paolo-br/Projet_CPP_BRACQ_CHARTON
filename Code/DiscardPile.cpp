#include "DiscardPile.h"

DiscardPile::DiscardPile(std::list<Card> cards):m_cards(cards){
    std::cout << "Constructeur DiscardPile" << std::endl;
}
DiscardPile::~DiscardPile(){}

void DiscardPile::add(Card card){
    m_cards.push_back(card);
}
void DiscardPile::clear(){
    m_cards = std::list<Card>({});
}