#include <iostream>
#include <string>
#include <list>
#include "ChampionCard.h"

ChampionCard::ChampionCard(std::string name, int cost, Faction faction, std::string type, int defense, bool isGuard, bool isTapped, std::list<Ability*> abilities)
    : Card(name, cost, faction, type), m_defense(defense), m_isGuard(isGuard), m_isTapped(isTapped), m_abilities(abilities)
{
    std::cout << "Champion créée"<< std::endl;
}

ChampionCard::~ChampionCard() {
    // Libérez la mémoire des objets Ability
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    std::cout << "Champion détruite " <<std::endl;
}

void ChampionCard::defend() {
    std::cout << "Champion défend" << std::endl;
}

void ChampionCard::activate() {
    std::cout << "Champion activée" << std::endl;
}
void ChampionCard::sacrifice() {
    std::cout << "Champion sacrifiée" << std::endl;
}

std::list<Ability*> ChampionCard::getAbilities() {
    return m_abilities;
}

int ChampionCard::getDefense() {
    return m_defense;
}
bool ChampionCard::getIsGuard() {
    return m_isGuard;
}
bool ChampionCard::getIsTapped() {
    return m_isTapped;
}

void ChampionCard::setDefense(int defense) {
    m_defense = defense;
}
void ChampionCard::setIsGuard(bool isGuard) {
    m_isGuard = isGuard;
}
void ChampionCard::setIsTapped(bool isTapped) {
    m_isTapped = isTapped;
}
void ChampionCard::setAbilities(std::list<Ability*> abilities) {
    m_abilities = abilities;
}

void ChampionCard::play(Player& owner, Player& opponent) {
    std::cout << "Champion joué : " << this->getName() << std::endl;
     std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}

