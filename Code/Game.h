#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Market.h"
#include "GameSettings.h"
#include "Turn.h"

class Game {
private:
    std::vector<Player> players;
    Market market;
    GameSettings settings;
    Turn currentTurn;

public:
    Game();

    void addPlayer(const Player& player);
    void start();
    void playTurn();
    void endGame();

    
    std::vector<Player>& getPlayers();
    Market& getMarket();
    GameSettings& getSettings();
};

#endif // GAME_H
