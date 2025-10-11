#include "Market.h"
#include <iostream>
#include <vector>
#include "ActionCard.h"
#include "ItemCard.h"
#include "ChampionCard.h"
#include "Effect.h"
#include "GoldEffect.h"
#include "AttackEffect.h"
#include "HealEffect.h"
#include "DrawEffect.h"
#include "SacrificeEffect.h"
#include "Ability.h"
#include "AllyAbility.h"
#include "SacrificeAbility.h"



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
        ItemCard fireGem = m_fireGems.front();
        m_fireGems.pop_front();
        
        // Ajouter à la défausse du joueur
        player.getDiscardPile().add(&fireGem);
        
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
    for (int i = 0; i < 16; ++i) {
        std::vector<Effect*> fireGemEff;
        addEffect<GoldEffect>(fireGemEff, 2);
        addEffect<SacrificeEffect>(fireGemEff, 1);
        ItemCard fireGem("Gemme de Feu", 2, Faction::None, "Item", fireGemEff);
        m_marketDeck.addCard(&fireGem);
    }
}

void Market::initializeBaseSet() {
    std::cout << "Initialisation du marché (Base Set)..." << std::endl;

    // —————————————————————
    // IMPERIAL
    // —————————————————————

    // Arkus, Imperial Dragon
    std::vector<Effect*> effs_arkus;
    addEffect<AttackEffect>(effs_arkus, 5);
    addEffect<DrawEffect>(effs_arkus, 1);
    std::list<Ability*> abilities_arkus;
    abilities_arkus.push_back(new AllyAbility());
    ChampionCard arkus("Arkus, Imperial Dragon", 8, Faction::Imperial, "Champion", 6, true, false, abilities_arkus);
    m_marketDeck.addCard(&arkus);

    // Close Ranks
    std::vector<Effect*> effs_closeRanks;
    addEffect<AttackEffect>(effs_closeRanks, 5);
    ActionCard closeRanks("Close Ranks", 3, Faction::Imperial, "Action", effs_closeRanks);
    m_marketDeck.addCard(&closeRanks);

    // Command
    std::vector<Effect*> effs_command;
    addEffect<GoldEffect>(effs_command, 2);
    addEffect<AttackEffect>(effs_command, 3);
    addEffect<HealEffect>(effs_command, 4);
    addEffect<DrawEffect>(effs_command, 1);
    ActionCard command("Command", 5, Faction::Imperial, "Action", effs_command);
    m_marketDeck.addCard(&command);

    // Darian, War Mage
    std::vector<Effect*> effs_darian;
    addEffect<AttackEffect>(effs_darian, 3);
    ChampionCard darian("Darian, War Mage", 4, Faction::Imperial, "Champion", 5, false, false, {});
    m_marketDeck.addCard(&darian);

    // Domination
    std::vector<Effect*> effs_domination;
    addEffect<AttackEffect>(effs_domination, 6);
    addEffect<HealEffect>(effs_domination, 6);
    addEffect<DrawEffect>(effs_domination, 1);
    ActionCard domination("Domination", 7, Faction::Imperial, "Action", effs_domination);
    m_marketDeck.addCard(&domination);

    // Cristov, the Just
    std::vector<Effect*> effs_cristov;
    addEffect<AttackEffect>(effs_cristov, 2);
    addEffect<HealEffect>(effs_cristov, 3);
    std::list<Ability*> abilities_cristov;
    abilities_cristov.push_back(new AllyAbility());
    ChampionCard cristov("Cristov, the Just", 5, Faction::Imperial, "Champion", 5, true, false, abilities_cristov);
    m_marketDeck.addCard(&cristov);

    // Kraka, High Priest
    std::vector<Effect*> effs_kraka;
    addEffect<HealEffect>(effs_kraka, 2);
    addEffect<DrawEffect>(effs_kraka, 1);
    ChampionCard kraka("Kraka, High Priest", 6, Faction::Imperial, "Champion", 6, false, false, {});
    m_marketDeck.addCard(&kraka);

    // Man-at-Arms (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_man;
        addEffect<AttackEffect>(effs_man, 2);
        ChampionCard man("Man-at-Arms", 3, Faction::Imperial, "Champion", 4, true, false, {});
        m_marketDeck.addCard(&man);
    }

    // Master Weyan
    std::vector<Effect*> effs_masterWeyan;
    addEffect<AttackEffect>(effs_masterWeyan, 3);
    ChampionCard masterWeyan("Master Weyan", 4, Faction::Imperial, "Champion", 4, true, false, {});
    m_marketDeck.addCard(&masterWeyan);

    // Rally the Troops
    std::vector<Effect*> effs_rally;
    addEffect<AttackEffect>(effs_rally, 5);
    addEffect<HealEffect>(effs_rally, 5);
    ActionCard rally("Rally the Troops", 4, Faction::Imperial, "Action", effs_rally);
    m_marketDeck.addCard(&rally);

    // Recruit (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_recruit;
        addEffect<GoldEffect>(effs_recruit, 2);
        addEffect<HealEffect>(effs_recruit, 3);
        ActionCard recruit("Recruit", 2, Faction::Imperial, "Action", effs_recruit);
        m_marketDeck.addCard(&recruit);
    }

    // Tithe Priest (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_tithe;
        addEffect<GoldEffect>(effs_tithe, 1);
        ChampionCard tithe("Tithe Priest", 2, Faction::Imperial, "Champion", 3, false, false, {});
        m_marketDeck.addCard(&tithe);
    }

    // Taxation (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_taxation;
        addEffect<GoldEffect>(effs_taxation, 2);
        ActionCard taxation("Taxation", 1, Faction::Imperial, "Action", effs_taxation);
        m_marketDeck.addCard(&taxation);
    }

    // Word of Power
    std::vector<Effect*> effs_word;
    addEffect<DrawEffect>(effs_word, 2);
    ActionCard word("Word of Power", 6, Faction::Imperial, "Action", effs_word);
    m_marketDeck.addCard(&word);

    // —————————————————————
    // GUILD
    // —————————————————————

    // Borg, Ogre Mercenary
    std::vector<Effect*> effs_borg;
    addEffect<AttackEffect>(effs_borg, 4);
    ChampionCard borg("Borg, Ogre Mercenary", 6, Faction::Guilde, "Champion", 6, true, false, {});
    m_marketDeck.addCard(&borg);

    // Bribe (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_bribe;
        addEffect<GoldEffect>(effs_bribe, 3);
        ActionCard bribe("Bribe", 3, Faction::Guilde, "Action", effs_bribe);
        m_marketDeck.addCard(&bribe);
    }

    // Death Threat
    std::vector<Effect*> effs_deathThreat;
    addEffect<AttackEffect>(effs_deathThreat, 1);
    addEffect<DrawEffect>(effs_deathThreat, 1);
    ActionCard deathThreat("Death Threat", 3, Faction::Guilde, "Action", effs_deathThreat);
    m_marketDeck.addCard(&deathThreat);

    // Deception
    std::vector<Effect*> effs_deception;
    addEffect<GoldEffect>(effs_deception, 2);
    addEffect<DrawEffect>(effs_deception, 1);
    ActionCard deception("Deception", 5, Faction::Guilde, "Action", effs_deception);
    m_marketDeck.addCard(&deception);

    // Fire Bomb
    std::vector<Effect*> effs_fireBomb;
    addEffect<AttackEffect>(effs_fireBomb, 8);
    ActionCard fireBomb("Fire Bomb", 8, Faction::Guilde, "Action", effs_fireBomb);
    m_marketDeck.addCard(&fireBomb);

    // Hit Job
    std::vector<Effect*> effs_hitJob;
    addEffect<AttackEffect>(effs_hitJob, 7);
    ActionCard hitJob("Hit Job", 4, Faction::Guilde, "Action", effs_hitJob);
    m_marketDeck.addCard(&hitJob);

    // Intimidation (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_intimidation;
        addEffect<AttackEffect>(effs_intimidation, 5);
        ActionCard intimidation("Intimidation", 2, Faction::Guilde, "Action", effs_intimidation);
        m_marketDeck.addCard(&intimidation);
    }

    // Myros, Guild Mage
    std::vector<Effect*> effs_myros;
    addEffect<GoldEffect>(effs_myros, 3);
    ChampionCard myros("Myros, Guild Mage", 5, Faction::Guilde, "Champion", 3, true, false, {});
    m_marketDeck.addCard(&myros);

    // Parov, the Enforcer
    std::vector<Effect*> effs_parov;
    addEffect<AttackEffect>(effs_parov, 3);
    ChampionCard parov("Parov, the Enforcer", 5, Faction::Guilde, "Champion", 5, true, false, {});
    m_marketDeck.addCard(&parov);

    // Profit (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_profit;
        addEffect<GoldEffect>(effs_profit, 2);
        ActionCard profit("Profit", 1, Faction::Guilde, "Action", effs_profit);
        m_marketDeck.addCard(&profit);
    }

    // Rake, Master Assassin
    std::vector<Effect*> effs_rake;
    addEffect<AttackEffect>(effs_rake, 4);
    ChampionCard rake("Rake, Master Assassin", 7, Faction::Guilde, "Champion", 7, false, false, {});
    m_marketDeck.addCard(&rake);

    // Rasmus, the Smuggler
    std::vector<Effect*> effs_rasmus;
    addEffect<GoldEffect>(effs_rasmus, 2);
    ChampionCard rasmus("Rasmus, the Smuggler", 4, Faction::Guilde, "Champion", 5, false, false, {});
    m_marketDeck.addCard(&rasmus);

    // Smash and Grab
    std::vector<Effect*> effs_smash;
    addEffect<AttackEffect>(effs_smash, 6);
    ActionCard smash("Smash and Grab", 6, Faction::Guilde, "Action", effs_smash);
    m_marketDeck.addCard(&smash);

    // Street Thug (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_streetThug;
        addEffect<GoldEffect>(effs_streetThug, 1);
        ChampionCard streetThug("Street Thug", 3, Faction::Guilde, "Champion", 4, false, false, {});
        m_marketDeck.addCard(&streetThug);
    }

    // —————————————————————
    // NECROS
    // —————————————————————

    // Cult Priest (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_cultPriest;
        addEffect<GoldEffect>(effs_cultPriest, 1);
        ChampionCard cultPriest("Cult Priest", 3, Faction::Necros, "Champion", 4, false, false, {});
        m_marketDeck.addCard(&cultPriest);
    }

    // Dark Energy
    std::vector<Effect*> effs_darkEnergy;
    addEffect<AttackEffect>(effs_darkEnergy, 7);
    ActionCard darkEnergy("Dark Energy", 4, Faction::Necros, "Action", effs_darkEnergy);
    m_marketDeck.addCard(&darkEnergy);

    // Dark Reward
    std::vector<Effect*> effs_darkReward;
    addEffect<GoldEffect>(effs_darkReward, 3);
    ActionCard darkReward("Dark Reward", 5, Faction::Necros, "Action", effs_darkReward);
    m_marketDeck.addCard(&darkReward);

    // Death Cultist (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_deathCultist;
        addEffect<AttackEffect>(effs_deathCultist, 2);
        ChampionCard deathCultist("Death Cultist", 2, Faction::Necros, "Champion", 3, true, false, {});
        m_marketDeck.addCard(&deathCultist);
    }

    // Death Touch (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_deathTouch;
        addEffect<AttackEffect>(effs_deathTouch, 2);
        ActionCard deathTouch("Death Touch", 1, Faction::Necros, "Action", effs_deathTouch);
        m_marketDeck.addCard(&deathTouch);
    }

    // Rayla, Endweaver
    std::vector<Effect*> effs_rayla;
    addEffect<AttackEffect>(effs_rayla, 3);
    ChampionCard rayla("Rayla, Endweaver", 4, Faction::Necros, "Champion", 4, false, false, {});
    m_marketDeck.addCard(&rayla);

    // Influence (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_influence;
        addEffect<GoldEffect>(effs_influence, 3);
        ActionCard influence("Influence", 2, Faction::Necros, "Action", effs_influence);
        m_marketDeck.addCard(&influence);
    }

    // Krythos, Master Vampire
    std::vector<Effect*> effs_krythos;
    addEffect<AttackEffect>(effs_krythos, 3);
    ChampionCard krythos("Krythos, Master Vampire", 7, Faction::Necros, "Champion", 6, false, false, {});
    m_marketDeck.addCard(&krythos);

    // Life Drain
    std::vector<Effect*> effs_lifeDrain;
    addEffect<AttackEffect>(effs_lifeDrain, 8);
    ActionCard lifeDrain("Life Drain", 6, Faction::Necros, "Action", effs_lifeDrain);
    m_marketDeck.addCard(&lifeDrain);

    // Lys, the Unseen
    std::vector<Effect*> effs_lys;
    addEffect<AttackEffect>(effs_lys, 2);
    ChampionCard lys("Lys, the Unseen", 6, Faction::Necros, "Champion", 5, true, false, {});
    m_marketDeck.addCard(&lys);

    // The Rot (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_rot;
        addEffect<AttackEffect>(effs_rot, 4);
        ActionCard rot("The Rot", 3, Faction::Necros, "Action", effs_rot);
        m_marketDeck.addCard(&rot);
    }

    // Tyrannor, the Devourer
    std::vector<Effect*> effs_tyrannor;
    addEffect<AttackEffect>(effs_tyrannor, 4);
    ChampionCard tyrannor("Tyrannor, the Devourer", 8, Faction::Necros, "Champion", 6, true, false, {});
    m_marketDeck.addCard(&tyrannor);

    // Varrick, the Necromancer
    std::vector<Effect*> effs_varrick;
    ChampionCard varrick("Varrick, the Necromancer", 5, Faction::Necros, "Champion", 3, false, false, {});
    m_marketDeck.addCard(&varrick);

    // —————————————————————
    // WILD
    // —————————————————————

    // Broelyn, Loreweaver
    std::vector<Effect*> effs_broelyn;
    addEffect<GoldEffect>(effs_broelyn, 2);
    ChampionCard broelyn("Broelyn, Loreweaver", 4, Faction::Sauvage, "Champion", 6, false, false, {});
    m_marketDeck.addCard(&broelyn);

    // Cron, the Berserker
    std::vector<Effect*> effs_cron;
    addEffect<AttackEffect>(effs_cron, 5);
    ChampionCard cron("Cron, the Berserker", 6, Faction::Sauvage, "Champion", 6, false, false, {});
    m_marketDeck.addCard(&cron);

    // Dire Wolf
    std::vector<Effect*> effs_direWolf;
    addEffect<AttackEffect>(effs_direWolf, 3);
    ChampionCard direWolf("Dire Wolf", 5, Faction::Sauvage, "Champion", 5, true, false, {});
    m_marketDeck.addCard(&direWolf);

    // Elven Curse (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_elvenCurse;
        addEffect<AttackEffect>(effs_elvenCurse, 6);
        ActionCard elvenCurse("Elven Curse", 3, Faction::Sauvage, "Action", effs_elvenCurse);
        m_marketDeck.addCard(&elvenCurse);
    }

    // Elven Gift (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_elvenGift;
        addEffect<GoldEffect>(effs_elvenGift, 2);
        ActionCard elvenGift("Elven Gift", 2, Faction::Sauvage, "Action", effs_elvenGift);
        m_marketDeck.addCard(&elvenGift);
    }

    // Grak, Storm Giant
    std::vector<Effect*> effs_grak;
    addEffect<AttackEffect>(effs_grak, 6);
    ChampionCard grak("Grak, Storm Giant", 8, Faction::Sauvage, "Champion", 7, true, false, {});
    m_marketDeck.addCard(&grak);

    // Nature's Bounty
    std::vector<Effect*> effs_nature;
    addEffect<GoldEffect>(effs_nature, 4);
    ActionCard nature("Nature's Bounty", 4, Faction::Sauvage, "Action", effs_nature);
    m_marketDeck.addCard(&nature);

    // Orc Grunt (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_orcGrunt;
        addEffect<AttackEffect>(effs_orcGrunt, 2);
        ChampionCard orcGrunt("Orc Grunt", 3, Faction::Sauvage, "Champion", 3, true, false, {});
        m_marketDeck.addCard(&orcGrunt);
    }

    // Rampage
    std::vector<Effect*> effs_rampage;
    addEffect<AttackEffect>(effs_rampage, 6);
    ActionCard rampage("Rampage", 6, Faction::Sauvage, "Action", effs_rampage);
    m_marketDeck.addCard(&rampage);

    // Torgen Rocksplitter
    std::vector<Effect*> effs_torgen;
    addEffect<AttackEffect>(effs_torgen, 4);
    ChampionCard torgen("Torgen Rocksplitter", 7, Faction::Sauvage, "Champion", 7, true, false, {});
    m_marketDeck.addCard(&torgen);

    // Spark (x3)
    for (int i = 0; i < 3; ++i) {
        std::vector<Effect*> effs_spark;
        addEffect<AttackEffect>(effs_spark, 3);
        ActionCard spark("Spark", 1, Faction::Sauvage, "Action", effs_spark);
        m_marketDeck.addCard(&spark);
    }

    // Wolf Form
    std::vector<Effect*> effs_wolfForm;
    addEffect<AttackEffect>(effs_wolfForm, 8);
    ActionCard wolfForm("Wolf Form", 5, Faction::Sauvage, "Action", effs_wolfForm);
    m_marketDeck.addCard(&wolfForm);

    // Wolf Shaman (x2)
    for (int i = 0; i < 2; ++i) {
        std::vector<Effect*> effs_wolfShaman;
        addEffect<AttackEffect>(effs_wolfShaman, 2);
        ChampionCard wolfShaman("Wolf Shaman", 2, Faction::Sauvage, "Champion", 4, false, false, {});
        m_marketDeck.addCard(&wolfShaman);
    }

    // —————————————————————
    // FIRE GEMS
    // —————————————————————
    for (int i = 0; i < 16; ++i) {
        std::vector<Effect*> effs_fg;
        addEffect<GoldEffect>(effs_fg, 2);
        addEffect<SacrificeEffect>(effs_fg, 3);
        ItemCard fireGem("Fire Gem", 2, Faction::None, "Item", effs_fg);
        m_marketDeck.addCard(&fireGem);
    }

    // —————————————————————
    // DECKS PERSONNELS
    // —————————————————————
    for (int i = 0; i < 28; ++i) {
        std::vector<Effect*> effs_gold;
        addEffect<GoldEffect>(effs_gold, 1);
        ItemCard gold("Gold", 0, Faction::None, "Item", effs_gold);
        m_marketDeck.addCard(&gold);
    }

    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> effs_sword;
        addEffect<AttackEffect>(effs_sword, 2);
        ItemCard sw("Shortsword", 0, Faction::None, "Item", effs_sword);
        m_marketDeck.addCard(&sw);
    }

    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> effs_dagger;
        addEffect<AttackEffect>(effs_dagger, 1);
        ItemCard dg("Dagger", 0, Faction::None, "Item", effs_dagger);
        m_marketDeck.addCard(&dg);
    }

    for (int i = 0; i < 4; ++i) {
        std::vector<Effect*> effs_ruby;
        addEffect<GoldEffect>(effs_ruby, 2);
        ItemCard ruby("Ruby", 1, Faction::None, "Item", effs_ruby);
        m_marketDeck.addCard(&ruby);
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
    std::list<ItemCard>& Market::getFireGems() { return m_fireGems; }
    std::list<Card*>& Market::getSacrificeZone() { return m_sacrificeZone; }

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