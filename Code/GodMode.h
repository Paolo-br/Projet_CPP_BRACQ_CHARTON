#ifndef __GODMODE_H
#define __GODMODE_H

#include <vector>
#include "Player.h"
#include "Cards/Market.h"
#include "Turn.h"

class GodMode {
private:
    bool m_isActive;
    
public:
    GodMode();
    
    // Activer/Désactiver le God Mode
    void activate();
    void deactivate();
    void toggle();
    bool isActive() const;
    
    // Fonctionnalités du God Mode
    void setAllPlayersToOneHP(std::vector<Player>& players);
    void buyFromFullDeck(Player& player, Market& market, Turn& turn);
    
    // Afficher l'interface God Mode
    void displayMenu(std::vector<Player>& players, Market& market, Turn& turn);
};

#endif