#ifndef __CHAMPIONCARD_H
#define __CHAMPIONCARD_H
#include <string>
#include <list>
#include "Faction.h"
#include "Card.h"
#include "PrimaryAbility.h"

class Player;

class ChampionCard : public Card{
	int m_defense;
    bool m_isGuard;
    bool m_isTapped; // true = démobilisé, false = mobilisé
    int m_currentDamage;  // Dégâts reçus ce tour
    std::list<Ability*> m_abilities;


    public:

    ChampionCard(std::string name, int cost, Faction faction, std::string type, int defense, bool isGuard, bool isTapped, std::list<Ability*> abilities);
    
    // RÈGLE DES 5 - OBLIGATOIRE
    ~ChampionCard() override;
    ChampionCard(const ChampionCard& other);
    ChampionCard& operator=(const ChampionCard& other);
    ChampionCard(ChampionCard&& other) noexcept;
    ChampionCard& operator=(ChampionCard&& other) noexcept;
    
    void defend();
    void activate();
    void sacrifice();
   
    int getDefense();
    bool getIsGuard();
    bool getIsTapped();
    bool isGuard() const;       // Vérifie si c'est un Garde
    bool isReady() const;       // Vérifie si le champion est mobilisé
    std::list<Ability*> getAbilities();
    void setDefense(int defense);
    void setIsGuard(bool isGuard);
    void setIsTapped(bool isTapped);
    void setAbilities(std::list<Ability*> abilities);
    void setReady(bool ready);  // Mobilise/démobilise le champion
    
    std::string getType() const override { return "Champion"; }
    void executeEffects(Player& player, Turn& turn) override;
    void play(Player& owner, Player& opponent) override;

    // Gestion des dégâts
    void takeDamage(int damage);
    void resetDamage();  // Reset des dégâts en fin de tour
    bool isStunned() const;
    int getCurrentDamage() const { return m_currentDamage; }
    int getRemainingDefense() const { return m_defense - m_currentDamage; }
};
#endif