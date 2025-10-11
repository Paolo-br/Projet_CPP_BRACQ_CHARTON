#ifndef INPLAYAREA_H
#define INPLAYAREA_H

#include <list>
#include <iostream>
#include <vector>
#include "Card.h"
#include "ChampionCard.h"

class InPlayArea {
private:
    std::vector<Card*> m_cards;        // Actions et Objets
    std::vector<ChampionCard> m_champions; // Champions

public:
    InPlayArea();
    InPlayArea(std::vector<Card*> cards, std::vector<ChampionCard> champions);
    ~InPlayArea();

    // Gestion des cartes normales
    void add(Card* card);
    void clear();
    std::vector<Card*>& getCards();
    
    // Gestion des Champions
    void addChampion(ChampionCard champion);
    void removeChampion(ChampionCard& champion);
    std::vector<ChampionCard>& getChampions();
    
    // Méthodes utilitaires
    bool hasGuardInPlay() const;
    void mobilizeChampions();
    void clearAll();
    size_t getChampionCount() const;
    size_t getCardCount() const;
};

#endif