#ifndef __GAME_H
#define __GAME_H

#include <vector>
#include "Player.h"
#include "Market.h"
#include "Turn.h"
#include "GameSettings.h"



class Game {
    std::vector<Player> m_players;
    Market m_market;
    GameSettings m_settings;
    Turn m_currentTurn;
    int m_currentPlayerIndex;
    bool m_gameStarted;
    bool m_gameEnded;
    bool m_mainPhaseActive;
    
public:
    Game();

    // RÈGLE DES 5
    ~Game();
    Game(const Game& other);
    Game& operator=(const Game& other);
    Game(Game&& other) noexcept;
    Game& operator=(Game&& other) noexcept;

    void addPlayer(const Player& player);

    void start();
    void playTurn();



    void playCard(Card* card, Player* target = nullptr);
    void acquireCard(Card* card);
    void attackPlayer(Player& target, int combat);
    void attackChampion(ChampionCard& target, int combat);
    



    
    // Getters
    std::vector<Player>& getPlayers();
    Market& getMarket();
    GameSettings& getSettings();
    Turn& getCurrentTurn();
    Player& getCurrentPlayer();
    Player& getNextPlayer();
    bool isGameOver() const;
    bool isMainPhaseActive() const { return m_mainPhaseActive; }

    // Méthodes pour l'interaction joueur
    void playCardFromHand(int handIndex);
    void activateChampionAbility(const std::string& championName);
    void acquireCardFromMarket(int marketIndex);
    void attackPlayer(int targetPlayerIndex);
    void attackChampion(int targetPlayerIndex, const std::string& championName);
    void useAllyAbility(const std::string& cardName);
    void sacrificeCard(const std::string& cardName);

    private:
    // Phases du tour
    void mainPhase();
    void discardPhase();
    void drawPhase();
    void advanceTurn();
    void endGame();
    bool checkEndCondition() const;
    Player* getWinner() const;
    void displayGameState() const;

    // Méthodes helper pour la phase principale
    void displayMainPhaseOptions();
    void handleMainPhaseChoice(int choice);
    void playCardsPhase();
    void activateAbilitiesPhase();
    void acquireCardsPhase();
    void combatPhase();
    void viewDiscardPile();
    
    // Gestion des capacités Alliées
    void triggerAllyAbilities(Faction faction);
    void checkAndTriggerAllyAbilities();
    
    // Validation des actions
    bool canAttackPlayer(const Player& target) const;
    bool canTargetChampion(const Player& target, const ChampionCard& champion) const;
};

#endif
