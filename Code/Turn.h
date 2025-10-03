#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Phase.h"

class Turn {
private:
    Player* currentPlayer; // pointeur pour éviter les copies lourdes
    Phase phase;

public:
    Turn(); 
    Turn(Player& player);

    void nextPhase();
    Player& getCurrentPlayer() const;
    Phase getPhase() const;

    void reset(Player& player); // pour changer de joueur au prochain tour
};

#endif // TURN_H
