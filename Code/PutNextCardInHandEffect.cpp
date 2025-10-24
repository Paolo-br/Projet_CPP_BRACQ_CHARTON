#include "PutNextCardInHandEffect.h"
#include "Player.h"
#include "Turn.h"
#include <iostream>

PutNextCardInHandEffect::PutNextCardInHandEffect() : Effect(0) {
}

void PutNextCardInHandEffect::apply(Player& player, Turn& turn) {
    (void)player; 
    
    turn.setNextCardGoesInHand(true);
    std::cout << "→ La prochaine carte acquise ira directement dans votre main!" << std::endl;
}

Effect* PutNextCardInHandEffect::clone() const {
    return new PutNextCardInHandEffect(*this);
}

std::string PutNextCardInHandEffect::getName() const {
    return "PutNextCardInHandEffect";
}
