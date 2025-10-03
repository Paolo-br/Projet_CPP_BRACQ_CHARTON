#include "Deck.h"
#include <iostream>
#include "Card.h"
#include <list>

Deck::Deck(const std::list<Card>& cards) : m_cards(cards) {}
Deck::~Deck(){}
void Deck::shuffle(std::list<Card>& lst){
    // std::list<int> mylist = {1,2,3,4,5};

    std::vector<std::list<Card>::iterator> iters;
    //Ajoute les éléments de lst à la liste iters
    for (auto it = lst.begin(); it != lst.end(); ++it)
        iters.push_back(it);

    std::random_device rd; 
    std::mt19937 g(rd());
    std::shuffle(iters.begin(), iters.end(), g); // mélange iters

    std::list<Card> newlist;
    for (auto it : iters)
        newlist.splice(newlist.end(), lst, it); // déplace le nœud sans recopier

    lst.swap(newlist); // déplace les pointeurs des deux listes
}

std::list<Card> Deck::getCards(){return m_cards;}

Card Deck::draw(){
    if(m_cards.empty()){
        throw std::out_of_range("Le deck est vide, impossible de piocher une carte.");
    }
    Card topCard = m_cards.front();
    m_cards.pop_front();
    return topCard;
}
void Deck::addCard(Card& card){
    m_cards.push_back(card);
}

