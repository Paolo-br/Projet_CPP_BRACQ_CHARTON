#ifndef __GAME_H
#define __GAME_H

#include <vector>
#include "Player.h"
#include "Market.h"
#include "Turn.h"
#include "GameSettings.h"

class Game {
    std::vector<Player> players;
    Market market;
    GameSettings settings;
    Turn currentTurn;

public:
    Game();

    void addPlayer(const Player& player);
    void start();
    void playTurn();
    void advanceTurn();
    void endGame();

    bool checkEndCondition() const;

    std::vector<Player>& getPlayers();
    Market& getMarket();
    GameSettings& getSettings();
};

#endif
