#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include <string>
#include <list>
#include "Cards/Deck.h"
#include "CardsType/Card.h"
#include "Cards/Hand.h"
#include "Cards/DiscardPile.h"
#include "InPlayArea.h"


class ChampionCard;

class Player {
private:
    std::string m_name;
    int m_health;
    int m_gold;
    Deck m_deck;
    Hand m_hand;
    DiscardPile m_discardPile;
    InPlayArea m_playArea; // Cartes en jeu (Champions)
    std::vector<Card*> m_sacrificeZone; // Zone de Sacrifice
    bool m_eliminated;

public:
    Player(const std::string& name, int health, const Deck& deck,
           const Hand& hand, const DiscardPile& discardPile);
    // Constructeur avec move semantics pour le chargement
    Player(const std::string& name, int health, Deck&& deck,
           Hand&& hand, DiscardPile&& discardPile);
    
    // RÈGLE DES 5 - Tout implémenter
    ~Player();                                      // 1. Destructeur
    Player(const Player& other);                    // 2. Constructeur copie
    Player& operator=(const Player& other);         // 3. Opérateur affectation copie
    Player(Player&& other) noexcept;                // 4. Constructeur déplacement
    Player& operator=(Player&& other) noexcept;     // 5. Opérateur affectation déplacement

    // Getters
    std::string getName() const;
    int getHealth() const;
    Deck& getDeck();
    Hand& getHand();
    DiscardPile& getDiscardPile();
    InPlayArea& getPlayArea();
    std::vector<Card*>& getSacrificeZone();
    bool isEliminated() const;
    int getGold();

    // Setters
    void setName(const std::string& name);
    void setHealth(int health);
    void setEliminated(bool eliminated);
    void setGold(int gold);

    // Actions du jeu
    void initializeStarterDeck();
    void drawCards(int count);
    void discardHand();
    void mobilizeChampions(); // Remet tous les Champions mobilisés
    void takeDamage(int damage);
    void heal(int amount);

    void discardCard(Card* card);

    
    // Gestion des Champions
    bool hasGuardInPlay() const;
    void stunChampion(ChampionCard& champion);
    void sacrificeChampion(ChampionCard& champion);
    void addChampionToPlayArea(ChampionCard& champion);
    
    // Gestion de la Zone de Sacrifice
    void addToSacrificeZone(Card* card);
    void viewSacrificeZone() const;

    
    bool canBeAttacked() const;  // Vérifie si le joueur peut être attaqué
    bool canAttackChampion(const ChampionCard& champion) const; // Vérifie si un champion peut être attaqué
    
    void attackPlayer(int combatDamage);  // Attaquer le joueur
    void attackChampion(ChampionCard& champion, int combatDamage); // Attaquer un champion
    
    ChampionCard* findChampionToAttack(); // Trouve un champion attaquable
    void stunChampions(); // Assomme les champions avec dégâts suffisants
    

    void addCardToPlayArea(Card* card); 
    void acquireCard(Card* card, Turn& turn);

    // Gestion des dégâts des champions
    void resetChampionDamage(); // Reset tous les dégâts en fin de tour
    
    // Utilitaires
    void displayStatus() const;
};

#endif
