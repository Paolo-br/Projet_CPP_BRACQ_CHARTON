#include "CardsType/ActionCard.h"
#include "CardsType/ItemCard.h"
#include "CardsType/ChampionCard.h"
#include "Effects/DrawThenDiscardEffect.h"
#include "Effects/Effect.h"
#include "Effects/GoldEffect.h"
#include "Effects/AttackEffect.h"
#include "Effects/HealEffect.h"
#include "Effects/DrawEffect.h"
#include "Effects/SacrificeEffect.h"
#include "Effects/PrepareChampionEffect.h"
#include "Effects/StunChampionEffect.h"
#include "Effects/DiscardOpponentEffect.h"
#include "Effects/ConditionalEffect.h"
#include "Effects/ChoiceEffect.h"
#include "Effects/PutNextCardOnTopEffect.h"
#include "Effects/PutNextCardInHandEffect.h"
#include "Effects/PutFromDiscardOnTopEffect.h"
#include "Effects/OptionalSacrificeEffect.h"
#include "Effects/PutChampionFromDiscardOnTopEffect.h"
#include "Abilities/Ability.h"
#include "Abilities/AllyAbility.h"
#include "Abilities/SacrificeAbility.h"
#include "Abilities/ActivateAbility.h"
#include "Abilities/PrimaryAbility.h"
#include "CardFactory.h"
#include <iostream>

// Fonction helper pour créer les cartes du starter deck
static Card* createStarterCard(const std::string& cardName) {
    if (cardName == "Or") {
        std::vector<Effect*> effects;
        effects.push_back(new GoldEffect(1));
        return new ItemCard("Or", 0, Faction::None, "Item", effects);
    }
    else if (cardName == "Épée Courte") {
        std::vector<Effect*> effects;
        effects.push_back(new AttackEffect(2));
        return new ItemCard("Épée Courte", 0, Faction::None, "Item", effects);
    }
    else if (cardName == "Dague") {
        std::vector<Effect*> effects;
        effects.push_back(new AttackEffect(1));
        return new ItemCard("Dague", 0, Faction::None, "Item", effects);
    }
    else if (cardName == "Rubis") {
        std::vector<Effect*> effects;
        effects.push_back(new GoldEffect(2));
        return new ItemCard("Rubis", 0, Faction::None, "Item", effects);
    }
    else if (cardName == "Fire Gem") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        
        return new ItemCard("Fire Gem", 2, Faction::None, "Item", {}, abilities);
    }
    
    return nullptr;
}

// Fonction helper pour créer les cartes Imperial
static Card* createImperialCard(const std::string& cardName) {
    // 1. Arkus, Imperial Dragon
    if (cardName == "Arkus, Imperial Dragon") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(5));
        activateEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new HealEffect(6));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Arkus, Imperial Dragon", 8, Faction::Imperial, "Champion", 6, true, abilities);
    }
    
    // 2. Close Ranks
    if (cardName == "Close Ranks") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(5));
        primaryEffs.push_back(new ConditionalEffect(ResourceType::Combat, 2, ConditionType::ChampionCount));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new HealEffect(6));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Close Ranks", 3, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 3. Command
    if (cardName == "Command") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        primaryEffs.push_back(new AttackEffect(3));
        primaryEffs.push_back(new HealEffect(4));
        primaryEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        
        return new ActionCard("Command", 5, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 4. Darian, War Mage
    if (cardName == "Darian, War Mage") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new ChoiceEffect(
            new AttackEffect(3), "+3 Combat",
            new HealEffect(4), "+4 Health"
        ));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Darian, War Mage", 4, Faction::Imperial, "Champion", 5, false, abilities);
    }
    
    // 5. Domination
    if (cardName == "Domination") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(6));
        primaryEffs.push_back(new HealEffect(6));
        primaryEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new PrepareChampionEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Domination", 7, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 6. Cristov, the Just
    if (cardName == "Cristov, the Just") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        activateEffs.push_back(new HealEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Cristov, the Just", 5, Faction::Imperial, "Champion", 5, true, abilities);
    }
    
    // 7. Kraka, High Priest
    if (cardName == "Kraka, High Priest") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new HealEffect(2));
        activateEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new ConditionalEffect(ResourceType::Health, 2, ConditionType::ChampionCount));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Kraka, High Priest", 6, Faction::Imperial, "Champion", 6, false, abilities);
    }
    
    // 8. Man-at-Arms
    if (cardName == "Man-at-Arms") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        activateEffs.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::OtherGuardCount, Faction::None, false));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Man-at-Arms", 3, Faction::Imperial, "Champion", 4, true, abilities);
    }
    
    // 9. Master Weyan
    if (cardName == "Master Weyan") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(3));
        activateEffs.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::OtherChampionCount, Faction::None, false));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Master Weyan", 4, Faction::Imperial, "Champion", 4, true, abilities);
    }
    
    // 10. Rally the Troops
    if (cardName == "Rally the Troops") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(5));
        primaryEffs.push_back(new HealEffect(5));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new PrepareChampionEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Rally the Troops", 4, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 11. Recruit
    if (cardName == "Recruit") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        primaryEffs.push_back(new HealEffect(3));
        primaryEffs.push_back(new ConditionalEffect(ResourceType::Health, 1, ConditionType::ChampionCount));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new GoldEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Recruit", 2, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 12. Tithe Priest
    if (cardName == "Tithe Priest") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new ConditionalEffect(ResourceType::Health, 1, ConditionType::ChampionCount), "+1 Health par champion"
        ));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Tithe Priest", 2, Faction::Imperial, "Champion", 3, false, abilities);
    }
    
    // 13. Taxation
    if (cardName == "Taxation") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new HealEffect(6));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Taxation", 1, Faction::Imperial, "Action", {}, abilities);
    }
    
    // 14. Word of Power
    if (cardName == "Word of Power") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new DrawEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new HealEffect(5));
        
        std::vector<Effect*> sacrificeEffs;
        sacrificeEffs.push_back(new AttackEffect(5));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        abilities.push_back(new SacrificeAbility(sacrificeEffs));
        
        return new ActionCard("Word of Power", 6, Faction::Imperial, "Action", {}, abilities);
    }
    
    return nullptr;
}

// Fonction helper pour créer les cartes Guild
static Card* createGuildCard(const std::string& cardName) {
    // 1. Borg, Ogre Mercenary
    if (cardName == "Borg, Ogre Mercenary") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Borg, Ogre Mercenary", 6, Faction::Guilde, "Champion", 6, true, abilities);
    }
    
    // 2. Bribe
    if (cardName == "Bribe") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new PutNextCardOnTopEffect("Action"));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Bribe", 3, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 3. Death Threat
    if (cardName == "Death Threat") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(1));
        primaryEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new StunChampionEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Death Threat", 3, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 4. Deception
    if (cardName == "Deception") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        primaryEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new PutNextCardInHandEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Deception", 5, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 5. Fire Bomb
    if (cardName == "Fire Bomb") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(8));
        primaryEffs.push_back(new StunChampionEffect());
        primaryEffs.push_back(new DrawEffect(1));
        
        std::vector<Effect*> sacrificeEffs;
        sacrificeEffs.push_back(new AttackEffect(5));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new SacrificeAbility(sacrificeEffs));
        
        return new ActionCard("Fire Bomb", 8, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 6. Hit Job
    if (cardName == "Hit Job") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(7));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new StunChampionEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Hit Job", 4, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 7. Intimidation
    if (cardName == "Intimidation") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(5));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new GoldEffect(2));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Intimidation", 2, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 8. Myros, Guild Mage
    if (cardName == "Myros, Guild Mage") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new GoldEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Myros, Guild Mage", 5, Faction::Guilde, "Champion", 3, true, abilities);
    }
    
    // 9. Parov, the Enforcer
    if (cardName == "Parov, the Enforcer") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Parov, the Enforcer", 5, Faction::Guilde, "Champion", 5, true, abilities);
    }
    
    // 10. Profit
    if (cardName == "Profit") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Profit", 1, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 11. Rake, Master Assassin
    if (cardName == "Rake, Master Assassin") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(4));
        activateEffs.push_back(new StunChampionEffect());
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Rake, Master Assassin", 7, Faction::Guilde, "Champion", 7, false, abilities);
    }
    
    // 12. Rasmus, the Smuggler
    if (cardName == "Rasmus, the Smuggler") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new PutNextCardOnTopEffect("Any"));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Rasmus, the Smuggler", 4, Faction::Guilde, "Champion", 5, false, abilities);
    }
    
    // 13. Smash and Grab
    if (cardName == "Smash and Grab") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(6));
        primaryEffs.push_back(new PutFromDiscardOnTopEffect(true));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        
        return new ActionCard("Smash and Grab", 6, Faction::Guilde, "Action", {}, abilities);
    }
    
    // 14. Street Thug
    if (cardName == "Street Thug") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new AttackEffect(2), "+2 Combat"
        ));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Street Thug", 3, Faction::Guilde, "Champion", 4, false, abilities);
    }
    
    return nullptr;
}

// Fonction helper pour créer les cartes Necros
static Card* createNecrosCard(const std::string& cardName) {
    // 1. Cult Priest
    if (cardName == "Cult Priest") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new ChoiceEffect(
            new GoldEffect(1), "+1 Gold",
            new AttackEffect(1), "+1 Combat"
        ));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Cult Priest", 3, Faction::Necros, "Champion", 4, false, abilities);
    }
    
    // 2. Dark Energy
    if (cardName == "Dark Energy") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(7));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Dark Energy", 4, Faction::Necros, "Action", {}, abilities);
    }
    
    // 3. Dark Reward
    if (cardName == "Dark Reward") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(3));
        primaryEffs.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(6));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Dark Reward", 5, Faction::Necros, "Action", {}, abilities);
    }
    
    // 4. Death Cultist
    if (cardName == "Death Cultist") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Death Cultist", 2, Faction::Necros, "Champion", 3, true, abilities);
    }
    
    // 5. Death Touch
    if (cardName == "Death Touch") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(2));
        primaryEffs.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Death Touch", 1, Faction::Necros, "Action", {}, abilities);
    }
    
    // 6. Rayla, Endweaver
    if (cardName == "Rayla, Endweaver") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Rayla, Endweaver", 4, Faction::Necros, "Champion", 4, false, abilities);
    }
    
    // 7. Influence
    if (cardName == "Influence") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(3));
        
        std::vector<Effect*> sacrificeEffs;
        sacrificeEffs.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new SacrificeAbility(sacrificeEffs));
        
        return new ActionCard("Influence", 2, Faction::Necros, "Action", {}, abilities);
    }
    
    // 8. Krythos, Master Vampire
    if (cardName == "Krythos, Master Vampire") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(3));
        activateEffs.push_back(new OptionalSacrificeEffect(1, 1, true, new AttackEffect(3)));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Krythos, Master Vampire", 7, Faction::Necros, "Champion", 6, false, abilities);
    }
    
    // 9. Life Drain
    if (cardName == "Life Drain") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(8));
        primaryEffs.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Life Drain", 6, Faction::Necros, "Action", {}, abilities);
    }
    
    // 10. Lys, the Unseen
    if (cardName == "Lys, the Unseen") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        activateEffs.push_back(new OptionalSacrificeEffect(1, 1, true, new AttackEffect(2)));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Lys, the Unseen", 6, Faction::Necros, "Champion", 5, true, abilities);
    }
    
    // 11. The Rot
    if (cardName == "The Rot") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(4));
        primaryEffs.push_back(new OptionalSacrificeEffect(1, 1, true, nullptr));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("The Rot", 3, Faction::Necros, "Action", {}, abilities);
    }
    
    // 12. Tyrannor, the Devourer
    if (cardName == "Tyrannor, the Devourer") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(4));
        activateEffs.push_back(new OptionalSacrificeEffect(1, 2, true, nullptr));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Tyrannor, the Devourer", 8, Faction::Necros, "Champion", 6, true, abilities);
    }
    
    // 13. Varrick, the Necromancer
    if (cardName == "Varrick, the Necromancer") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new PutChampionFromDiscardOnTopEffect());
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Varrick, the Necromancer", 5, Faction::Necros, "Champion", 3, false, abilities);
    }
    
    return nullptr;
}

// Fonction helper pour créer les cartes Wild
static Card* createWildCard(const std::string& cardName) {
    // 1. Broelyn, Loreweaver
    if (cardName == "Broelyn, Loreweaver") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new GoldEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Broelyn, Loreweaver", 4, Faction::Sauvage, "Champion", 6, false, abilities);
    }
    
    // 2. Cron, the Berserker
    if (cardName == "Cron, the Berserker") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(5));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Cron, the Berserker", 6, Faction::Sauvage, "Champion", 6, false, abilities);
    }
    
    // 3. Dire Wolf
    if (cardName == "Dire Wolf") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(3));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Dire Wolf", 5, Faction::Sauvage, "Champion", 5, true, abilities);
    }
    
    // 4. Elven Curse
    if (cardName == "Elven Curse") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(6));
        primaryEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(3));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Elven Curse", 3, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 5. Elven Gift
    if (cardName == "Elven Gift") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(2));
        primaryEffs.push_back(new DrawThenDiscardEffect(1, 1, true));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Elven Gift", 2, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 6. Grak, Storm Giant
    if (cardName == "Grak, Storm Giant") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(6));
        activateEffs.push_back(new DrawThenDiscardEffect(1, 1, true));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawThenDiscardEffect(1, 1, false));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Grak, Storm Giant", 8, Faction::Sauvage, "Champion", 7, true, abilities);
    }
    
    // 7. Nature's Bounty
    if (cardName == "Nature's Bounty") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new GoldEffect(4));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> sacrificeEffs;
        sacrificeEffs.push_back(new AttackEffect(4));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        abilities.push_back(new SacrificeAbility(sacrificeEffs));
        
        return new ActionCard("Nature's Bounty", 4, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 8. Orc Grunt
    if (cardName == "Orc Grunt") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new DrawEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ChampionCard("Orc Grunt", 3, Faction::Sauvage, "Champion", 3, true, abilities);
    }
    
    // 9. Rampage
    if (cardName == "Rampage") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(6));
        primaryEffs.push_back(new DrawThenDiscardEffect(2, 2, true));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        
        return new ActionCard("Rampage", 6, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 10. Torgen Rocksplitter
    if (cardName == "Torgen Rocksplitter") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(4));
        activateEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Torgen Rocksplitter", 7, Faction::Sauvage, "Champion", 7, true, abilities);
    }
    
    // 11. Spark
    if (cardName == "Spark") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(3));
        primaryEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> allyEffs;
        allyEffs.push_back(new AttackEffect(2));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new AllyAbility(allyEffs));
        
        return new ActionCard("Spark", 1, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 12. Wolf Form
    if (cardName == "Wolf Form") {
        std::vector<Effect*> primaryEffs;
        primaryEffs.push_back(new AttackEffect(8));
        primaryEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Effect*> sacrificeEffs;
        sacrificeEffs.push_back(new DiscardOpponentEffect(1));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new PrimaryAbility(primaryEffs));
        abilities.push_back(new SacrificeAbility(sacrificeEffs));
        
        return new ActionCard("Wolf Form", 5, Faction::Sauvage, "Action", {}, abilities);
    }
    
    // 13. Wolf Shaman
    if (cardName == "Wolf Shaman") {
        std::vector<Effect*> activateEffs;
        activateEffs.push_back(new AttackEffect(2));
        activateEffs.push_back(new ConditionalEffect(ResourceType::Combat, 1, ConditionType::FactionCardCount, Faction::Sauvage, false));
        
        std::vector<Ability*> abilities;
        abilities.push_back(new ActivateAbility(activateEffs));
        
        return new ChampionCard("Wolf Shaman", 2, Faction::Sauvage, "Champion", 4, false, abilities);
    }
    
    return nullptr;
}

Card* CardFactory::createCard(const std::string& cardName) {
    // Essayer de créer une carte du starter deck
    Card* card = createStarterCard(cardName);
    if (card != nullptr) {
        return card;
    }
    
    // Essayer de créer une carte Imperial
    card = createImperialCard(cardName);
    if (card != nullptr) {
        return card;
    }
    
    // Essayer de créer une carte Guild
    card = createGuildCard(cardName);
    if (card != nullptr) {
        return card;
    }
    
    // Essayer de créer une carte Necros
    card = createNecrosCard(cardName);
    if (card != nullptr) {
        return card;
    }
    
    // Essayer de créer une carte Wild
    card = createWildCard(cardName);
    if (card != nullptr) {
        return card;
    }
    
    // Carte inconnue
    std::cerr << "⚠️ CardFactory: Carte inconnue '" << cardName << "'" << std::endl;
    std::cerr << "   Création d'une carte de remplacement (Or)" << std::endl;
    
    // Créer une carte de remplacement pour éviter les crashes
    std::vector<Effect*> effects;
    effects.push_back(new GoldEffect(1));
    return new ItemCard("Or", 0, Faction::None, "Item", effects);
}

bool CardFactory::isValidCardName(const std::string& cardName) {
    // Cartes du starter deck
    if (cardName == "Or" || cardName == "Épée Courte" || 
        cardName == "Dague" || cardName == "Rubis" || cardName == "Fire Gem") {
        return true;
    }
    
    // Cartes Imperial
    if (cardName == "Arkus, Imperial Dragon" || cardName == "Close Ranks" || 
        cardName == "Command" || cardName == "Darian, War Mage" || 
        cardName == "Domination" || cardName == "Cristov, the Just" ||
        cardName == "Kraka, High Priest" || cardName == "Man-at-Arms" ||
        cardName == "Master Weyan" || cardName == "Rally the Troops" ||
        cardName == "Recruit" || cardName == "Tithe Priest" ||
        cardName == "Taxation" || cardName == "Word of Power") {
        return true;
    }
    
    // Cartes Guild
    if (cardName == "Borg, Ogre Mercenary" || cardName == "Bribe" || 
        cardName == "Death Threat" || cardName == "Deception" || 
        cardName == "Fire Bomb" || cardName == "Hit Job" ||
        cardName == "Intimidation" || cardName == "Myros, Guild Mage" ||
        cardName == "Parov, the Enforcer" || cardName == "Profit" ||
        cardName == "Rake, Master Assassin" || cardName == "Rasmus, the Smuggler" ||
        cardName == "Smash and Grab" || cardName == "Street Thug") {
        return true;
    }
    
    // Cartes Necros
    if (cardName == "Cult Priest" || cardName == "Dark Energy" || 
        cardName == "Dark Reward" || cardName == "Death Cultist" || 
        cardName == "Death Touch" || cardName == "Rayla, Endweaver" ||
        cardName == "Influence" || cardName == "Krythos, Master Vampire" ||
        cardName == "Life Drain" || cardName == "Lys, the Unseen" ||
        cardName == "The Rot" || cardName == "Tyrannor, the Devourer" ||
        cardName == "Varrick, the Necromancer") {
        return true;
    }
    
    // Cartes Wild
    if (cardName == "Broelyn, Loreweaver" || cardName == "Cron, the Berserker" || 
        cardName == "Dire Wolf" || cardName == "Elven Curse" || 
        cardName == "Elven Gift" || cardName == "Grak, Storm Giant" ||
        cardName == "Nature's Bounty" || cardName == "Orc Grunt" ||
        cardName == "Rampage" || cardName == "Torgen Rocksplitter" ||
        cardName == "Spark" || cardName == "Wolf Form" ||
        cardName == "Wolf Shaman") {
        return true;
    }
    
    return false;
}
