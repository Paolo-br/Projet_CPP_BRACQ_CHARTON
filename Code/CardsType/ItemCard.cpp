#include "ItemCard.h"
#include "../Player.h"
#include "../Turn.h"
#include "../Abilities/AllyAbility.h"
#include "../Abilities/SacrificeAbility.h"

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
    : Card(other) {
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
    : Card(std::move(other)), 
      m_effects(std::move(other.m_effects)), m_abilities(std::move(other.m_abilities)) {
    other.m_effects.clear();
    other.m_abilities.clear();
}


// 5. Opérateur d'affectation déplacement
ItemCard& ItemCard::operator=(ItemCard&& other) noexcept {
    if (this != &other) {
        Card::operator=(std::move(other));
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

std::tuple<int,int> ItemCard::display(int row, int col){
    int indice = 1;
    row++;
    int n = Utils::countChar(Utils::EntireName(getName(),getCost()))-2;
    n = n - Utils::countSpaces(getName());
    if(n<16) n=16;
    Faction faction = getFaction();
    Utils::moveCursor(row,col);row++;
    Utils::printBarre(n+1,0);
    Utils::moveCursor(row,col);row++;
    Utils::printCenteredName(getName(),n,getCost());
    Utils::moveCursor(row,col);row++;
    Utils::printBarre(n,1);
    Utils::moveCursor(row,col);row++;
    Utils::printCentered(getType(),n, "", "italic");
    Utils::moveCursor(row,col);row++;
    Utils::printVide(n);
    Utils::moveCursor(row,col);row++;
    Utils::printVide(n);
    Utils::moveCursor(row,col);row++;
    Utils::printVide(n);
    Utils::moveCursor(row,col);

    Utils::printEffect(this,row,col,indice,n);

    if(factionToString(faction) != "Aucune"){
        Utils::printCentered(factionToString(faction),n);
        Utils::moveCursor(row+indice,col);
        indice++;
    }
    Utils::printBarre(n,1);
    return std::make_tuple(row+indice,n+2);  // Retourner la largeur, pas la position
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
