#include "PutFromDiscardOnTopEffect.h"
#include "Player.h"
#include "Turn.h"
#include "DiscardPile.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <limits>

PutFromDiscardOnTopEffect::PutFromDiscardOnTopEffect(bool optional)
    : Effect(0), m_optional(optional) {
}

void PutFromDiscardOnTopEffect::apply(Player& player, Turn& turn) {
    (void)turn;
    
    DiscardPile& discard = player.getDiscardPile();
    
    if (discard.isEmpty()) {
        std::cout << player.getName() << " n'a aucune carte dans sa défausse." << std::endl;
        return;
    }
    
    if (m_optional) {
        std::cout << "\nVoulez-vous placer une carte de votre défausse sur le dessus de votre deck? (o/n): ";
        std::string choice;
        std::cin >> choice;
        if (choice != "o" && choice != "O") {
            std::cout << "Effet non activé." << std::endl;
            return;
        }
    }
    
    // Afficher les cartes de la défausse
    std::cout << "\n=== DÉFAUSSE DE " << player.getName() << " ===" << std::endl;
    const std::vector<Card*>& cards = discard.getCards();
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << cards[i]->getName() << std::endl;
    }
    std::cout << "[0] Annuler" << std::endl;
    
    int choice;
    while (true) {
        std::cout << "Choisissez une carte à placer sur votre deck (0 pour annuler): ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide!" << std::endl;
            continue;
        }
        
        if (choice == 0) {
            std::cout << "Annulé." << std::endl;
            return;
        }
        
        if (choice > 0 && choice <= static_cast<int>(cards.size())) {
            Card* selectedCard = cards[choice - 1];
            
            // Retirer la carte de la défausse
            discard.removeCard(selectedCard);
            
            // Placer la carte sur le dessus du deck
            player.getDeck().addCardOnTop(selectedCard);
            
            std::cout << "→ " << selectedCard->getName() 
                      << " placée sur le dessus du deck de " << player.getName() << "!" << std::endl;
            return;
        }
        
        std::cout << "Choix invalide!" << std::endl;
    }
}

Effect* PutFromDiscardOnTopEffect::clone() const {
    return new PutFromDiscardOnTopEffect(*this);
}

std::string PutFromDiscardOnTopEffect::getName() const {
    return "PutFromDiscardOnTopEffect";
}
