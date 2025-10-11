#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Phase.h"

class Turn {
private:
    Player* currentPlayer; // pointeur pour éviter les copies lourdes
    Phase phase;
    int goldReserve;
    int combatReserve;

public:
    Turn(); 
    Turn(Player& player);

    // RÈGLE DES 5 - À cause du pointeur raw
    ~Turn();
    Turn(const Turn& other);                    // Constructeur copie
    Turn& operator=(const Turn& other);         // Opérateur affectation copie
    Turn(Turn&& other) noexcept;                // Constructeur déplacement  
    Turn& operator=(Turn&& other) noexcept;     // Opérateur affectation déplacement

    void nextPhase();
    Player& getCurrentPlayer() const;
    Phase getPhase() const;

    void reset(Player& player); // pour changer de joueur au prochain tour

    // Gestion des réserves
    void addGold(int amount);
    void addCombat(int amount);
    int getGoldReserve();
    int getCombatReserve();
    void spendGold(int amount);
    void spendCombat(int amount);
    void clearReserves();
};

#endif // TURN_H
