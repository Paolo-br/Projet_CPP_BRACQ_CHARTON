#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int health, int gold, const Deck& deck,
               const std::list<Card>& hand, const std::list<Card>& discardPile)
    : m_name(name), m_health(health), m_gold(gold), m_deck(deck), m_hand(hand), m_discardPile(discardPile) {
    std::cout << "Constructeur de Player initialisé" << std::endl;
}

Player::~Player() {
    std::cout << "Destructeur de Player" << std::endl;
}

std::string Player::getName() const { return m_name; }
int Player::getHealth() const { return m_health; }
int Player::getGold() const { return m_gold; }
Deck& Player::getDeck() { return m_deck; }
DiscardPile& Player::getDiscardPile() { return m_discardPile; }

void Player::setName(const std::string& name) { m_name = name; }
void Player::setHealth(int health) { m_health = health; }

void Player::addCardDeck(Card& card) {
    m_deck.addCard(card);
    std::cout << "Carte ajoutée dans le deck" << std::endl;
}

void Player::addCardDiscard(Card& card) {
    m_discardPile.add(card);
}

void Player::discard(const Card& card) {
    m_discardPile.add(card);
}

void Player::drawCard(const Card& card) {
    m_hand.add(card);
}

void Player::sacrifice(const Card& card) {
    m_hand.remove(card);
}

void Player::buyCard(Card& card) {
    if (card.getCost() <= m_gold) {
        discard(card);
        m_gold -= card.getCost();
    }
}

Hand& Player::getHand() { return m_hand; }
void Player::setGold(int gold) { m_gold = gold; }
