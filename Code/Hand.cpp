#include "Hand.h"

Hand::Hand(std::list<Card> cards):m_cards(cards){
    std::cout << "Constructeur Hand" << std::endl;
}
Hand::~Hand(){}

void Hand::add(Card card){
    m_cards.push_back(card);
}

void Hand::remove(Card card){
    m_cards.remove(card);
}

void Hand::show(){ // A faire
    // for(int i=0;i<m_cards.size();i++){
    //     std::cout << m_cards[i]
    // }
}