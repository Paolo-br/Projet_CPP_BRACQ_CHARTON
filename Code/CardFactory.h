#ifndef __CARDFACTORY_H
#define __CARDFACTORY_H

#include <string>
#include <memory>
#include "CardsType/Card.h"

// Classe Factory pour créer des cartes à partir de leur nom
class CardFactory {
public:
    // Crée une carte à partir de son nom
    static Card* createCard(const std::string& cardName);
    
    // Vérifie si un nom de carte est valide
    static bool isValidCardName(const std::string& cardName);
};

#endif
