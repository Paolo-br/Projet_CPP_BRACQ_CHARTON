#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "DiscardPile.h"
#include "Card.h"
#include "ActionCard.h"
#include "ItemCard.h"
#include "ChampionCard.h"
#include "Effect.h"
#include "GoldEffect.h"
#include "AttackEffect.h"
#include "HealEffect.h"
#include "DrawEffect.h"
#include "SacrificeEffect.h"
#include "Market.h"
#include "Game.h"
#include "GameSettings.h"
#include "Turn.h"
#include "Ability.h"
#include "SacrificeAbility.h"
#include "Faction.h"


int main() {
    // Créer un joueur et un tour pour les tests
    Player player("TestPlayer", 50, Deck(), Hand(), DiscardPile());
    Turn turn(player);

    // Créer des effets pour les cartes
    std::vector<Effect*> goldEffects;
    goldEffects.push_back(new GoldEffect(1));

    std::vector<Effect*> attackEffects;
    attackEffects.push_back(new AttackEffect(2));

    std::list<Ability*> championAbilities;
    championAbilities.push_back(new PrimaryAbility());

    // Créer des cartes
    ItemCard* goldCard = new ItemCard("Or", 0, Faction::None, "Item", goldEffects);
    ActionCard* attackCard = new ActionCard("Attaque", 1, Faction::None, "Action", attackEffects);
    ChampionCard* warriorCard = new ChampionCard("Guerrier", 2, Faction::None, "Champion", 3, true, false, championAbilities);

    // Tester les méthodes de Card
    std::cout << "Test des méthodes de Card:" << std::endl;
    std::cout << "Nom de la carte Or: " << goldCard->getName() << std::endl;
    std::cout << "Coût de la carte Or: " << goldCard->getCost() << std::endl;
    std::cout << "Type de la carte Or: " << goldCard->getType() << std::endl;

    // Tester les méthodes spécifiques à ItemCard
    std::cout << "\nTest des méthodes spécifiques à ItemCard:" << std::endl;
    goldCard->executeEffects(player, turn);

    // Tester les méthodes spécifiques à ActionCard
    std::cout << "\nTest des méthodes spécifiques à ActionCard:" << std::endl;
    attackCard->executeEffects(player, turn);

    // Tester les méthodes spécifiques à ChampionCard
    std::cout << "\nTest des méthodes spécifiques à ChampionCard:" << std::endl;
    std::cout << "Défense du Guerrier: " << warriorCard->getDefense() << std::endl;
    std::cout << "Le Guerrier est-il un Garde ? " << (warriorCard->isGuard() ? "Oui" : "Non") << std::endl;
    warriorCard->takeDamage(2);
    std::cout << "Dégâts actuels du Guerrier: " << warriorCard->getCurrentDamage() << std::endl;
    std::cout << "Le Guerrier est-il assommé ? " << (warriorCard->isStunned() ? "Oui" : "Non") << std::endl;
    warriorCard->executeEffects(player, turn);

    // Nettoyer la mémoire
    delete goldCard;
    delete attackCard;
    delete warriorCard;

    return 0;
}
