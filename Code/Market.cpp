#include "Market.h"
#include <iostream>
#include <vector>
#include "ActionCard.h"
#include "ItemCard.h"
#include "ChampionCard.h"
#include "DrawThenDiscardEffect.h"
#include "Effect.h"
#include "GoldEffect.h"
#include "AttackEffect.h"
#include "HealEffect.h"
#include "DrawEffect.h"
#include "SacrificeEffect.h"
#include "PrepareChampionEffect.h"
#include "StunChampionEffect.h"
#include "DiscardOpponentEffect.h"
#include "ConditionalEffect.h"
#include "ChoiceEffect.h"
#include "PutNextCardOnTopEffect.h"
#include "PutNextCardInHandEffect.h"
#include "PutFromDiscardOnTopEffect.h"
#include "OptionalSacrificeEffect.h"
#include "Ability.h"
#include "AllyAbility.h"
#include "SacrificeAbility.h"
#include "ActivateAbility.h"
#include "PrimaryAbility.h"



// Constructeurs
Market::Market() : m_visibleCards(), m_marketDeck(), m_fireGems(), m_sacrificeZone() {}
Market::Market(std::vector<Card*> visibleCards, Deck marketDeck)
    : m_visibleCards(visibleCards), m_marketDeck(marketDeck) {}

// 1. Destructeur
Market::~Market() {
    std::cout << "Destructeur Market" << std::endl;
}

// 2. Constructeur copie
Market::Market(const Market& other)
    : m_visibleCards(other.m_visibleCards), 
      m_marketDeck(other.m_marketDeck),
      m_fireGems(other.m_fireGems),
      m_sacrificeZone(other.m_sacrificeZone) {
    std::cout << "Constructeur copie Market" << std::endl;
}

// 3. Opérateur affectation copie
Market& Market::operator=(const Market& other) {
    if (this != &other) {
        m_visibleCards = other.m_visibleCards;
        m_marketDeck = other.m_marketDeck;
        m_fireGems = other.m_fireGems;
        m_sacrificeZone = other.m_sacrificeZone;
    }
    std::cout << "Opérateur affectation copie Market" << std::endl;
    return *this;
}

// 4. Constructeur déplacement
Market::Market(Market&& other) noexcept
    : m_visibleCards(std::move(other.m_visibleCards)),
      m_marketDeck(std::move(other.m_marketDeck)),
      m_fireGems(std::move(other.m_fireGems)),
      m_sacrificeZone(std::move(other.m_sacrificeZone)) {
    std::cout << "Constructeur déplacement Market" << std::endl;
}

// 5. Opérateur affectation déplacement
Market& Market::operator=(Market&& other) noexcept {
    if (this != &other) {
        m_visibleCards = std::move(other.m_visibleCards);
        m_marketDeck = std::move(other.m_marketDeck);
        m_fireGems = std::move(other.m_fireGems);
        m_sacrificeZone = std::move(other.m_sacrificeZone);
    }
    std::cout << "Opérateur affectation déplacement Market" << std::endl;
    return *this;
}



void Market::addCard(Card* card){m_visibleCards.push_back(card);}

bool Market::buyCard(Player& player, Card& card, int& goldReserve) {
    if (goldReserve >= card.getCost()) {
        // Retirer l'or de la réserve
        goldReserve -= card.getCost();
        
        // Ajouter la carte à la défausse du joueur
        player.getDiscardPile().add(&card);
        
        // Retirer la carte du marché visible
        removeCardFromMarket(&card);
        
        // Remplir l'emplacement vide
        refillMarket();
        
        std::cout << player.getName() << " achète " << card.getName() << " pour " << card.getCost() << " or." << std::endl;
        std::cout << "Or restant: " << goldReserve << std::endl;
        return true;
    } else {
        std::cout << "Pas assez d'or pour acheter " << card.getName() 
             << " (coût: " << card.getCost() << ", or disponible: " << goldReserve << ")" << std::endl;
        return false;
    }
}

// Achat d'une Gemme de Feu
bool Market::buyFireGem(Player& player, int& goldReserve) {
    if (m_fireGems.empty()) {
        std::cout << "Plus de Gemmes de Feu disponibles !" << std::endl;
        return false;
    }
    
    if (goldReserve >= 2) { // Les Gemmes de Feu coûtent 2
        goldReserve -= 2;
        
        // Prendre la première Gemme de Feu
        ItemCard* fireGem = m_fireGems.front();
        m_fireGems.erase(m_fireGems.begin());
        
        // Ajouter à la défausse du joueur
        player.getDiscardPile().add(fireGem);
        
        std::cout << player.getName() << " achète une Gemme de Feu pour 2 or." << std::endl;
        std::cout << "Or restant: " << goldReserve << std::endl;
        return true;
    } else {
        std::cout << "Pas assez d'or pour acheter une Gemme de Feu (coût: 2, or disponible: " << goldReserve << ")" << std::endl;
        return false;
    }
}
void Market::removeCardFromMarket(Card* card) {
    for (size_t i=0; i<m_visibleCards.size(); i++){
        if (m_visibleCards[i]->getName() == card->getName()){
            m_visibleCards.erase(m_visibleCards.begin()+i);
            break;
        }
    }
}

void Market::refillMarket() {
    while (m_visibleCards.size() < 5 && !m_marketDeck.isEmpty()) {
        Card* newCard = m_marketDeck.draw();

        m_visibleCards.push_back(newCard);
    }
}

template<typename T>
void Market::addEffect(std::vector<Effect*>& effects, int value) {
    effects.push_back(new T(value));
}

void Market::initializeFireGems() {
    // Fire Gem (×16) - Coût: 2
    // Primary: +2 Gold
    // Sacrifice: +3 Combat
    for (int i = 0; i < 16; ++i) {
        std::vector<Effect*> primaryEffs_fireGem;
        primaryEffs_fireGem.push_back(new GoldEffect(2));
        
        std::vector<Effect*> sacrificeEffs_fireGem;
        sacrificeEffs_fireGem.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities_fireGem;
        abilities_fireGem.push_back(new PrimaryAbility(primaryEffs_fireGem));
        abilities_fireGem.push_back(new SacrificeAbility(sacrificeEffs_fireGem));
        
        ItemCard* fireGem = new ItemCard("Fire Gem", 2, Faction::None, "Item", {}, abilities_fireGem);
        m_fireGems.push_back(fireGem);
    }
}

void Market::initializeBaseSet() {
    std::cout << "Initialisation du marché (Base Set)..." << std::endl;

    // —————————————————————
    // IMPERIAL
    // —————————————————————

    // 1. Arkus, Imperial Dragon (Champion, Guard) - Coût: 8, Défense: 6
    // Expend: +5 Combat, Draw 1
    // Imperial Ally: +6 Health
    std::vector<Effect*> activateEffs_arkus;
    activateEffs_arkus.push_back(new AttackEffect(5));
    activateEffs_arkus.push_back(new DrawEffect(1));
    
    std::vector<Effect*> allyEffs_arkus;
    allyEffs_arkus.push_back(new HealEffect(6));
    
    std::vector<Ability*> abilities_arkus;
    abilities_arkus.push_back(new ActivateAbility(activateEffs_arkus));
    abilities_arkus.push_back(new AllyAbility(allyEffs_arkus));
    
    ChampionCard* arkus = new ChampionCard("Arkus, Imperial Dragon", 8, Faction::Imperial, "Champion", 6, true,abilities_arkus);
    m_marketDeck.addCard(arkus);

    // 2. Close Ranks (Action) - Coût: 3
    // +5 Combat, +2 Combat pour chaque champion en jeu
    // Imperial Ally: +6 Health
    std::vector<Effect*> primaryEffs_closeRanks;
    primaryEffs_closeRanks.push_back(new AttackEffect(5));
    primaryEffs_closeRanks.push_back(new ConditionalEffect(ResourceType::Combat, 2, ConditionType::ChampionCount));
    
    std::vector<Effect*> allyEffs_closeRanks;
    allyEffs_closeRanks.push_back(new HealEffect(6));
    
    std::vector<Ability*> abilities_closeRanks;
    abilities_closeRanks.push_back(new PrimaryAbility(primaryEffs_closeRanks));
    abilities_closeRanks.push_back(new AllyAbility(allyEffs_closeRanks));
    
    ActionCard* closeRanks = new ActionCard("Close Ranks", 3, Faction::Imperial, "Action", {}, abilities_closeRanks);
    m_marketDeck.addCard(closeRanks);

    // 3. Command (Action) - Coût: 5
    // +2 Gold, +3 Combat, +4 Health, Draw 1
    std::vector<Effect*> primaryEffs_command;
    primaryEffs_command.push_back(new GoldEffect(2));
    primaryEffs_command.push_back(new AttackEffect(3));
    primaryEffs_command.push_back(new HealEffect(4));
    primaryEffs_command.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_command;
    abilities_command.push_back(new PrimaryAbility(primaryEffs_command));
    
    ActionCard* command = new ActionCard("Command", 5, Faction::Imperial, "Action", {}, abilities_command);
    m_marketDeck.addCard(command);

    // 4. Darian, War Mage (Champion) - Coût: 4, Défense: 5
    // Expend: +3 Combat OU +4 Health
    std::vector<Effect*> activateEffs_darian;
    activateEffs_darian.push_back(new ChoiceEffect(
        new AttackEffect(3), "+3 Combat",
        new HealEffect(4), "+4 Health"
    ));
    
    std::vector<Ability*> abilities_darian;
    abilities_darian.push_back(new ActivateAbility(activateEffs_darian));
    
    ChampionCard* darian = new ChampionCard("Darian, War Mage", 4, Faction::Imperial, "Champion", 5, false, abilities_darian);
    m_marketDeck.addCard(darian);

    // 5. Domination (Action) - Coût: 7
    // +6 Combat, +6 Health, Draw 1
    // Imperial Ally: Prepare a champion
    std::vector<Effect*> primaryEffs_domination;
    primaryEffs_domination.push_back(new AttackEffect(6));
    primaryEffs_domination.push_back(new HealEffect(6));
    primaryEffs_domination.push_back(new DrawEffect(1));
    
    std::vector<Effect*> allyEffs_domination;
    allyEffs_domination.push_back(new PrepareChampionEffect());
    
    std::vector<Ability*> abilities_domination;
    abilities_domination.push_back(new PrimaryAbility(primaryEffs_domination));
    abilities_domination.push_back(new AllyAbility(allyEffs_domination));
    
    ActionCard* domination = new ActionCard("Domination", 7, Faction::Imperial, "Action", {}, abilities_domination);
    m_marketDeck.addCard(domination);

    // 6. Cristov, the Just (Champion, Guard) - Coût: 5, Défense: 5
    // Expend: +2 Combat, +3 Health
    // Imperial Ally: Draw 1
    std::vector<Effect*> activateEffs_cristov;
    activateEffs_cristov.push_back(new AttackEffect(2));
    activateEffs_cristov.push_back(new HealEffect(3));
    
    std::vector<Effect*> allyEffs_cristov;
    allyEffs_cristov.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_cristov;
    abilities_cristov.push_back(new ActivateAbility(activateEffs_cristov));
    abilities_cristov.push_back(new AllyAbility(allyEffs_cristov));
    
    ChampionCard* cristov = new ChampionCard("Cristov, the Just", 5, Faction::Imperial, "Champion", 5, true,abilities_cristov);
    m_marketDeck.addCard(cristov);

    // 7. Kraka, High Priest (Champion) - Coût: 6, Défense: 6
    // Expend: +2 Health, Draw 1
    // Imperial Ally: +2 Health pour chaque champion en jeu
    std::vector<Effect*> activateEffs_kraka;
    activateEffs_kraka.push_back(new HealEffect(2));
    activateEffs_kraka.push_back(new DrawEffect(1));
    
    std::vector<Effect*> allyEffs_kraka;
    allyEffs_kraka.push_back(new ConditionalEffect(ResourceType::Health, 2, ConditionType::ChampionCount));
    
    std::vector<Ability*> abilities_kraka;
    abilities_kraka.push_back(new ActivateAbility(activateEffs_kraka));
    abilities_kraka.push_back(new AllyAbility(allyEffs_kraka));
    
    ChampionCard* kraka = new ChampionCard("Kraka, High Priest", 6, Faction::Imperial, "Champion", 6, false, abilities_kraka);
    m_marketDeck.addCard(kraka);

    // 8. Man-at-Arms (Champion, Guard) - Coût: 3, Défense: 4 (×2)
    // Expend: +2 Combat, +1 Combat pour chaque AUTRE garde en jeu
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_man;
        activateEffs_man.push_back(new AttackEffect(2));
        activateEffs_man.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::OtherGuardCount, Faction::None, false));
        
        std::vector<Ability*> abilities_man;
        abilities_man.push_back(new ActivateAbility(activateEffs_man));
        
        ChampionCard* man = new ChampionCard("Man-at-Arms", 3, Faction::Imperial, "Champion", 4, true, abilities_man);
        m_marketDeck.addCard(man);
    }

    // 9. Master Weyan (Champion, Guard) - Coût: 4, Défense: 4
    // Expend: +3 Combat, +1 Combat pour chaque AUTRE champion en jeu
    std::vector<Effect*> activateEffs_weyan;
    activateEffs_weyan.push_back(new AttackEffect(3));
    activateEffs_weyan.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::OtherChampionCount, Faction::None, false));
    
    std::vector<Ability*> abilities_weyan;
    abilities_weyan.push_back(new ActivateAbility(activateEffs_weyan));
    
    ChampionCard* masterWeyan = new ChampionCard("Master Weyan", 4, Faction::Imperial, "Champion", 4, true, abilities_weyan);
    m_marketDeck.addCard(masterWeyan);

    // 10. Rally the Troops (Action) - Coût: 4
    // +5 Combat, +5 Health
    // Imperial Ally: Prepare a champion
    std::vector<Effect*> primaryEffs_rally;
    primaryEffs_rally.push_back(new AttackEffect(5));
    primaryEffs_rally.push_back(new HealEffect(5));
    
    std::vector<Effect*> allyEffs_rally;
    allyEffs_rally.push_back(new PrepareChampionEffect());
    
    std::vector<Ability*> abilities_rally;
    abilities_rally.push_back(new PrimaryAbility(primaryEffs_rally));
    abilities_rally.push_back(new AllyAbility(allyEffs_rally));
    
    ActionCard* rally = new ActionCard("Rally the Troops", 4, Faction::Imperial, "Action", {}, abilities_rally);
    m_marketDeck.addCard(rally);

    // 11. Recruit (Action) - Coût: 2 (×3)
    // +2 Gold, +3 Health, +1 Health pour chaque champion en jeu
    // Imperial Ally: +1 Gold
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_recruit;
        primaryEffs_recruit.push_back(new GoldEffect(2));
        primaryEffs_recruit.push_back(new HealEffect(3));
        primaryEffs_recruit.push_back(new ConditionalEffect(ResourceType::Health, 1, ConditionType::ChampionCount));
        
        std::vector<Effect*> allyEffs_recruit;
        allyEffs_recruit.push_back(new GoldEffect(1));
        
        std::vector<Ability*> abilities_recruit;
        abilities_recruit.push_back(new PrimaryAbility(primaryEffs_recruit));
        abilities_recruit.push_back(new AllyAbility(allyEffs_recruit));
        
        ActionCard* recruit = new ActionCard("Recruit", 2, Faction::Imperial, "Action", {}, abilities_recruit);
        m_marketDeck.addCard(recruit);
    }

    // 12. Tithe Priest (Champion) - Coût: 2, Défense: 3 (×2)
    // Expend: +1 Gold OU +1 Health pour chaque champion en jeu
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_tithe;
        activateEffs_tithe.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new ConditionalEffect(ResourceType::Health, 1, ConditionType::ChampionCount), "+1 Health par champion"
        ));
        
        std::vector<Ability*> abilities_tithe;
        abilities_tithe.push_back(new ActivateAbility(activateEffs_tithe));
        
        ChampionCard* tithe = new ChampionCard("Tithe Priest", 2, Faction::Imperial, "Champion", 3, false, abilities_tithe);
        m_marketDeck.addCard(tithe);
    }

    // 13. Taxation (Action) - Coût: 1 (×3)
    // +2 Gold
    // Imperial Ally: +6 Health
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_taxation;
        primaryEffs_taxation.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs_taxation;
        allyEffs_taxation.push_back(new HealEffect(6));
        
        std::vector<Ability*> abilities_taxation;
        abilities_taxation.push_back(new PrimaryAbility(primaryEffs_taxation));
        abilities_taxation.push_back(new AllyAbility(allyEffs_taxation));
        
        ActionCard* taxation = new ActionCard("Taxation", 1, Faction::Imperial, "Action", {}, abilities_taxation);
        m_marketDeck.addCard(taxation);
    }

    // 14. Word of Power (Action) - Coût: 6
    // Draw 2 cartes
    // Imperial Ally: +5 Health
    // Sacrifice: +5 Combat
    std::vector<Effect*> primaryEffs_word;
    primaryEffs_word.push_back(new DrawEffect(2));
    
    std::vector<Effect*> allyEffs_word;
    allyEffs_word.push_back(new HealEffect(5));
    
    std::vector<Effect*> sacrificeEffs_word;
    sacrificeEffs_word.push_back(new AttackEffect(5));
    
    std::vector<Ability*> abilities_word;
    abilities_word.push_back(new PrimaryAbility(primaryEffs_word));
    abilities_word.push_back(new AllyAbility(allyEffs_word));
    abilities_word.push_back(new SacrificeAbility(sacrificeEffs_word));
    
    ActionCard* word = new ActionCard("Word of Power", 6, Faction::Imperial, "Action", {}, abilities_word);
    m_marketDeck.addCard(word);

    // —————————————————————
    // GUILD
    // —————————————————————

    // 1. Borg, Ogre Mercenary (Champion, Guard) - Coût: 6, Défense: 6
    // Expend: +4 Combat
    std::vector<Effect*> activateEffs_borg;
    activateEffs_borg.push_back(new AttackEffect(4));
    
    std::vector<Ability*> abilities_borg;
    abilities_borg.push_back(new ActivateAbility(activateEffs_borg));
    
    ChampionCard* borg = new ChampionCard("Borg, Ogre Mercenary", 6, Faction::Guilde, "Champion", 6, true, abilities_borg);
    m_marketDeck.addCard(borg);

    // 2. Bribe (Action) - Coût: 3 (×3)
    // +3 Gold
    // Guild Ally: Put the next action you acquire this turn on top of your deck.
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_bribe;
        primaryEffs_bribe.push_back(new GoldEffect(3));
        
        std::vector<Effect*> allyEffs_bribe;
        allyEffs_bribe.push_back(new PutNextCardOnTopEffect("Action")); // Filter pour Actions seulement
        
        std::vector<Ability*> abilities_bribe;
        abilities_bribe.push_back(new PrimaryAbility(primaryEffs_bribe));
        abilities_bribe.push_back(new AllyAbility(allyEffs_bribe));
        
        ActionCard* bribe = new ActionCard("Bribe", 3, Faction::Guilde, "Action", {}, abilities_bribe);
        m_marketDeck.addCard(bribe);
    }

    // 3. Death Threat (Action) - Coût: 3
    // +1 Combat, Draw 1
    // Guild Ally: Stun target champion
    std::vector<Effect*> primaryEffs_deathThreat;
    primaryEffs_deathThreat.push_back(new AttackEffect(1));
    primaryEffs_deathThreat.push_back(new DrawEffect(1));
    
    std::vector<Effect*> allyEffs_deathThreat;
    allyEffs_deathThreat.push_back(new StunChampionEffect());
    
    std::vector<Ability*> abilities_deathThreat;
    abilities_deathThreat.push_back(new PrimaryAbility(primaryEffs_deathThreat));
    abilities_deathThreat.push_back(new AllyAbility(allyEffs_deathThreat));
    
    ActionCard* deathThreat = new ActionCard("Death Threat", 3, Faction::Guilde, "Action", {}, abilities_deathThreat);
    m_marketDeck.addCard(deathThreat);

    // 4. Deception (Action) - Coût: 5
    // +2 Gold, Draw 1
    // Guild Ally: Put the next card you acquire this turn into your hand
    std::vector<Effect*> primaryEffs_deception;
    primaryEffs_deception.push_back(new GoldEffect(2));
    primaryEffs_deception.push_back(new DrawEffect(1));
    
    std::vector<Effect*> allyEffs_deception;
    allyEffs_deception.push_back(new PutNextCardInHandEffect());
    
    std::vector<Ability*> abilities_deception;
    abilities_deception.push_back(new PrimaryAbility(primaryEffs_deception));
    abilities_deception.push_back(new AllyAbility(allyEffs_deception));
    
    ActionCard* deception = new ActionCard("Deception", 5, Faction::Guilde, "Action", {}, abilities_deception);
    m_marketDeck.addCard(deception);

    // 5. Fire Bomb (Action) - Coût: 8
    // +8 Combat, Stun target champion, Draw 1
    // Sacrifice: +5 Combat
    std::vector<Effect*> primaryEffs_fireBomb;
    primaryEffs_fireBomb.push_back(new AttackEffect(8));
    primaryEffs_fireBomb.push_back(new StunChampionEffect());
    primaryEffs_fireBomb.push_back(new DrawEffect(1));
    
    std::vector<Effect*> sacrificeEffs_fireBomb;
    sacrificeEffs_fireBomb.push_back(new AttackEffect(5));
    
    std::vector<Ability*> abilities_fireBomb;
    abilities_fireBomb.push_back(new PrimaryAbility(primaryEffs_fireBomb));
    abilities_fireBomb.push_back(new SacrificeAbility(sacrificeEffs_fireBomb));
    
    ActionCard* fireBomb = new ActionCard("Fire Bomb", 8, Faction::Guilde, "Action", {}, abilities_fireBomb);
    m_marketDeck.addCard(fireBomb);

    // 6. Hit Job (Action) - Coût: 4
    // +7 Combat
    // Guild Ally: Stun target champion
    std::vector<Effect*> primaryEffs_hitJob;
    primaryEffs_hitJob.push_back(new AttackEffect(7));
    
    std::vector<Effect*> allyEffs_hitJob;
    allyEffs_hitJob.push_back(new StunChampionEffect());
    
    std::vector<Ability*> abilities_hitJob;
    abilities_hitJob.push_back(new PrimaryAbility(primaryEffs_hitJob));
    abilities_hitJob.push_back(new AllyAbility(allyEffs_hitJob));
    
    ActionCard* hitJob = new ActionCard("Hit Job", 4, Faction::Guilde, "Action", {}, abilities_hitJob);
    m_marketDeck.addCard(hitJob);

    // 7. Intimidation (Action) - Coût: 2 (×2)
    // +5 Combat
    // Guild Ally: +2 Gold
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> primaryEffs_intimidation;
        primaryEffs_intimidation.push_back(new AttackEffect(5));
        
        std::vector<Effect*> allyEffs_intimidation;
        allyEffs_intimidation.push_back(new GoldEffect(2));
        
        std::vector<Ability*> abilities_intimidation;
        abilities_intimidation.push_back(new PrimaryAbility(primaryEffs_intimidation));
        abilities_intimidation.push_back(new AllyAbility(allyEffs_intimidation));
        
        ActionCard* intimidation = new ActionCard("Intimidation", 2, Faction::Guilde, "Action", {}, abilities_intimidation);
        m_marketDeck.addCard(intimidation);
    }

    // 8. Myros, Guild Mage (Champion, Guard) - Coût: 5, Défense: 3
    // Expend: +3 Gold
    // Guild Ally: +4 Combat
    std::vector<Effect*> activateEffs_myros;
    activateEffs_myros.push_back(new GoldEffect(3));
    
    std::vector<Effect*> allyEffs_myros;
    allyEffs_myros.push_back(new AttackEffect(4));
    
    std::vector<Ability*> abilities_myros;
    abilities_myros.push_back(new ActivateAbility(activateEffs_myros));
    abilities_myros.push_back(new AllyAbility(allyEffs_myros));
    
    ChampionCard* myros = new ChampionCard("Myros, Guild Mage", 5, Faction::Guilde, "Champion", 3, true, abilities_myros);
    m_marketDeck.addCard(myros);

    // 9. Parov, the Enforcer (Champion, Guard) - Coût: 5, Défense: 5
    // Expend: +3 Combat
    // Guild Ally: Draw 1
    std::vector<Effect*> activateEffs_parov;
    activateEffs_parov.push_back(new AttackEffect(3));
    
    std::vector<Effect*> allyEffs_parov;
    allyEffs_parov.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_parov;
    abilities_parov.push_back(new ActivateAbility(activateEffs_parov));
    abilities_parov.push_back(new AllyAbility(allyEffs_parov));
    
    ChampionCard* parov = new ChampionCard("Parov, the Enforcer", 5, Faction::Guilde, "Champion", 5, true, abilities_parov);
    m_marketDeck.addCard(parov);

    // 10. Profit (Action) - Coût: 1 (×3)
    // +2 Gold
    // Guild Ally: +4 Combat
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_profit;
        primaryEffs_profit.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs_profit;
        allyEffs_profit.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities_profit;
        abilities_profit.push_back(new PrimaryAbility(primaryEffs_profit));
        abilities_profit.push_back(new AllyAbility(allyEffs_profit));
        
        ActionCard* profit = new ActionCard("Profit", 1, Faction::Guilde, "Action", {}, abilities_profit);
        m_marketDeck.addCard(profit);
    }

    // 11. Rake, Master Assassin (Champion) - Coût: 7, Défense: 7
    // Expend: +4 Combat, You may stun target champion
    std::vector<Effect*> activateEffs_rake;
    activateEffs_rake.push_back(new AttackEffect(4));
    activateEffs_rake.push_back(new StunChampionEffect());
    
    std::vector<Ability*> abilities_rake;
    abilities_rake.push_back(new ActivateAbility(activateEffs_rake));
    
    ChampionCard* rake = new ChampionCard("Rake, Master Assassin", 7, Faction::Guilde, "Champion", 7, false, abilities_rake);
    m_marketDeck.addCard(rake);

    // 12. Rasmus, the Smuggler (Champion) - Coût: 4, Défense: 5
    // Expend: +2 Gold
    // Guild Ally: Put the next card you acquire this turn on top of your deck
    std::vector<Effect*> activateEffs_rasmus;
    activateEffs_rasmus.push_back(new GoldEffect(2));
    
    std::vector<Effect*> allyEffs_rasmus;
    allyEffs_rasmus.push_back(new PutNextCardOnTopEffect("Any")); // Toutes les cartes
    
    std::vector<Ability*> abilities_rasmus;
    abilities_rasmus.push_back(new ActivateAbility(activateEffs_rasmus));
    abilities_rasmus.push_back(new AllyAbility(allyEffs_rasmus));
    
    ChampionCard* rasmus = new ChampionCard("Rasmus, the Smuggler", 4, Faction::Guilde, "Champion", 5, false, abilities_rasmus);
    m_marketDeck.addCard(rasmus);

    // 13. Smash and Grab (Action) - Coût: 6
    // +6 Combat
    // You may put a card from your discard pile on top of your deck
    std::vector<Effect*> primaryEffs_smash;
    primaryEffs_smash.push_back(new AttackEffect(6));
    primaryEffs_smash.push_back(new PutFromDiscardOnTopEffect(true)); // Optional = true
    
    std::vector<Ability*> abilities_smash;
    abilities_smash.push_back(new PrimaryAbility(primaryEffs_smash));
    
    ActionCard* smash = new ActionCard("Smash and Grab", 6, Faction::Guilde, "Action", {}, abilities_smash);
    m_marketDeck.addCard(smash);

    // 14. Street Thug (Champion) - Coût: 3, Défense: 4 (×2)
    // Expend: +1 Gold OR +2 Combat
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_streetThug;
        activateEffs_streetThug.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new AttackEffect(2), "+2 Combat"
        ));
        
        std::vector<Ability*> abilities_streetThug;
        abilities_streetThug.push_back(new ActivateAbility(activateEffs_streetThug));
        
        ChampionCard* streetThug = new ChampionCard("Street Thug", 3, Faction::Guilde, "Champion", 4, false, abilities_streetThug);
        m_marketDeck.addCard(streetThug);
    }

    // —————————————————————
    // NECROS
    // —————————————————————

    // 1. Cult Priest (Champion) - Coût: 3, Défense: 4 (×2)
    // Expend: +1 Gold OR +1 Combat
    // Necros Ally: +4 Combat
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_cultPriest;
        activateEffs_cultPriest.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new AttackEffect(1), "+1 Combat"
        ));
        
        std::vector<Effect*> allyEffs_cultPriest;
        allyEffs_cultPriest.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities_cultPriest;
        abilities_cultPriest.push_back(new ActivateAbility(activateEffs_cultPriest));
        abilities_cultPriest.push_back(new AllyAbility(allyEffs_cultPriest));
        
        ChampionCard* cultPriest = new ChampionCard("Cult Priest", 3, Faction::Necros, "Champion", 4, false, abilities_cultPriest);
        m_marketDeck.addCard(cultPriest);
    }

    // 2. Dark Energy (Action) - Coût: 4
    // +7 Combat
    // Necros Ally: Draw 1
    std::vector<Effect*> primaryEffs_darkEnergy;
    primaryEffs_darkEnergy.push_back(new AttackEffect(7));
    
    std::vector<Effect*> allyEffs_darkEnergy;
    allyEffs_darkEnergy.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_darkEnergy;
    abilities_darkEnergy.push_back(new PrimaryAbility(primaryEffs_darkEnergy));
    abilities_darkEnergy.push_back(new AllyAbility(allyEffs_darkEnergy));
    
    ActionCard* darkEnergy = new ActionCard("Dark Energy", 4, Faction::Necros, "Action", {}, abilities_darkEnergy);
    m_marketDeck.addCard(darkEnergy);

    // 3. Dark Reward (Action) - Coût: 5
    // +3 Gold
    // You may sacrifice a card in your hand or discard pile
    // Necros Ally: +6 Combat
    std::vector<Effect*> primaryEffs_darkReward;
    primaryEffs_darkReward.push_back(new GoldEffect(3));
    primaryEffs_darkReward.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
    
    std::vector<Effect*> allyEffs_darkReward;
    allyEffs_darkReward.push_back(new AttackEffect(6));
    
    std::vector<Ability*> abilities_darkReward;
    abilities_darkReward.push_back(new PrimaryAbility(primaryEffs_darkReward));
    abilities_darkReward.push_back(new AllyAbility(allyEffs_darkReward));
    
    ActionCard* darkReward = new ActionCard("Dark Reward", 5, Faction::Necros, "Action", {}, abilities_darkReward);
    m_marketDeck.addCard(darkReward);

    // 4. Death Cultist (Champion, Guard) - Coût: 2, Défense: 3 (×2)
    // Expend: +2 Combat
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_deathCultist;
        activateEffs_deathCultist.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities_deathCultist;
        abilities_deathCultist.push_back(new ActivateAbility(activateEffs_deathCultist));
        
        ChampionCard* deathCultist = new ChampionCard("Death Cultist", 2, Faction::Necros, "Champion", 3, true, abilities_deathCultist);
        m_marketDeck.addCard(deathCultist);
    }

    // 5. Death Touch (Action) - Coût: 1 (×3)
    // +2 Combat
    // You may sacrifice a card in your hand or discard pile
    // Necros Ally: +2 Combat
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_deathTouch;
        primaryEffs_deathTouch.push_back(new AttackEffect(2));
        primaryEffs_deathTouch.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs_deathTouch;
        allyEffs_deathTouch.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities_deathTouch;
        abilities_deathTouch.push_back(new PrimaryAbility(primaryEffs_deathTouch));
        abilities_deathTouch.push_back(new AllyAbility(allyEffs_deathTouch));
        
        ActionCard* deathTouch = new ActionCard("Death Touch", 1, Faction::Necros, "Action", {}, abilities_deathTouch);
        m_marketDeck.addCard(deathTouch);
    }

    // 6. Rayla, Endweaver (Champion) - Coût: 4, Défense: 4
    // Expend: +3 Combat
    // Necros Ally: Draw 1
    std::vector<Effect*> activateEffs_rayla;
    activateEffs_rayla.push_back(new AttackEffect(3));
    
    std::vector<Effect*> allyEffs_rayla;
    allyEffs_rayla.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_rayla;
    abilities_rayla.push_back(new ActivateAbility(activateEffs_rayla));
    abilities_rayla.push_back(new AllyAbility(allyEffs_rayla));
    
    ChampionCard* rayla = new ChampionCard("Rayla, Endweaver", 4, Faction::Necros, "Champion", 4, false, abilities_rayla);
    m_marketDeck.addCard(rayla);

    // 7. Influence (Action) - Coût: 2 (×3)
    // +3 Gold
    // Sacrifice: +3 Combat
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_influence;
        primaryEffs_influence.push_back(new GoldEffect(3));
        
        std::vector<Effect*> sacrificeEffs_influence;
        sacrificeEffs_influence.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities_influence;
        abilities_influence.push_back(new PrimaryAbility(primaryEffs_influence));
        abilities_influence.push_back(new SacrificeAbility(sacrificeEffs_influence));
        
        ActionCard* influence = new ActionCard("Influence", 2, Faction::Necros, "Action", {}, abilities_influence);
        m_marketDeck.addCard(influence);
    }

    // 8. Krythos, Master Vampire (Champion) - Coût: 7, Défense: 6
    // Expend: +3 Combat
    // You may sacrifice a card in your hand or discard pile. If you do, gain an additional +3 Combat
    std::vector<Effect*> activateEffs_krythos;
    activateEffs_krythos.push_back(new AttackEffect(3));
    activateEffs_krythos.push_back(new OptionalSacrificeEffect(1, 1, true, new AttackEffect(3)));
    
    std::vector<Ability*> abilities_krythos;
    abilities_krythos.push_back(new ActivateAbility(activateEffs_krythos));
    
    ChampionCard* krythos = new ChampionCard("Krythos, Master Vampire", 7, Faction::Necros, "Champion", 6, false, abilities_krythos);
    m_marketDeck.addCard(krythos);

    // 9. Life Drain (Action) - Coût: 6
    // +8 Combat
    // You may sacrifice a card in your hand or discard pile
    // Necros Ally: Draw 1
    std::vector<Effect*> primaryEffs_lifeDrain;
    primaryEffs_lifeDrain.push_back(new AttackEffect(8));
    primaryEffs_lifeDrain.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
    
    std::vector<Effect*> allyEffs_lifeDrain;
    allyEffs_lifeDrain.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_lifeDrain;
    abilities_lifeDrain.push_back(new PrimaryAbility(primaryEffs_lifeDrain));
    abilities_lifeDrain.push_back(new AllyAbility(allyEffs_lifeDrain));
    
    ActionCard* lifeDrain = new ActionCard("Life Drain", 6, Faction::Necros, "Action", {}, abilities_lifeDrain);
    m_marketDeck.addCard(lifeDrain);

    // 10. Lys, the Unseen (Champion, Guard) - Coût: 6, Défense: 5
    // Expend: +2 Combat
    // You may sacrifice a card in your hand or discard pile. If you do, gain an additional +2 Combat
    std::vector<Effect*> activateEffs_lys;
    activateEffs_lys.push_back(new AttackEffect(2));
    activateEffs_lys.push_back(new OptionalSacrificeEffect(1, 1, true, new AttackEffect(2)));
    
    std::vector<Ability*> abilities_lys;
    abilities_lys.push_back(new ActivateAbility(activateEffs_lys));
    
    ChampionCard* lys = new ChampionCard("Lys, the Unseen", 6, Faction::Necros, "Champion", 5, true, abilities_lys);
    m_marketDeck.addCard(lys);

    // 11. The Rot (Action) - Coût: 3 (×2)
    // +4 Combat
    // You may sacrifice a card in your hand or discard pile
    // Necros Ally: +3 Combat
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> primaryEffs_rot;
        primaryEffs_rot.push_back(new AttackEffect(4));
        primaryEffs_rot.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs_rot;
        allyEffs_rot.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities_rot;
        abilities_rot.push_back(new PrimaryAbility(primaryEffs_rot));
        abilities_rot.push_back(new AllyAbility(allyEffs_rot));
        
        ActionCard* rot = new ActionCard("The Rot", 3, Faction::Necros, "Action", {}, abilities_rot);
        m_marketDeck.addCard(rot);
    }

    // 12. Tyrannor, the Devourer (Champion, Guard) - Coût: 8, Défense: 6
    // Expend: +4 Combat
    // You may sacrifice up to two cards in your hand and/or discard pile
    // Necros Ally: Draw 1
    std::vector<Effect*> activateEffs_tyrannor;
    activateEffs_tyrannor.push_back(new AttackEffect(4));
    activateEffs_tyrannor.push_back(new OptionalSacrificeEffect(1, 2, true, nullptr)); // up to 2 cards
    
    std::vector<Effect*> allyEffs_tyrannor;
    allyEffs_tyrannor.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_tyrannor;
    abilities_tyrannor.push_back(new ActivateAbility(activateEffs_tyrannor));
    abilities_tyrannor.push_back(new AllyAbility(allyEffs_tyrannor));
    
    ChampionCard* tyrannor = new ChampionCard("Tyrannor, the Devourer", 8, Faction::Necros, "Champion", 6, true, abilities_tyrannor);
    m_marketDeck.addCard(tyrannor);

    // 13. Varrick, the Necromancer (Champion) - Coût: 5, Défense: 3
    // Expend: Take a champion from your discard pile and put it on top of your deck
    // Necros Ally: Draw 1
    std::vector<Effect*> activateEffs_varrick;
    // TODO COMPLEXE: Nécessite PutChampionFromDiscardOnTopEffect()
    // Cet effet doit:
    // 1. Filtrer les Champions dans la défausse
    // 2. Afficher les Champions disponibles
    // 3. Laisser le joueur en choisir un
    // 4. Retirer le Champion de la défausse
    // 5. Le placer sur le dessus du deck
    // Requiert: Nouvelle classe PutChampionFromDiscardOnTopEffect()
    
    std::vector<Effect*> allyEffs_varrick;
    allyEffs_varrick.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_varrick;
    abilities_varrick.push_back(new ActivateAbility(activateEffs_varrick));
    abilities_varrick.push_back(new AllyAbility(allyEffs_varrick));
    
    ChampionCard* varrick = new ChampionCard("Varrick, the Necromancer", 5, Faction::Necros, "Champion", 3, false, abilities_varrick);
    m_marketDeck.addCard(varrick);

    // —————————————————————
    // WILD
    // —————————————————————

    // 1. Broelyn, Loreweaver (Champion) - Coût: 4, Défense: 6
    // Expend: +2 Gold
    // Wild Ally: Target opponent discards a card
    std::vector<Effect*> activateEffs_broelyn;
    activateEffs_broelyn.push_back(new GoldEffect(2));
    
    std::vector<Effect*> allyEffs_broelyn;
    allyEffs_broelyn.push_back(new DiscardOpponentEffect(1));
    
    std::vector<Ability*> abilities_broelyn;
    abilities_broelyn.push_back(new ActivateAbility(activateEffs_broelyn));
    abilities_broelyn.push_back(new AllyAbility(allyEffs_broelyn));
    
    ChampionCard* broelyn = new ChampionCard("Broelyn, Loreweaver", 4, Faction::Sauvage, "Champion", 6, false, abilities_broelyn);
    m_marketDeck.addCard(broelyn);

    // 2. Cron, the Berserker (Champion) - Coût: 6, Défense: 6
    // Expend: +5 Combat
    // Wild Ally: Draw 1
    std::vector<Effect*> activateEffs_cron;
    activateEffs_cron.push_back(new AttackEffect(5));
    
    std::vector<Effect*> allyEffs_cron;
    allyEffs_cron.push_back(new DrawEffect(1));
    
    std::vector<Ability*> abilities_cron;
    abilities_cron.push_back(new ActivateAbility(activateEffs_cron));
    abilities_cron.push_back(new AllyAbility(allyEffs_cron));
    
    ChampionCard* cron = new ChampionCard("Cron, the Berserker", 6, Faction::Sauvage, "Champion", 6, false, abilities_cron);
    m_marketDeck.addCard(cron);

    // 3. Dire Wolf (Champion, Guard) - Coût: 5, Défense: 5
    // Expend: +3 Combat
    // Wild Ally: +4 Combat
    std::vector<Effect*> activateEffs_direWolf;
    activateEffs_direWolf.push_back(new AttackEffect(3));
    
    std::vector<Effect*> allyEffs_direWolf;
    allyEffs_direWolf.push_back(new AttackEffect(4));
    
    std::vector<Ability*> abilities_direWolf;
    abilities_direWolf.push_back(new ActivateAbility(activateEffs_direWolf));
    abilities_direWolf.push_back(new AllyAbility(allyEffs_direWolf));
    
    ChampionCard* direWolf = new ChampionCard("Dire Wolf", 5, Faction::Sauvage, "Champion", 5, true, abilities_direWolf);
    m_marketDeck.addCard(direWolf);

    // 4. Elven Curse (Action) - Coût: 3 (×2)
    // +6 Combat, Target opponent discards a card
    // Wild Ally: +3 Combat
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> primaryEffs_elvenCurse;
        primaryEffs_elvenCurse.push_back(new AttackEffect(6));
        primaryEffs_elvenCurse.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> allyEffs_elvenCurse;
        allyEffs_elvenCurse.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities_elvenCurse;
        abilities_elvenCurse.push_back(new PrimaryAbility(primaryEffs_elvenCurse));
        abilities_elvenCurse.push_back(new AllyAbility(allyEffs_elvenCurse));
        
        ActionCard* elvenCurse = new ActionCard("Elven Curse", 3, Faction::Sauvage, "Action", {}, abilities_elvenCurse);
        m_marketDeck.addCard(elvenCurse);
    }

    // 5. Elven Gift (Action) - Coût: 2 (×3)
    // +2 Gold
    // You may draw a card. If you do, discard a card
    // Wild Ally: +4 Combat
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_elvenGift;
        primaryEffs_elvenGift.push_back(new GoldEffect(2));
        primaryEffs_elvenGift.push_back(new DrawThenDiscardEffect(1, 1, true)); // Optional: may draw/discard
        
        std::vector<Effect*> allyEffs_elvenGift;
        allyEffs_elvenGift.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities_elvenGift;
        abilities_elvenGift.push_back(new PrimaryAbility(primaryEffs_elvenGift));
        abilities_elvenGift.push_back(new AllyAbility(allyEffs_elvenGift));
        
        ActionCard* elvenGift = new ActionCard("Elven Gift", 2, Faction::Sauvage, "Action", {}, abilities_elvenGift);
        m_marketDeck.addCard(elvenGift);
    }

    // 6. Grak, Storm Giant (Champion, Guard) - Coût: 8, Défense: 7
    // Expend: +6 Combat
    // You may draw a card. If you do, discard a card
    // Wild Ally: Draw a card, then discard a card
    std::vector<Effect*> activateEffs_grak;
    activateEffs_grak.push_back(new AttackEffect(6));
    activateEffs_grak.push_back(new DrawThenDiscardEffect(1, 1, true)); // Optional
    
    std::vector<Effect*> allyEffs_grak;
    allyEffs_grak.push_back(new DrawThenDiscardEffect(1, 1, false)); // Not optional
    
    std::vector<Ability*> abilities_grak;
    abilities_grak.push_back(new ActivateAbility(activateEffs_grak));
    abilities_grak.push_back(new AllyAbility(allyEffs_grak));
    
    ChampionCard* grak = new ChampionCard("Grak, Storm Giant", 8, Faction::Sauvage, "Champion", 7, true, abilities_grak);
    m_marketDeck.addCard(grak);

    // 7. Nature's Bounty (Action) - Coût: 4
    // +4 Gold
    // Wild Ally: Target opponent discards a card
    // Sacrifice: +4 Combat
    std::vector<Effect*> primaryEffs_nature;
    primaryEffs_nature.push_back(new GoldEffect(4));
    
    std::vector<Effect*> allyEffs_nature;
    allyEffs_nature.push_back(new DiscardOpponentEffect(1));
    
    std::vector<Effect*> sacrificeEffs_nature;
    sacrificeEffs_nature.push_back(new AttackEffect(4));
    
    std::vector<Ability*> abilities_nature;
    abilities_nature.push_back(new PrimaryAbility(primaryEffs_nature));
    abilities_nature.push_back(new AllyAbility(allyEffs_nature));
    abilities_nature.push_back(new SacrificeAbility(sacrificeEffs_nature));
    
    ActionCard* nature = new ActionCard("Nature's Bounty", 4, Faction::Sauvage, "Action", {}, abilities_nature);
    m_marketDeck.addCard(nature);

    // 8. Orc Grunt (Champion, Guard) - Coût: 3, Défense: 3 (×2)
    // Expend: +2 Combat
    // Wild Ally: Draw 1
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_orcGrunt;
        activateEffs_orcGrunt.push_back(new AttackEffect(2));
        
        std::vector<Effect*> allyEffs_orcGrunt;
        allyEffs_orcGrunt.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities_orcGrunt;
        abilities_orcGrunt.push_back(new ActivateAbility(activateEffs_orcGrunt));
        abilities_orcGrunt.push_back(new AllyAbility(allyEffs_orcGrunt));
        
        ChampionCard* orcGrunt = new ChampionCard("Orc Grunt", 3, Faction::Sauvage, "Champion", 3, true, abilities_orcGrunt);
        m_marketDeck.addCard(orcGrunt);
    }

    // 9. Rampage (Action) - Coût: 6
    // +6 Combat
    // You may draw up to two cards, then discard that many cards
    std::vector<Effect*> primaryEffs_rampage;
    primaryEffs_rampage.push_back(new AttackEffect(6));
    primaryEffs_rampage.push_back(new DrawThenDiscardEffect(2, 2, true)); // Optional: draw up to 2, discard that many
    
    std::vector<Ability*> abilities_rampage;
    abilities_rampage.push_back(new PrimaryAbility(primaryEffs_rampage));
    
    ActionCard* rampage = new ActionCard("Rampage", 6, Faction::Sauvage, "Action", {}, abilities_rampage);
    m_marketDeck.addCard(rampage);

    // 10. Torgen Rocksplitter (Champion, Guard) - Coût: 7, Défense: 7
    // Expend: +4 Combat, Target opponent discards a card
    std::vector<Effect*> activateEffs_torgen;
    activateEffs_torgen.push_back(new AttackEffect(4));
    activateEffs_torgen.push_back(new DiscardOpponentEffect(1));
    
    std::vector<Ability*> abilities_torgen;
    abilities_torgen.push_back(new ActivateAbility(activateEffs_torgen));
    
    ChampionCard* torgen = new ChampionCard("Torgen Rocksplitter", 7, Faction::Sauvage, "Champion", 7, true, abilities_torgen);
    m_marketDeck.addCard(torgen);

    // 11. Spark (Action) - Coût: 1 (×3)
    // +3 Combat, Target opponent discards a card
    // Wild Ally: +2 Combat
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> primaryEffs_spark;
        primaryEffs_spark.push_back(new AttackEffect(3));
        primaryEffs_spark.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> allyEffs_spark;
        allyEffs_spark.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities_spark;
        abilities_spark.push_back(new PrimaryAbility(primaryEffs_spark));
        abilities_spark.push_back(new AllyAbility(allyEffs_spark));
        
        ActionCard* spark = new ActionCard("Spark", 1, Faction::Sauvage, "Action", {}, abilities_spark);
        m_marketDeck.addCard(spark);
    }

    // 12. Wolf Form (Action) - Coût: 5
    // +8 Combat, Target opponent discards a card
    // Sacrifice: Target opponent discards a card
    std::vector<Effect*> primaryEffs_wolfForm;
    primaryEffs_wolfForm.push_back(new AttackEffect(8));
    primaryEffs_wolfForm.push_back(new DiscardOpponentEffect(1));
    
    std::vector<Effect*> sacrificeEffs_wolfForm;
    sacrificeEffs_wolfForm.push_back(new DiscardOpponentEffect(1));
    
    std::vector<Ability*> abilities_wolfForm;
    abilities_wolfForm.push_back(new PrimaryAbility(primaryEffs_wolfForm));
    abilities_wolfForm.push_back(new SacrificeAbility(sacrificeEffs_wolfForm));
    
    ActionCard* wolfForm = new ActionCard("Wolf Form", 5, Faction::Sauvage, "Action", {}, abilities_wolfForm);
    m_marketDeck.addCard(wolfForm);

    // 13. Wolf Shaman (Champion) - Coût: 2, Défense: 4 (×2)
    // Expend: +2 Combat
    // +1 Combat for each other Wild card you have in play
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> activateEffs_wolfShaman;
        activateEffs_wolfShaman.push_back(new AttackEffect(2));
        activateEffs_wolfShaman.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::FactionCardCount, Faction::Sauvage, false));
        
        std::vector<Ability*> abilities_wolfShaman;
        abilities_wolfShaman.push_back(new ActivateAbility(activateEffs_wolfShaman));
        
        ChampionCard* wolfShaman = new ChampionCard("Wolf Shaman", 2, Faction::Sauvage, "Champion", 4, false, abilities_wolfShaman);
        m_marketDeck.addCard(wolfShaman);
    }

    // —————————————————————
    // DECKS PERSONNELS
    // —————————————————————
    // Gold (×28) - Coût: 0
    // +1 Gold
    for (int i = 0; i < 28; ++i) {
        std::vector<Effect*> primaryEffs_gold;
        primaryEffs_gold.push_back(new GoldEffect(1));
        
        std::vector<Ability*> abilities_gold;
        abilities_gold.push_back(new PrimaryAbility(primaryEffs_gold));
        
        ItemCard* gold = new ItemCard("Gold", 0, Faction::None, "Item", {}, abilities_gold);
        m_marketDeck.addCard(gold);
    }

    // Shortsword (×4) - Coût: 0
    // +2 Combat
    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> primaryEffs_sword;
        primaryEffs_sword.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities_sword;
        abilities_sword.push_back(new PrimaryAbility(primaryEffs_sword));
        
        ItemCard* sw = new ItemCard("Shortsword", 0, Faction::None, "Item", {}, abilities_sword);
        m_marketDeck.addCard(sw);
    }

    // Dagger (×4) - Coût: 0
    // +1 Combat
    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> primaryEffs_dagger;
        primaryEffs_dagger.push_back(new AttackEffect(1));
        
        std::vector<Ability*> abilities_dagger;
        abilities_dagger.push_back(new PrimaryAbility(primaryEffs_dagger));
        
        ItemCard* dg = new ItemCard("Dagger", 0, Faction::None, "Item", {}, abilities_dagger);
        m_marketDeck.addCard(dg);
    }

    // Ruby (×4) - Coût: 1
    // +2 Gold
    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> primaryEffs_ruby;
        primaryEffs_ruby.push_back(new GoldEffect(2));
        
        std::vector<Ability*> abilities_ruby;
        abilities_ruby.push_back(new PrimaryAbility(primaryEffs_ruby));
        
        ItemCard* ruby = new ItemCard("Ruby", 1, Faction::None, "Item", {}, abilities_ruby);
        m_marketDeck.addCard(ruby);
    }

// Mélanger le deck du marché
    m_marketDeck.shuffle();

    // Initialiser les 5 cartes visibles
    for (int i = 0; i < 5; ++i) {
        if (!m_marketDeck.isEmpty()) {
            Card* card = m_marketDeck.draw();
            m_visibleCards.push_back(card);
        }
    }

    // Initialiser les Gemmes de Feu
    initializeFireGems();

    std::cout << "Marché initialisé: " << m_visibleCards.size() 
         << " cartes visibles, " << m_marketDeck.size() 
         << " dans la pioche, " << m_fireGems.size() 
         << " Gemmes de Feu" << std::endl;
}

    // Getters
    std::vector<Card*>& Market::getVisibleCards() { return m_visibleCards; }
    Deck& Market::getMarketDeck() { return m_marketDeck; }
    std::vector<ItemCard*>& Market::getFireGems() { return m_fireGems; }
    std::vector<Card*>& Market::getSacrificeZone() { return m_sacrificeZone; }

    int Market::getVisibleCardsCount() const {
        return m_visibleCards.size();
    }

    void Market::displayMarket() const {
        std::cout << "\n=== MARCHÉ ===" << std::endl;
        std::cout << "Cartes visibles (" << m_visibleCards.size() << "):" << std::endl;
        int index = 1;
        for (auto& card : m_visibleCards) {
            std::cout << index << ". " << card->getName()<< " (" <<card->getCost()<< " or)" << std::endl;
            index++;
        }
        std::cout << "Gemmes de Feu: " << m_fireGems.size() << " disponibles" << std::endl;
    }