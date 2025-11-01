#ifndef __CHAMPIONCARD_H
#define __CHAMPIONCARD_H
#include <string>
#include <vector>
#include "../Faction.h"
#include "Card.h"
#include "../Effects/Effect.h"
#include "../Abilities/Ability.h"
#include "../Utils.h"


class Player;
class Effect;
class ChampionCard : public Card{
	int m_defense;
    bool m_isGuard;
    bool m_isTapped; // true = démobilisé, false = mobilisé
    int m_currentDamage;  // Dégâts accumulés ce tour
    std::vector<Ability*> m_abilities;


    public:
    void printChampionCard();

    ChampionCard(const std::string name, int cost, Faction faction, const std::string type, 
                 int defense, bool isGuard, std::vector<Ability*> abilities);
    
    // RÈGLE DES 5 - OBLIGATOIRE
    ~ChampionCard() override;
    ChampionCard(const ChampionCard& other);
    ChampionCard& operator=(const ChampionCard& other);
    ChampionCard(ChampionCard&& other) noexcept;
    ChampionCard& operator=(ChampionCard&& other) noexcept;
    
    // Actions du champion
    void activateAbility(Player& owner, Turn& turn);  // Active la capacité principale
    void triggerAllyAbility(Player& owner, Turn& turn); // Déclenche l'effet Allié
    void triggerSacrificeAbility(Player& owner, Turn& turn); // Déclenche l'effet Sacrifice
    void sacrifice(Player& owner); // Sacrifie le champion
    std::tuple<int,int> display(int row,int col) override;
   
    // Getters
    int getDefense() const;
    bool getIsGuard() const;
    bool getIsTapped() const;
    bool isGuard() const;       // Vérifie si c'est un Garde
    bool isReady() const;       // Vérifie si le champion est mobilisé
    std::vector<Ability*> getAbilities() const override;
    std::vector<Effect*> getEffect() const override { return {}; }
    int getCurrentDamage() const { return m_currentDamage; }
    int getRemainingDefense() const { return m_defense - m_currentDamage; }
    

    // Setters
    void setDefense(int defense);
    void setIsGuard(bool isGuard);
    void setIsTapped(bool isTapped);
    void setAbilities(std::vector<Ability*> abilities);
    void setReady(bool ready);  // Mobilise/démobilise le champion
    
    // Méthodes de Card
    std::string getType() const override { return "Champion"; }
    void executeEffects(Player& player, Turn& turn) override;
    void play(Player& owner, Player& opponent) override;

    // Vérification des abilities
    bool hasActivateAbility() const;
    bool hasAllyAbility() const override;
    bool hasSacrificeAbility() const override;

    // Gestion des dégâts
    void takeDamage(int damage);
    void resetDamage();  // Reset des dégâts en fin de tour
    bool isStunned() const;
};
#endif