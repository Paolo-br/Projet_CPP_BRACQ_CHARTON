#include "DiscardOpponentEffect.h"
#include "Player.h"
#include <iostream>

DiscardOpponentEffect::DiscardOpponentEffect(int cardCount) : Effect(cardCount) {}

void DiscardOpponentEffect::apply(Player& player, Turn& turn) {
    (void)player;
    (void)turn;
    
    std::cout << "Effet: L'adversaire défausse " << getValue() 
              << " carte(s) (à implémenter dans Game)" << std::endl;
    // NOTEA MOI MEME: Nécessite l'accès aux adversaires via Game
}

Effect* DiscardOpponentEffect::clone() const {
    return new DiscardOpponentEffect(getValue());
}

std::string DiscardOpponentEffect::getName() const {
    return "DiscardOpponentEffect";
}
