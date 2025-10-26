#ifndef OPTIONALSACRIFICEEFFECT_H
#define OPTIONALSACRIFICEEFFECT_H

#include "Effect.h"
#include <string>

class Player;
class Turn;

/**
 * Effet permettant de sacrifier optionnellement des cartes depuis la main ou la défausse
 * 
 * Cet effet permet au joueur de choisir de sacrifier une ou plusieurs cartes
 * depuis sa main et/ou sa défausse. Un bonus peut être appliqué après le sacrifice.
 */
class OptionalSacrificeEffect : public Effect {
private:
    int m_count;              // Nombre de cartes à sacrifier
    int m_maxCount;           // Nombre maximum de cartes (pour "up to X")
    bool m_isOptional;        // Le sacrifice est-il complètement optionnel?
    Effect* m_bonusEffect;    // Effet bonus appliqué après chaque sacrifice (peut être nullptr)

public:
    // Constructeurs
    OptionalSacrificeEffect(int count = 1, int maxCount = 1, bool isOptional = true, Effect* bonusEffect = nullptr);
    
    // Destructeur
    ~OptionalSacrificeEffect() override;
    
    // Méthodes héritées
    Effect* clone() const override;
    void apply(Player& player, Turn& turn) override;
    std::string getName() const override;
    int getValue();
    
    // Getters
    int getCount() const { return m_count; }
    int getMaxCount() const { return m_maxCount; }
    bool isOptional() const { return m_isOptional; }
    Effect* getBonusEffect() const { return m_bonusEffect; }
};

#endif // OPTIONALSACRIFICEEFFECT_H
