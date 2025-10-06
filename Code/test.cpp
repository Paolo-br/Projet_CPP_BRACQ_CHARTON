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

    // ------------------- TEST MARKET -------------------
    list<Card> visible = {c1, c2};
    Deck marketDeck(startingCards);
    Market market(visible, marketDeck);
    cout << "Marché initialisé avec " << visible.size() << " cartes visibles." << endl;
    market.buyCard(p1, c3);

    // ------------------- TEST GAME SETTINGS -------------------
    GameSettings settings;
    settings.enableGodMode();
    settings.disableGodMode();
    cout << "God mode activé puis désactivé." << endl;

    // ------------------- TEST GAME -------------------
    Game game;
    game.addPlayer(p1);
    game.addPlayer(p2);
    game.start();
    game.playTurn();
    game.endGame();

    cout << "===== TOUS LES TESTS SE SONT TERMINÉS SANS ERREUR =====" << endl;

    // ------------------- CLEANUP -------------------
    for (auto e : actionEffects) delete e;
    for (auto e : itemEffects) delete e;
    for (auto ab : abilities) delete ab;

    return 0;
}
