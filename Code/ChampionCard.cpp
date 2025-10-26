#include <iostream>
#include <string>
#include "ChampionCard.h"
#include "Player.h"
#include "Turn.h"
#include "ActivateAbility.h"
#include "AllyAbility.h"
#include "SacrificeAbility.h"

ChampionCard::ChampionCard(const std::string name, int cost, Faction faction, const std::string type, 
                           int defense, bool isGuard, std::vector<Ability*> abilities)
    : Card(name, cost, faction, type), 
      m_defense(defense), 
      m_isGuard(isGuard), 
      m_isTapped(false),  // Les champions entrent en jeu MOBILISÉS (tapped = false)
      m_currentDamage(0), // Initialiser les dégâts à 0
      m_abilities(abilities)
{
    std::cout << "Champion créé: " << name << " (Défense: " << defense 
         << ", Garde: " << (isGuard ? "Oui" : "Non") << ", État: Mobilisé)" << std::endl;
}

ChampionCard::~ChampionCard() {
    // Libération de la mémoire des objets Ability
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    m_abilities.clear();
    std::cout << "Champion détruit: " << getName() << std::endl;
}

// CONSTRUCTEUR COPIE - COPIE PROFONDE
ChampionCard::ChampionCard(const ChampionCard& other)
    : Card(other), 
      m_defense(other.m_defense), 
      m_isGuard(other.m_isGuard),
      m_isTapped(other.m_isTapped), 
      m_currentDamage(other.m_currentDamage) {
    
    std::cout << "Constructeur copie ChampionCard: " << other.getName() << std::endl;
    
    // Copie profonde des abilities avec clone()
    for (const auto& ability : other.m_abilities) {
        if (ability) {
            m_abilities.push_back(ability->clone());
        }
    }
}

// OPÉRATEUR AFFECTATION COPIE
ChampionCard& ChampionCard::operator=(const ChampionCard& other) {
    std::cout << "Opérateur affectation copie ChampionCard" << std::endl;
    
    if (this != &other) {
        // Appel à l'opérateur d'affectation de la classe de base
        Card::operator=(other);
        
        // Nettoyer les abilities existantes
        for (Ability* ability : m_abilities) {
            delete ability;
        }
        m_abilities.clear();
        
        // Copier les attributs
        m_defense = other.m_defense;
        m_isGuard = other.m_isGuard;
        m_isTapped = other.m_isTapped;
        m_currentDamage = other.m_currentDamage;
        
        // Copie profonde des abilities avec clone()
        for (const auto& ability : other.m_abilities) {
            if (ability) {
                m_abilities.push_back(ability->clone());
            }
        }
    }
    return *this;
}

// CONSTRUCTEUR DÉPLACEMENT
ChampionCard::ChampionCard(ChampionCard&& other) noexcept
    : Card(std::move(other)), 
      m_defense(other.m_defense), 
      m_isGuard(other.m_isGuard),
      m_isTapped(other.m_isTapped), 
      m_currentDamage(other.m_currentDamage),
      m_abilities(std::move(other.m_abilities)) {
    
    std::cout << "Constructeur déplacement ChampionCard" << std::endl;
    other.m_abilities.clear();
}

// OPÉRATEUR AFFECTATION DÉPLACEMENT
ChampionCard& ChampionCard::operator=(ChampionCard&& other) noexcept {
    std::cout << "Opérateur affectation déplacement ChampionCard" << std::endl;
    
    if (this != &other) {
        // Appel à l'opérateur d'affectation déplacement de la classe de base
        Card::operator=(std::move(other));
        
        // Nettoyer les abilities existantes
        for (Ability* ability : m_abilities) {
            delete ability;
        }
        m_abilities.clear();
        
        // Transférer les attributs
        m_defense = other.m_defense;
        m_isGuard = other.m_isGuard;
        m_isTapped = other.m_isTapped;
        m_currentDamage = other.m_currentDamage;
        m_abilities = std::move(other.m_abilities);
        
        other.m_abilities.clear();
    }
    return *this;
}
    
// Exécute les effets lorsque le champion entre en jeu
void ChampionCard::executeEffects(Player& player, Turn& turn) {
    std::cout<< player.getName()<<turn.getCombatReserve()<<std::endl;    
    // Les champions n'ont généralement pas d'effets immédiats à l'entrée en jeu
    // Leurs capacités doivent être activées explicitement
}

// Active la capacité principale du champion (si non démobilisé)
void ChampionCard::activateAbility(Player& owner, Turn& turn) {
    if (m_isTapped) {
        std::cout << getName() << " est démobilisé et ne peut pas être activé !" << std::endl;
        return;
    }
    
    if (isStunned()) {
        std::cout << getName() << " est assommé et ne peut pas être activé !" << std::endl;
        return;
    }
    
    std::cout << getName() << " active sa capacité !" << std::endl;
    
    // Chercher et déclencher l'ActivateAbility
    for (auto& ability : m_abilities) {
        if (dynamic_cast<ActivateAbility*>(ability)) {
            ability->trigger(owner, turn);
        }
    }
    
    // Le champion se démobilise après activation
    m_isTapped = true;
    std::cout << getName() << " se démobilise" << std::endl;
}

// Déclenche l'effet Allié
void ChampionCard::triggerAllyAbility(Player& owner, Turn& turn) {
    std::cout << getName() << " déclenche son effet Allié !" << std::endl;
    
    for (auto& ability : m_abilities) {
        if (dynamic_cast<AllyAbility*>(ability)) {
            ability->trigger(owner, turn);
        }
    }
}

// Déclenche l'effet Sacrifice et détruit le champion
void ChampionCard::triggerSacrificeAbility(Player& owner, Turn& turn) {
    std::cout << getName() << " est sacrifié pour déclencher sa capacité !" << std::endl;
    
    for (auto& ability : m_abilities) {
        if (dynamic_cast<SacrificeAbility*>(ability)) {
            ability->trigger(owner, turn);
        }
    }
}

// Sacrifie le champion (sans déclencher l'effet)
void ChampionCard::sacrifice(Player& owner) {
    std::cout << getName() << " est sacrifié !" << "Pour le joueur "<<owner.getName()<<std::endl;
    // La carte sera retirée de la zone de jeu par le Player
}


// Gestion des dégâts
void ChampionCard::takeDamage(int damage) {
    m_currentDamage += damage;
    std::cout << getName() << " subit " << damage << " dégâts";
    
    if (isStunned()) {
        std::cout << " et est assommé ! (Dégâts: " << m_currentDamage 
                  << "/" << m_defense << ")" << std::endl;
    } else {
        std::cout << " (Défense restante: " << getRemainingDefense() 
                  << "/" << m_defense << ")" << std::endl;
    }
}

void ChampionCard::resetDamage() {
    if (m_currentDamage > 0) {
        std::cout << getName() << " récupère (dégâts réinitialisés)" << std::endl;
    }
    m_currentDamage = 0;
}

bool ChampionCard::isStunned() const {
    return m_currentDamage >= m_defense;
}

// Getters
std::vector<Ability*> ChampionCard::getAbilities() const {
    return m_abilities;
}

int ChampionCard::getDefense() const {
    return m_defense;
}

bool ChampionCard::getIsGuard() const {
    return m_isGuard;
}

bool ChampionCard::getIsTapped() const {
    return m_isTapped;
}

// Setters
void ChampionCard::setDefense(int defense) {
    m_defense = defense;
    std::cout << getName() << ": défense modifiée à " << defense << std::endl;
}

void ChampionCard::setIsGuard(bool isGuard) {
    m_isGuard = isGuard;
    std::cout << getName() << ": statut Garde modifié à " 
              << (isGuard ? "Oui" : "Non") << std::endl;
}

void ChampionCard::setIsTapped(bool isTapped) {
    m_isTapped = isTapped;
    std::cout << getName() << ": état modifié à " 
              << (isTapped ? "Démobilisé" : "Mobilisé") << std::endl;
}

void ChampionCard::setAbilities(std::vector<Ability*> abilities) {
    // Nettoyer les anciennes abilities
    for (Ability* ability : m_abilities) {
        delete ability;
    }
    m_abilities.clear();
    
    m_abilities = abilities;
}

void ChampionCard::setReady(bool ready) {
    m_isTapped = !ready; // ready = true → mobilisé (non tapped)
    std::cout << getName() << " est maintenant " 
              << (ready ? "mobilisé" : "démobilisé") << std::endl;
}

// Vérification d'état
bool ChampionCard::isGuard() const {
    return m_isGuard;
}

bool ChampionCard::isReady() const {
    return !m_isTapped && !isStunned(); // Ready = mobilisé ET non assommé
}

// Vérification des abilities
bool ChampionCard::hasActivateAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<ActivateAbility*>(ability)) {
            return true;
        }
    }
    return false;
}

bool ChampionCard::hasAllyAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<AllyAbility*>(ability)) {
            return true;
        }
    }
    return false;
}

bool ChampionCard::hasSacrificeAbility() const {
    for (const auto& ability : m_abilities) {
        if (dynamic_cast<SacrificeAbility*>(ability)) {
            return true;
        }
    }
    return false;
}


// Jouer le champion
void ChampionCard::play(Player& owner, Player& opponent) {
    std::cout << "═══════════════════════════════════════════════" << std::endl;
    std::cout << owner.getName() << " joue le champion: " << getName() << std::endl;
    std::cout << "═══════════════════════════════════════════════" << std::endl;
    
    // Le champion entre en jeu mobilisé (déjà défini dans le constructeur)
    // Il peut être activé immédiatement durant la Phase Principale
    m_currentDamage = 0;
    
    std::cout << "→ " << getName() << " entre en jeu mobilisé !" << " contre le joueur " << opponent.getName() << std::endl;
    
    // Afficher les caractéristiques
    std::cout << "   Défense: " << m_defense;
    if (m_isGuard) {
        std::cout << " [GARDE]";
    }
    std::cout << std::endl;
    
    // Afficher les capacités
    if (hasActivateAbility()) {
        std::cout << " Capacité d'activation disponible" << std::endl;
    }
    if (hasAllyAbility()) {
        std::cout << " Capacité alliée disponible" << std::endl;
    }
    if (hasSacrificeAbility()) {
        std::cout << "  Capacité de sacrifice disponible" << std::endl;
    }
    
    std::cout << "═══════════════════════════════════════════════" << std::endl;
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