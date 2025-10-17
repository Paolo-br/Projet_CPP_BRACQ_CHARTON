#ifndef TURN_H
#define TURN_H

#include "Phase.h"

class Turn {
private:
    Phase phase;
    int goldReserve;
    int combatReserve;

public:
    Turn(); 

    // Règle des 0/3/5 : Pas de gestion de ressources dynamiques
    // Utilisation des versions par défaut du compilateur
    ~Turn() = default;
    Turn(const Turn& other) = default;
    Turn& operator=(const Turn& other) = default;
    Turn(Turn&& other) noexcept = default;
    Turn& operator=(Turn&& other) noexcept = default;

    void nextPhase();
    Phase getPhase() const;

    void reset(); // Reset pour un nouveau tour

    // Gestion des réserves
    void addGold(int amount);
    void addCombat(int amount);
    int getGoldReserve() const;
    int getCombatReserve() const;
    void spendGold(int amount);
    void spendCombat(int amount);
    void clearReserves();
};

#endif // TURN_H
