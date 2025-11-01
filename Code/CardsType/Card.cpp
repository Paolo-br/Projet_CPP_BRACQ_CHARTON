#include <iostream>
#include <string>
#include "Card.h"
#include "../Faction.h"
#include "../Player.h"
#include "../Turn.h"   


Card::Card(const std::string name, int cost, Faction faction,const std::string type)
    : m_name(name), m_cost(cost), m_faction(faction), m_type(type) 
{
    std::cout << "Carte créée"<< std::endl;
}



std::string Card::getName() const {
    return m_name;
}

int Card::getCost() const {
    return m_cost;
}

Faction Card::getFaction() const {
    return m_faction;
}

std::string Card::getType() const {
    return m_type;
}

void Card::setName(std::string name) {
    m_name = name;
}

void Card::setCost(int cost) {
    m_cost = cost;
}

void Card::setFaction(Faction faction) {
    m_faction = faction;
}

void Card::setType(std::string type) {
    m_type = type;
}


void Card::play(Player& owner, Player& opponent) {
    std::cout << "Carte jouée : " << m_name << std::endl;
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
}


bool Card::operator==(const Card& other) const {
    return m_name == other.m_name; // Comparez les cartes par leur nom
}
