#ifndef INPLAYAREA_H
#define INPLAYAREA_H

#include <list>
#include <iostream>
#include <vector>
#include "CardsType/Card.h"
#include "CardsType/ChampionCard.h"

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
    // Vider la liste des cartes (sans delete)
    void removeAllCardsNoDelete();
    std::vector<Card*>& getCards();
    
    // Gestion des Champions
    void addChampion(ChampionCard champion);
    void removeChampion(ChampionCard& champion);
    std::vector<ChampionCard>& getChampions();
    const std::vector<ChampionCard>& getChampions() const;
    
    // Méthodes utilitaires
    bool hasGuardInPlay() const;
    void mobilizeChampions();
    void clearAll();
    size_t getChampionCount() const;
    size_t getCardCount() const;
};

#endif