#include "DrawThenDiscardEffect.h"
#include "Player.h"
#include "Turn.h"
#include "Hand.h"
#include "Deck.h"
#include "DiscardPile.h"
#include <iostream>

DrawThenDiscardEffect::DrawThenDiscardEffect(int drawCount, int discardCount, bool optional)
    : Effect(0), m_drawCount(drawCount), m_discardCount(discardCount), m_optional(optional) {
}

void DrawThenDiscardEffect::apply(Player& player, Turn& turn) {
    (void)turn; 
    if (m_optional) {
        std::cout << "Voulez-vous piocher " << m_drawCount << " carte(s) puis en défausser " 
                  << m_discardCount << " ? (o/n): ";
        std::string choice;
        std::cin >> choice;
        if (choice != "o" && choice != "O") {
            std::cout << "Effet non activé." << std::endl;
            return;
        }
    }
    
    // Piocher les cartes
    std::cout << player.getName() << " pioche " << m_drawCount << " carte(s)" << std::endl;
    size_t handSizeBefore = player.getHand().size();
    player.drawCards(m_drawCount);
    size_t cardsActuallyDrawn = player.getHand().size() - handSizeBefore;
    
    if (cardsActuallyDrawn < static_cast<size_t>(m_drawCount)) {
        std::cout << "Seulement " << cardsActuallyDrawn << " carte(s) ont pu être piochées" << std::endl;
    }
    
    // Défausser les cartes
    if (player.getHand().size() < static_cast<size_t>(m_discardCount)) {
        std::cout << "Pas assez de cartes en main pour en défausser " << m_discardCount << std::endl;
        return;
    }
    
    std::cout << player.getName() << " doit défausser " << m_discardCount << " carte(s)" << std::endl;
    for (int i = 0; i < m_discardCount; ++i) {
        // Display hand
        std::cout << "Main: ";
        for (size_t j = 0; j < player.getHand().size(); ++j) {
            std::cout << j << ". " << player.getHand().getCardAt(j)->getName() << " | ";
        }
        std::cout << std::endl;
        
        std::cout << "Choisissez une carte à défausser (index): ";
        int index;
        std::cin >> index;
        
        if (index >= 0 && index < static_cast<int>(player.getHand().size())) {
            Card* card = player.getHand().getCardAt(index);
            player.getHand().removeCardAt(index);
            player.getDiscardPile().add(card);
            std::cout << "Carte \"" << card->getName() << "\" défaussée." << std::endl;
        } else {
            std::cout << "Index invalide !" << std::endl;
            --i; 
        }
    }
}

Effect* DrawThenDiscardEffect::clone() const {
    return new DrawThenDiscardEffect(m_drawCount, m_discardCount, m_optional);
}

std::string DrawThenDiscardEffect::getName() const {
    std::string name = m_optional ? "May draw " : "Draw ";
    name += std::to_string(m_drawCount) + " then discard " + std::to_string(m_discardCount);
    return name;
}
