#include <iostream>
#include <list>
#include "Player.h"
#include "ChampionCard.h"
#include "Deck.h"
#include "Card.h"
#include "Ability.h"
#include "SacrificeAbility.h" 
#include "Faction.h"

using namespace std;

int main() {
    // Création de cartes temporaires pour le Deck
    Card c1("Épée Courte", 0, Faction::Imperial, "Item");
    Card c2("Dague", 0, Faction::Guilde, "Item");
    Card c3("Rubis", 1, Faction::Necros, "Item");
    cout << "Test carte" << endl;
    list<Card> startingCards = {c1, c2, c3};
    cout << "Test carte réssi" << endl;

    // Création d’un Deck
    cout << "Test deck" << endl;
    Deck deck(startingCards);
    cout << "Test deck réussi" << endl;

    // Création d’un joueur
    Player p1("Alice", 50, 5, deck, {}, {});
    cout << "Joueur : " << p1.getName() << " | Santé : " << p1.getHealth() << endl;

    // Ajout de cartes dans la main et la défausse
    p1.drawCard(c1);
    p1.discard(c2);
    cout << "Alice pioche et défausse une carte." << endl;

    // Création d’un Champion avec des abilities allouées dynamiquement
    list<Ability*> abilities;
    abilities.push_back(new SacrificeAbility()); // Allocation dynamique
    ChampionCard champ("Arkus, Dragon Imperial", 8, Faction::Imperial, "Champion", 6, true, false, abilities);
    cout << "Champion créé : " << champ.getName()
         << " | Défense : " << champ.getDefense()
         << " | Garde ? " << (champ.getIsGuard() ? "Oui" : "Non") << endl;

    // Simulation de sacrifice
    p1.sacrifice(c1);
    cout << "Alice sacrifie une carte." << endl;

    // Libérez la mémoire des abilities
    for (Ability* ability : abilities) {
        delete ability;
    }
    cout<<"Tout a fonctionné"<<endl;

    return 0;
}
