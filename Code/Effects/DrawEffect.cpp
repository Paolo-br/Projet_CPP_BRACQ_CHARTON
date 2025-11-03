#include "DrawEffect.h"
#include "../Player.h"
#include "../Turn.h"

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

Effect* DrawEffect::getOption1() const { return nullptr; }
Effect* DrawEffect::getOption2() const { return nullptr; }
const ResourceType* DrawEffect::getResourceType() const { return nullptr; }
const ConditionType* DrawEffect::getConditionType() const { return nullptr; }
bool DrawEffect::getIsOptional() const { return false; }
const std::string* DrawEffect::getCardTypeFilter() const { return nullptr; }
int DrawEffect::getCount() const { return 0; }
int DrawEffect::getMaxCount() const { return 0; }
Effect* DrawEffect::getBonusEffect() const { return nullptr; }
