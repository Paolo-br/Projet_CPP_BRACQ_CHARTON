#include "ItemCard.h"
#include "Player.h"
#include "Turn.h"
#include "AllyAbility.h"
#include "SacrificeAbility.h"

#include <iostream>

ItemCard::ItemCard(const std::string& name, int cost, Faction faction, const std::string& type,
                   const std::vector<Effect*>& effects,
                   const std::vector<Ability*>& abilities)
    : Card(name, cost, faction, type), m_effects(effects), m_abilities(abilities) {}


// 1. Destructeur - Nettoie tous les effets et toutes les capacités
ItemCard::~ItemCard() {
    std::cout << "Destructeur ItemCard: " << this->getName() << std::endl;
    for (Effect* effect : m_effects) {
        delete effect;
    }
    m_effects.clear();
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    m_abilities.clear();
}

// 2. Constructeur de copie (COPIE PROFONDE)
ItemCard::ItemCard(const ItemCard& other)
    : Card(other), m_type(other.m_type) {
    for (auto effect : other.m_effects) {
        m_effects.push_back(effect->clone());
    }
    for (auto ability : other.m_abilities) {
        m_abilities.push_back(ability->clone());
    }
}

// 3. Opérateur d'affectation copie
ItemCard& ItemCard::operator=(const ItemCard& other) {
    if (this != &other) {
        Card::operator=(other);
        m_type = other.m_type;
        for (auto effect : m_effects) {
            delete effect;
        }
        m_effects.clear();
        for (auto effect : other.m_effects) {
            m_effects.push_back(effect->clone());
        }
        for (auto ability : m_abilities) {
            delete ability;
        }
        m_abilities.clear();
        for (auto ability : other.m_abilities) {
            m_abilities.push_back(ability->clone());
        }
    }
    return *this;
}


// 4. Constructeur de déplacement
ItemCard::ItemCard(ItemCard&& other) noexcept
    : Card(std::move(other)), m_type(std::move(other.m_type)), 
      m_effects(std::move(other.m_effects)), m_abilities(std::move(other.m_abilities)) {
    other.m_effects.clear();
    other.m_abilities.clear();
}


// 5. Opérateur d'affectation déplacement
ItemCard& ItemCard::operator=(ItemCard&& other) noexcept {
    if (this != &other) {
        Card::operator=(std::move(other));
        m_type = std::move(other.m_type);
        m_effects = std::move(other.m_effects);
        m_abilities = std::move(other.m_abilities);
        other.m_effects.clear();
        other.m_abilities.clear();
    }
    return *this;
}

void ItemCard::executeEffects(Player& player, Turn& turn) {
    for (auto effect : m_effects) {
        effect->apply(player, turn);
    }
}


void ItemCard::play(Player& owner, Player& opponent) {
    std::cout<<"Joueur "<<owner.getName()<<" joue sur"<<opponent.getName()<<std::endl;

}

std::string ItemCard::getName() const {
    return Card::getName();  
}

void ItemCard::printItemCard(){
    int n = Utils::countChar(getName());
    n = n+ Utils::countSpaces(getName());
    std::vector<Effect*> liste_effet=m_effects;
    Faction faction = getFaction();

    Utils::printBarre(n,0);
    Utils::printCentered(getName(),n, "", "bold");
    Utils::printBarre(n,1);
    Utils::printCentered(getType(),n, "", "italic");
    Utils::printVide(n);
    Utils::printVide(n);
    Utils::printVide(n);
    for (Effect* e : liste_effet) {
        if(e->getName()=="AttackEffect"){Utils::printCentered(e->getValue(), 16, "red");}
        if(e->getName()=="HealEffect"){Utils::printCentered(e->getValue(), 16, "green");}
        if(e->getName()=="DrawEffect"){Utils::printCentered(e->getValue(), 16, "blue");}
        if(e->getName()=="SacrificeEffect"){Utils::printCentered(e->getValue(), 16, "grey");}     
    }
    
    if(factionToString(faction) != "Aucune"){
       Utils::printCentered(factionToString(faction),n);
    }
    Utils::printBarre(n,1);
}


void ItemCard::printItemCard(std::vector<ItemCard*>& cards){

    for(size_t i=0;i<cards.size();i++){
        for(size_t i=0;i<cards.size();i++){
            std::string name = cards[i]->getName();
            int n = Utils::countChar(name);
            n = n+ Utils::countSpaces(getName());
            Utils::printCentered(name, n,"","",false);
        }
    }
}

bool ItemCard::hasAllyAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<AllyAbility*>(ability)) {
            return true;
        }
    }
    return false;
}

bool ItemCard::hasSacrificeAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<SacrificeAbility*>(ability)) {
            return true;
        }
    }
    return false;
}
