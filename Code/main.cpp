#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Cards/Deck.h"
#include "Cards/Hand.h"
#include "Cards/DiscardPile.h"
#include "SaveManager.h"

using namespace std;

void startNewGame(Game& game);
bool loadSavedGame(Game& game);
int displayMainMenu();

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    HERO REALMS                             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        // Créer le jeu
        Game game;
        
        // Afficher le menu principal
        int menuChoice = displayMainMenu();
        
        if (menuChoice == 1) {
            // Nouvelle partie
            startNewGame(game);
        } else if (menuChoice == 2) {
            // Charger une partie
            if (!loadSavedGame(game)) {
                cout << "Aucune partie chargée. Démarrage d'une nouvelle partie..." << endl;
                startNewGame(game);
            }
        } else if (menuChoice == 3) {
            // Quitter
            cout << "\nMerci d'avoir joué à Hero Realms!" << endl;
            return 0;
        }
        
        // Boucle de jeu principale
        if (game.getPlayers().size() >= 2) {
            cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║              LA PARTIE COMMENCE !                          ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            cout << "Tapez les numéros pour choisir vos actions." << endl;
            cout << "Le premier joueur à 0 PV perd !\n" << endl;
            
            while (!game.isGameOver()) {
                game.playTurn();
                
                // Petite pause entre les tours
                if (!game.isGameOver()) {
                    cout << "\nAppuyez sur Entrée pour continuer au prochain tour...";
                    cin.ignore();
                    cin.get();
                }
            }
            
            cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                  PARTIE TERMINÉE                           ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
        }
        
        cout << "\nMerci d'avoir joué à Hero Realms !" << endl;
        
    } catch (const exception& e) {
        cerr << "\nERREUR FATALE: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

int displayMainMenu() {
    SaveManager saveManager;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    MENU PRINCIPAL                          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n[1] Nouvelle partie" << endl;
    cout << "[2] Charger une partie" << endl;
    cout << "[3] Quitter" << endl;
    cout << "\n════════════════════════════════════════════════════════════" << endl;
    
    int choice;
    while (true) {
        cout << "Votre choix: ";
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide! Veuillez entrer 1, 2 ou 3." << endl;
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }
}

void startNewGame(Game& game) {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              HERO REALMS - NOUVELLE PARTIE                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
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
}

bool loadSavedGame(Game& game) {
    SaveManager saveManager;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              CHARGER UNE PARTIE                            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    saveManager.displaySaveSlots();
    
    cout << "\n[1-3] Choisir un slot à charger" << endl;
    cout << "[0] Retour au menu principal" << endl;
    
    int choice;
    cout << "Votre choix: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (choice >= 1 && choice <= 3) {
        if (saveManager.isSlotEmpty(choice)) {
            cout << "\nCe slot est vide!" << endl;
            cout << "Appuyez sur Entrée pour continuer...";
            cin.get();
            return false;
        }
        
        if (saveManager.loadGame(game, choice)) {
            cout << "\nPartie chargée avec succès!" << endl;
            cout << "\n Note importante:" << endl;
            cout << "   - Les cartes du starter deck et Fire Gems sont restaurées" << endl;
            cout << "   - Les cartes du marché ont été remises en défausse" << endl;
            cout << "   - Le marché a été réinitialisé" << endl;
            cout << "\nAppuyez sur Entrée pour continuer...";
            cin.get();
            return true;
        } else {
            cout << "\nErreur lors du chargement de la partie." << endl;
            cout << "Appuyez sur Entrée pour continuer...";
            cin.get();
            return false;
        }
    }
    
    return false;
}
