#include "Player.h"
#include <iostream>

Player::Player(std::string name, int health, int gold, Deck deck, std::list<Card> hand, std::list<Card> discardPile):m_name(name), m_health(health), m_gold(gold), m_deck(deck), m_hand(hand),m_discardPile(discardPile){
    std::cout << "Constructeur de Player initialisé" << std::endl;
}

Player::~Player(){
    std::cout << "Destructeur de Player" << std::endl;
}
std::string Player::getName(){ return m_name;}
int Player::getHealth(){ return m_health;}
Deck Player::getDeck(){ return m_deck;}
std::list<Card> Player::getDiscardPile(){return m_discardPile;}
void Player::setName(std::string name){m_name=name;}
void Player::setHealth(int health){m_health=health;}
void Player::addCardDeck(Card card) {
    m_deck.addCard(card);
    std::cout << "Carte ajoutée" << std::endl;
}
void Player::discard(Card card){m_discardPile.push_back(card);}
void Player::drawCard(Card card){m_hand.push_back(card);}
void Player::sacrifice(Card card){m_hand.remove(card);}
void Player::buyCard(Card card){
    if(card.getCost() < m_gold){
        discard(card);
    }
}