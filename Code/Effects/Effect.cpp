#include "Effect.h"
#include "../Turn.h"
#include "../Player.h"

int Effect::getValue() const {
    return m_value;
}

void Effect::setValue(int value) {
    m_value = value;
}

Effect::Effect(int value):m_value(value){
    std::cout << "Constructeur Effect initialisé" << std::endl;
}

void Effect::apply(Player& player, Turn& turn){
    std::cout << "Joueur : " << player.getName() << std::endl;
    std::cout << "Or : " << turn.getGoldReserve() << std::endl;
}

std::string Effect::getName() const {return "Effect";}

