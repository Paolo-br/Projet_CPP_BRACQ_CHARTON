#include "DrawEffect.h"
#include "Player.h"
#include "Turn.h"

DrawEffect::DrawEffect(int value) : Effect(value) {}

void DrawEffect::apply(Player& player, Turn& turn) {
    (void)turn; // Paramètre non utilisé
    int cardsToDraw = Effect::getValue();
    std::cout << "EFFET: Piocher " << cardsToDraw << " carte(s)" << std::endl;
    player.drawCards(cardsToDraw);
}

Effect* DrawEffect::clone() const {
    return new DrawEffect(*this);
}

std::string DrawEffect::getName() const {return "DrawEffect";}
