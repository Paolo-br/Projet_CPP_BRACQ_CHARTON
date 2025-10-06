#include "InPlayArea.h"

InPlayArea::InPlayArea(std::list<Card> cards):m_cards(cards){
    std::cout << "Constructeur InPlayArea" << std::endl;
}
InPlayArea::~InPlayArea(){}

void InPlayArea::add(Card card){
    m_cards.push_back(card);
}
void InPlayArea::clear(){ //A faire

}