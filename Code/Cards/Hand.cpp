#include "Hand.h"
#include <vector>

Hand::Hand(std::vector<Card*> cards):m_cards(cards){
    std::cout << "Main créée" << std::endl;
}
Hand::Hand() {
    std::cout << "Main créée" << std::endl;
}

Hand::~Hand() {
    std::cout << "Destructeur Main (" << m_cards.size() << " cartes)" << std::endl;
    // Supprimer les cartes toujours présentes dans la main
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
}
void Hand::add(Card* card){
    m_cards.push_back(card);
}

Card* Hand::draw() {
    if (m_cards.empty()) {
        throw std::out_of_range("La main est vide, impossible de piocher une carte.");
    }
    
    Card* card = m_cards.front();
    m_cards.erase(m_cards.begin());
    
    std::cout << "Carte retirée de la main: " << card->getName() << std::endl;
    return card;
}

bool Hand::remove(Card* card) {
    for(size_t i = 0; i < m_cards.size(); i++) {
        if(m_cards[i]->getName() == card->getName()) {
            m_cards.erase(m_cards.begin() + i);
            std::cout << "Carte retirée de la main: " << card->getName() << std::endl;
            return true;
        }
    }
    return false;
}
bool Hand::isEmpty() const {
    return m_cards.empty();
}

size_t Hand::size() const {
    return m_cards.size();
}

void Hand::clear() {
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
    std::cout << "Main vidée" << std::endl;
}

std::vector<Card*> Hand::getCards() const {
    return m_cards;
}

Card* Hand::getCardAt(int index) {
    if (index < 0 || index >= static_cast<int>(m_cards.size())) {
        throw std::out_of_range("Index de carte invalide dans la main");
    }
    
    auto it = m_cards.begin();
    std::advance(it, index);
    return *it;
}

// Version const pour l'accès en lecture seule
const Card* Hand::getCardAt(int index) const {
    if (index < 0 || index >= static_cast<int>(m_cards.size())) {
        throw std::out_of_range("Index de carte invalide dans la main");
    }
    
    auto it = m_cards.begin();
    std::advance(it, index);
    return *it;
}

// Retirer une carte par index et la retourner
Card* Hand::removeCardAt(int index) {
    if (index < 0 || index >= static_cast<int>(m_cards.size())) {
        throw std::out_of_range("Index de carte invalide dans la main");
    }
    
    auto it = m_cards.begin();
    std::advance(it, index);
    Card* card = *it;
    m_cards.erase(it);
    
    std::cout << "Carte retirée de la main: " << card->getName() << std::endl;
    return card;
}

// Vérifier si la main contient une carte spécifique
bool Hand::contains(Card* card) {
    for (size_t i = 0; i < m_cards.size(); i++) {
        if (m_cards[i]->getName() == card->getName()) {
            return true;
        }
    }
    return false;
}