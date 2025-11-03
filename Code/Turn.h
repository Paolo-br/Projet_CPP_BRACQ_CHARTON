#ifndef TURN_H
#define TURN_H

#include "Phase.h"
#include "Faction.h"
#include <set>

class Player; 

class Turn {
private:
    Phase phase;
    int goldReserve;
    int combatReserve;
    Player* opponent;
    std::set<Faction> factionsPlayedThisTurn; // Track des factions jouées ce tour
    std::set<Faction> allyAbilitiesTriggeredThisTurn; // Track des capacités Allié déjà déclenchées ce tour

    bool nextCardGoesOnTop;       // La prochaine carte acquise va sur le deck
    bool nextActionGoesOnTop;     // La prochaine ACTION acquise va sur le deck
    bool nextCardGoesInHand;      // La prochaine carte acquise va en main

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
    void setGoldReserve(int amount);
    void setCombatReserve(int amount);
    void spendCombat(int amount);
    void clearReserves();
    
    // Gestion de l'adversaire
    void setOpponent(Player* opp);
    Player* getOpponent() const;
    bool hasOpponent() const;
    
    // Gestion des factions jouées (pour capacités Alliées)
    void addFactionPlayed(Faction faction);
    bool hasFactionBeenPlayed(Faction faction) const;
    void clearFactionsPlayed();
    int getFactionCount(Faction faction) const;
    
    // Gestion des capacités Alliées déjà déclenchées
    void markAllyAbilityTriggered(Faction faction);
    bool hasAllyAbilityBeenTriggered(Faction faction) const;
    void clearAllyAbilitiesTriggered();
    
    // Gestion des effets Guild de manipulation du deck
    void setNextCardGoesOnTop(bool value);
    void setNextActionGoesOnTop(bool value);
    void setNextCardGoesInHand(bool value);
    bool getNextCardGoesOnTop() const;
    bool getNextActionGoesOnTop() const;
    bool getNextCardGoesInHand() const;
    void resetAcquireFlags(); // Reset les flags après acquisition
};

#endif