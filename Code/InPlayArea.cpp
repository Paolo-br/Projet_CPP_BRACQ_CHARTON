#include "InPlayArea.h"
#include <iostream>

InPlayArea::InPlayArea() {
    std::cout << "Constructeur InPlayArea vide" << std::endl;
}

InPlayArea::InPlayArea(std::vector<Card*> cards, std::vector<ChampionCard> champions)
    : m_cards(cards), m_champions(champions) {
    std::cout << "Constructeur InPlayArea avec " << cards.size() 
              << " cartes et " << champions.size() << " champions" << std::endl;
}

InPlayArea::~InPlayArea() {
    std::cout << "Destructeur InPlayArea" << std::endl;
    // Supprimer les cartes non-champion détenues dans la zone de jeu
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
    m_champions.clear();
}

// Gestion des cartes normales
void InPlayArea::add(Card* card) {
    m_cards.push_back(card);
}

void InPlayArea::clear() {
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
}

std::vector<Card*>& InPlayArea::getCards() {
    return m_cards;
}

// Gestion des Champions
void InPlayArea::addChampion(ChampionCard champion) {
    m_champions.push_back(champion);
    std::cout << "Champion ajouté à la zone de jeu: " << champion.getName() << std::endl;
}

void InPlayArea::removeChampion(ChampionCard& champion) {
    for (size_t i = 0; i < m_champions.size(); ++i) {
        if (m_champions[i].getName() == champion.getName()) {
            m_champions.erase(m_champions.begin() + i);
            std::cout << "Champion retiré de la zone de jeu: " << champion.getName() << std::endl;
            return;
        }
    }
}

std::vector<ChampionCard>& InPlayArea::getChampions() {
    return m_champions;
}

const std::vector<ChampionCard>& InPlayArea::getChampions() const {
    return m_champions;
}


bool InPlayArea::hasGuardInPlay() const {
    for (const auto& champion : m_champions) {
        if (champion.isGuard() && champion.isReady()) {
            return true;
        }
    }
    return false;
}

void InPlayArea::mobilizeChampions() {
    for (auto& champion : m_champions) {
        champion.setReady(true);
    }
    std::cout << "Tous les Champions sont mobilisés" << std::endl;
}

void InPlayArea::clearAll() {
    for (auto card : m_cards) {
        delete card;
    }
    m_cards.clear();
    m_champions.clear();
    std::cout << "Zone de jeu complètement vidée" << std::endl;
}

size_t InPlayArea::getChampionCount() const {
    return m_champions.size();
}

size_t InPlayArea::getCardCount() const {
    return m_cards.size();
}