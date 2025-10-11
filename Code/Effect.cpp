#include "Effect.h"
#include "Player.h"

int Effect::getValue() const {
    return m_value;
}

void Effect::setValue(int value) {
    m_value = value;
}

