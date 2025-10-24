#include "DiscardOpponentEffect.h"
#include "Player.h"
#include "Hand.h"
#include <iostream>
#include <algorithm>

DiscardOpponentEffect::DiscardOpponentEffect(int cardCount) : Effect(cardCount) {
    std::cout << "DiscardOpponentEffect créé: force l'adversaire à défausser " 
              << cardCount << " carte(s)" << std::endl;
}

void DiscardOpponentEffect::apply(Player& player, Turn& turn) {
    std::cout << "EFFET: Défausse de l'adversaire lancé par" << player.getName()<< std::endl;    
    // Vérifier si un adversaire est défini dans le tour
    if (!turn.hasOpponent()) {
        std::cout << "Aucun adversaire défini dans le tour actuel." << std::endl;
        std::cout << "Cet effet sera ignoré" << std::endl;
        return;
    }
    
    Player* opponent = turn.getOpponent();
    Hand& opponentHand = opponent->getHand();
    
    // Vérifier si l'adversaire a des cartes en main
    if (opponentHand.isEmpty()) {
        std::cout << opponent->getName() << " n'a aucune carte en main !" << std::endl;
        return;
    }
    
    int cardsToDiscard = std::min(getValue(), static_cast<int>(opponentHand.size())); // pour éviter les erreurs de taille
    
    std::cout << opponent->getName() << " doit défausser "<< cardsToDiscard << " carte(s)" << std::endl;
    std::cout << "   (Main actuelle: " << opponentHand.size() << " carte(s))" << std::endl;
    std::cout << std::endl;
    


    //
    // A IMPLEMENTER
    //
    // Afficher les cartes en main de l'adversaire avec fonction de Raph
    std::cout << "Cartes en main de " << opponent->getName() << ":" << std::endl;
    const std::vector<Card*>& cards = opponentHand.getCards();

    
    // Demander au joueur adversaire de choisir les cartes à défausser
    for (int i = 0; i < cardsToDiscard; ++i) {
        if (opponentHand.isEmpty()) {
            break;
        }
        
        std::cout << "Carte " << (i + 1) << "/" << cardsToDiscard << " à défausser:" << std::endl;
        
        int choice = -1;
        bool validChoice = false;
        
        // Boucle de validation de la saisie
        while (!validChoice) {
            std::cout << opponent->getName() << ", choisissez une carte à défausser (1-" 
                      << opponentHand.size() << "): ";
            std::cin >> choice;
            
            // Vérifier si la saisie est valide
            if (std::cin.fail()) {
                std::cin.clear(); // Réinitialiser l'état du flux
                std::cin.ignore(10000, '\n'); // Ignorer la ligne incorrecte
                std::cout << "Entrée invalide ! Veuillez entrer un nombre." << std::endl;
                continue;
            }
            
            if (choice >= 1 && choice <= static_cast<int>(opponentHand.size())) {
                validChoice = true;
            } else {
                std::cout << "Choix invalide ! Choisissez entre 1 et " 
                          << opponentHand.size() << std::endl;
            }
        }
        
        // Défausser la carte choisie (index commence à 0)
        Card* cardToDiscard = opponentHand.removeCardAt(choice - 1);
        
        if (cardToDiscard) {
            opponent->discardCard(cardToDiscard);
            std::cout << cardToDiscard->getName() << " défaussée" << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "Résultat: " << opponent->getName() << " a défaussé " 
              << cardsToDiscard << " carte(s)" << std::endl;
    std::cout << "Main restante: " << opponentHand.size() << " carte(s)" << std::endl;
}

Effect* DiscardOpponentEffect::clone() const {
    return new DiscardOpponentEffect(getValue());
}

std::string DiscardOpponentEffect::getName() const {
    return "DiscardOpponentEffect";
}
