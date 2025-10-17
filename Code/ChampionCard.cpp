#include <iostream>
#include <string>
#include "ChampionCard.h"
#include "Player.h"
#include "Turn.h"

ChampionCard::ChampionCard(const std::string name, int cost, Faction faction,const std::string type, 
                           int defense, bool isGuard, bool isTapped, std::vector<Ability*> abilities)
    : Card(name, cost, faction, type), m_defense(defense), m_isGuard(isGuard), 
      m_isTapped(isTapped), m_abilities(abilities)
{
    std::cout << "Champion créé: " << name << " (Défense: " << defense 
         << ", Garde: " << (isGuard ? "Oui" : "Non") 
         << ", État: " << (isTapped ? "Démobilisé" : "Mobilisé") << ")" << std::endl;
}

ChampionCard::~ChampionCard() {
    // Libérez la mémoire des objets Ability
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    std::cout << "Champion détruite " <<std::endl;
}

// CONSTRUCTEUR COPIE
ChampionCard::ChampionCard(const ChampionCard& other)
    : Card(other), m_defense(other.m_defense), m_isGuard(other.m_isGuard),
      m_isTapped(other.m_isTapped), m_currentDamage(other.m_currentDamage) {
    
    // Copie profonde des abilities
    for (auto ability : other.m_abilities) {
        m_abilities.push_back(ability);
    }
}

// OPÉRATEUR AFFECTATION COPIE
ChampionCard& ChampionCard::operator=(const ChampionCard& other) {
    if (this != &other) {
        Card::operator=(other);
        for (Ability* ability : m_abilities) {
            delete ability;
        }
        
        m_defense = other.m_defense;
        m_isGuard = other.m_isGuard;
        m_isTapped = other.m_isTapped;
        m_currentDamage = other.m_currentDamage;
        
        // Copie profonde
        for (auto ability : other.m_abilities) {
            m_abilities.push_back(ability);
        }
    }
    return *this;
}

// CONSTRUCTEUR DÉPLACEMENT
ChampionCard::ChampionCard(ChampionCard&& other) noexcept
    : Card(std::move(other)), m_defense(other.m_defense), m_isGuard(other.m_isGuard),
      m_isTapped(other.m_isTapped), m_currentDamage(other.m_currentDamage),
      m_abilities(std::move(other.m_abilities)) {
    
    other.m_abilities.clear();
}

// OPÉRATEUR AFFECTATION DÉPLACEMENT
ChampionCard& ChampionCard::operator=(ChampionCard&& other) noexcept {
    if (this != &other) {
        Card::operator=(std::move(other));
        for (Ability* ability : m_abilities) {
        delete ability;
    }
        
        m_defense = other.m_defense;
        m_isGuard = other.m_isGuard;
        m_isTapped = other.m_isTapped;
        m_currentDamage = other.m_currentDamage;
        m_abilities = std::move(other.m_abilities);
                
        other.m_abilities.clear();
        return *this;
    
    }
    return *this;
}
    
void ChampionCard::executeEffects(Player& player, Turn& turn) {
    std::cout << this->getName()<< " entre en jeu ! Pour le joueur" << player.getName()<<"avec en or :"<<turn.getGoldReserve()<< std::endl;
    
    // Si le champion a une capacité qui se déclenche à l'entrée en jeu
    /**
    for (auto ability : m_abilities) {
        if (ability->isEnterPlayAbility()) {
            ability->execute(player, turn);
        }
    }
        **/
}


void ChampionCard::activate() {
    if (!m_isTapped) {
        std::cout << this->getName() << " active sa capacité !" << std::endl;
        m_isTapped = true; // Le champion se démobilise après activation
    } else {
        std::cout << this->getName() << " est déjà démobilisé, ne peut pas activer !" << std::endl;
    }
}

void ChampionCard::sacrifice() {
    std::cout << this->getName() << " est sacrifié !" << std::endl;
    // La carte sera placée dans la Zone de Sacrifice
}

void ChampionCard::defend() {
    std::cout << this->getName() << " se met en position défensive !" << std::endl;
    // Logique de défense spécifique si nécessaire
    // Par exemple, pourrait augmenter temporairement la défense, etc.
}


void ChampionCard::resetDamage() {
    m_currentDamage = 0;
}

bool ChampionCard::isStunned() const {
    return m_currentDamage >= m_defense;
}

std::vector<Ability*> ChampionCard::getAbilities() {
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
    std::cout << this->getName() << ": défense modifiée à " << defense << std::endl;
}

void ChampionCard::setIsGuard(bool isGuard) {
    m_isGuard = isGuard;
    std::cout << this->getName() << ": statut Garde modifié à " << (isGuard ? "Oui" : "Non") << std::endl;
}

void ChampionCard::setIsTapped(bool isTapped) {
    m_isTapped = isTapped;
    std::cout << this->getName() << ": état modifié à " << (isTapped ? "Démobilisé" : "Mobilisé") << std::endl;
}

void ChampionCard::setAbilities(std::vector<Ability*> abilities) {
    m_abilities = abilities;
}

void ChampionCard::setReady(bool ready) {
    m_isTapped = !ready; // ready = true → mobilisé (non tapped)
    std::cout << this->getName() << " est maintenant " 
         << (ready ? "mobilisé" : "démobilisé") << std::endl;
}

bool ChampionCard::isGuard() const {
    return m_isGuard;
}

bool ChampionCard::isReady() const {
    return !m_isTapped; // Ready = non démobilisé
}

void ChampionCard::takeDamage(int damage) {
    std::cout << this->getName() << " subit " << damage << " dégâts";
    
    if (damage >= m_defense) {
        std::cout << " et est assommé !" << std::endl;
        // Le champion sera placé dans la défausse
    } else {
        std::cout << " (défense restante: " << (m_defense - damage) << ")" << std::endl;
        // Les dégâts ne sont pas cumulatifs entre les tours
    }
}


void ChampionCard::play(Player& owner, Player& opponent) {
    std::cout << "Champion joué : " << this->getName() << std::endl;
    std::cout << "Joueur : " << owner.getName() << std::endl;
    std::cout << "Opposant : " << opponent.getName() << std::endl;
    
    // Le champion entre en jeu mobilisé (ready)
    setReady(true);
}

void ChampionCard::printChampionCard(){
    
    std::vector<Ability*> liste_abi=m_abilities;
    int n = Utils::countChar(getName());
    n = n+ Utils::countSpaces(getName());

    Faction faction = getFaction();
    Utils::printBarre(n,0);
    Utils::printCentered(getName(),n, "", "bold");
    Utils::printBarre(n,1);
    Utils::printCentered(getType(),n, "", "italic");
    Utils::printVide(n);
    Utils::printVide(n);
    Utils::printVide(n);
    Utils::printVide(n);
    
    for (Ability* e : liste_abi) {
        std::vector<Effect*> temp = e->getEffect();
        if(e->getName()=="ActivateAbility"){
            Utils::printCentered("ActivateAbility",n);
            for(Effect* e1 :temp){
                if(e1->getName()=="AttackEffect"){Utils::printCentered(e1->getValue(), n, "red");}
                if(e1->getName()=="HealEffect"){Utils::printCentered(e1->getValue(), n, "green");}
                if(e1->getName()=="DrawEffect"){Utils::printCentered(e1->getValue(), n, "blue");}
                if(e1->getName()=="SacrificeEffect"){Utils::printCentered(e1->getValue(), n, "grey");}
            }
        }
        else if(e->getName()=="AllyAbility"){
            Utils::printCentered("AllyAbility",n);
            for(Effect* e1 :temp){
                if(e1->getName()=="AttackEffect"){Utils::printCentered(e1->getValue(), n, "red");}
                if(e1->getName()=="HealEffect"){Utils::printCentered(e1->getValue(), n, "green");}
                if(e1->getName()=="DrawEffect"){Utils::printCentered(e1->getValue(), n, "blue");}
                if(e1->getName()=="SacrificeEffect"){Utils::printCentered(e1->getValue(), n, "grey");}
            }
        }
    }
    
    if(factionToString(faction) != "Aucune"){
        Utils::printCentered(factionToString(faction),n+1);
    }
    if(getIsGuard()==true){
        Utils::printCentered("Guard",n,"","bold");
    }
    Utils::printBarre(n,1);
}