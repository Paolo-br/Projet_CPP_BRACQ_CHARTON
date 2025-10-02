#include <iostream>
#include "Card.h"

Card::Card(std::string name, int cost, Faction faction, std::string type)
    : m_name(name), m_cost(cost), m_faction(faction), m_type(type) 
{
    std::cout << "Carte créée"<< std::endl;
}


Card::~Card() {
    std::cout << "Carte détruite " <<std::endl;
}

std::string Card::getName() {
    return m_name;
}

int Card::getCost() {
    return m_cost;
}

Faction Card::getFaction() {
    return m_faction;
}

std::string Card::getType() {
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


void Card::play(Player owner, Player opponent) {
}
