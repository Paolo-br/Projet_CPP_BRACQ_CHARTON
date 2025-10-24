#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "DiscardPile.h"

using namespace std;

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              HERO REALMS - NOUVELLE PARTIE                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        // Créer le jeu
        Game game;
        
        // Créer les joueurs
        cout << "\n=== CONFIGURATION DES JOUEURS ===" << endl;
        
        string player1Name, player2Name;
        cout << "Nom du Joueur 1: ";
        cin >> player1Name;
        cout << "Nom du Joueur 2: ";
        cin >> player2Name;
        
        // Créer les decks, mains et défausses vides
        Deck deck1, deck2;
        Hand hand1, hand2;
        DiscardPile discard1, discard2;
        
        Player player1(player1Name, 50, deck1, hand1, discard1);
        Player player2(player2Name, 50, deck2, hand2, discard2);
        
        // Ajouter les joueurs au jeu
        game.addPlayer(player1);
        game.addPlayer(player2);
        
        // Démarrer la partie
        game.start();
        
        // Boucle de jeu principale
        cout << "\n\nLA PARTIE COMMENCE !" << endl;
        cout << "Tapez les numéros pour choisir vos actions." << endl;
        cout << "Le premier joueur à 0 PV perd !\n" << endl;
        
        while (!game.isGameOver()) {
            game.playTurn();
            
            // Petite pause entre les tours
            cout << "\nAppuyez sur Entrée pour continuer au prochain tour...";
            cin.ignore();
            cin.get();
        }
        
        cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                  PARTIE TERMINÉE                           ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════╝" << endl;
        
        cout << "\nMerci d'avoir joué à Hero Realms !" << endl;
        
    } catch (const exception& e) {
        cerr << "\nERREUR FATALE: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
