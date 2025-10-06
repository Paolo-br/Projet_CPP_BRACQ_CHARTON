#include "Effect.h"
#include "Player.h"

Effect::Effect(int value) : m_value(value) {
    std::cout << "Création d'un effet de valeur " << value << std::endl;
}

Effect::~Effect() {
    std::cout << "destruction d'un effet" << std::endl;
}

int Effect::getValue() const {
    return m_value;
}

void Effect::setValue(int value) {
    m_value = value;
}
