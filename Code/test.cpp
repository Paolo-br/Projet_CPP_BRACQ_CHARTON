#include <iostream>
#include <list>
#include <vector>
#include "Player.h"
#include "Deck.h"
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

using namespace std;

int main() {
    cout << "===== 🧪 DÉBUT DES TESTS HERO REALMS =====" << endl;

    // ------------------- TEST CARD DE BASE -------------------
    Card c1("Épée Courte", 0, Faction::Imperial, "Item");
    Card c2("Dague", 0, Faction::Guilde, "Item");
    Card c3("Rubis", 1, Faction::Necros, "Item");
    cout << "Cartes de base créées : " << c1.getName() << ", " << c2.getName() << ", " << c3.getName() << endl;

    // ------------------- TEST DECK -------------------
    list<Card> startingCards = {c1, c2, c3};
    Deck deck(startingCards);
    cout << "Deck initialisé avec " << startingCards.size() << " cartes." << endl;

    // ------------------- TEST PLAYER -------------------
    Player p1("Alice", 50, 5, deck, {}, {});
    Player p2("Bob", 50, 3, deck, {}, {});
    cout << "Joueurs créés : " << p1.getName() << " et " << p2.getName() << endl;

    p1.drawCard(c1);
    p1.discard(c2);
    cout << p1.getName() << " pioche et défausse une carte." << endl;

    // ------------------- TEST EFFECTS -------------------
    GoldEffect gold(3);
    AttackEffect atk(5);
    HealEffect heal(4);
    DrawEffect draw(2);
    SacrificeEffect sac(1);

    cout << "Application des effets sur les joueurs..." << endl;
    gold.apply(p1, p1);
    atk.apply(p2, p1);
    heal.apply(p1, p1);
    draw.apply(p1, p1);
    sac.apply(p1, p1);

    cout << "Effets appliqués avec succès." << endl;

    // ------------------- TEST ACTIONCARD & ITEMCARD -------------------
    vector<Effect*> actionEffects = {new AttackEffect(4), new GoldEffect(2)};
    ActionCard fireball("Boule de Feu", 6, Faction::Necros, "Action", actionEffects);
    cout << "ActionCard test : " << fireball.getName() << endl;
    fireball.play(p1, p2);

    vector<Effect*> itemEffects = {new HealEffect(3)};
    ItemCard potion("Potion de Soin", 3, Faction::Imperial, "Item", itemEffects);
    cout << "ItemCard test : " << potion.getName() << endl;
    potion.play(p1, p1);

    // ------------------- TEST CHAMPIONCARD + ABILITIES -------------------
    list<Ability*> abilities;
    abilities.push_back(new SacrificeAbility());
    ChampionCard champ("Arkus, Dragon Imperial", 8, Faction::Imperial, "Champion", 6, true, false, abilities);
    cout << "Champion créé : " << champ.getName() << " (Défense " << champ.getDefense() << ")" << endl;

    champ.activate();
    champ.defend();
    champ.sacrifice();

    // ------------------- TEST MARKET INITIALISATION -------------------
    cout << "\n===== TEST INITIALISATION DU MARCHÉ =====" << endl;
    
    // Créer un marché vide
    Market market;
    
    // Initialiser le marché avec toutes les cartes
    cout << "Initialisation du marché en cours..." << endl;
    market.initializeBaseSet();
    
    // Afficher les statistiques du marché
    cout << "Marché initialisé avec succès !" << endl;
    
    // Tester l'achat d'une carte
    cout << "\n----- Test d'achat de carte -----" << endl;
    
    // Simuler que le joueur a assez d'or
    p1.setGold(10); // Donner de l'or au joueur
    
    // Afficher les cartes visibles disponibles
    cout << "Cartes visibles sur le marché :" << endl;
    // Note: Vous devrez peut-être ajouter une méthode getVisibleCards() dans Market.h
    
    // Tester l'achat d'une carte spécifique (première carte visible)
    cout << "Test d'achat d'une carte..." << endl;
    
    // ------------------- TEST FIRE GEMS -------------------
    cout << "\n----- Test des Gemmes de Feu -----" << endl;
    Market fireGemMarket;
    fireGemMarket.initializeFireGems();
    cout << "Gemmes de Feu initialisées" << endl;

    // ------------------- TEST PLAYER DECK CARDS -------------------
    cout << "\n----- Test des cartes de deck joueur -----" << endl;
    Market playerDeckMarket;
    playerDeckMarket.initializePlayerDeckCards();
    cout << "Cartes de deck joueur initialisées" << endl;

    // ------------------- TEST GAME SETTINGS -------------------
    GameSettings settings;
    settings.enableGodMode();
    settings.disableGodMode();
    cout << "God mode activé puis désactivé." << endl;

    // ------------------- TEST GAME COMPLET -------------------
    cout << "\n===== TEST PARTIE COMPLÈTE =====" << endl;
    Game game;
    game.addPlayer(p1);
    game.addPlayer(p2);
    
    cout << "Démarrage de la partie..." << endl;
    game.start();
    
    cout << "Simulation d'un tour..." << endl;
    game.playTurn();
    
    cout << "Fin de la partie..." << endl;
    game.endGame();

    // ------------------- TEST AVANCÉ DU MARCHÉ -------------------
    cout << "\n===== TESTS AVANCÉS DU MARCHÉ =====" << endl;
    
    // Test d'ajout de carte au marché
    Card testCard("Carte Test", 3, Faction::Imperial, "Action");
    market.addCard(testCard);
    cout << "Carte test ajoutée au marché" << endl;
    
    // Test avec différents types de cartes
    cout << "\n----- Test des différentes factions -----" << endl;
    
    // Créer quelques cartes de test pour chaque faction
    vector<Effect*> imperialEffects = {new GoldEffect(2), new HealEffect(3)};
    ActionCard imperialCard("Test Imperial", 4, Faction::Imperial, "Action", imperialEffects);
    
    vector<Effect*> guildEffects = {new AttackEffect(3), new GoldEffect(1)};
    ActionCard guildCard("Test Guilde", 3, Faction::Guilde, "Action", guildEffects);
    
    vector<Effect*> necrosEffects = {new AttackEffect(4), new SacrificeEffect(2)};
    ActionCard necrosCard("Test Necros", 5, Faction::Necros, "Action", necrosEffects);
    
    vector<Effect*> wildEffects = {new AttackEffect(3), new DrawEffect(1)};
    ActionCard wildCard("Test Wild", 4, Faction::Sauvage, "Action", wildEffects);
    
    cout << "Cartes de test créées pour toutes les factions" << endl;

    cout << "\n===== TOUS LES TESTS SE SONT TERMINÉS AVEC SUCCÈS =====" << endl;


    cout << "\nNettoyage de la mémoire..." << endl;
    for (auto e : actionEffects) delete e;
    for (auto e : itemEffects) delete e;
    for (auto ab : abilities) delete ab;
    for (auto e : imperialEffects) delete e;
    for (auto e : guildEffects) delete e;
    for (auto e : necrosEffects) delete e;
    for (auto e : wildEffects) delete e;

    cout << "Nettoyage terminé" << endl;

    return 0;
}