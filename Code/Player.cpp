#include "Player.h"
#include "CardsType/ChampionCard.h"
#include "CardsType/ItemCard.h"
#include "CardsType/ActionCard.h"
#include "Effects/GoldEffect.h"
#include "Effects/AttackEffect.h"
#include "Effects/HealEffect.h"


#include <iostream>
#include "Utils.h"

// Constructeur
Player::Player(const std::string& name, int health, const Deck& deck,
               const Hand& hand, const DiscardPile& discardPile)
    : m_name(name), m_health(health), m_gold(0), m_deck(deck), 
      m_hand(hand), m_discardPile(discardPile), m_sacrificeZone(), m_eliminated(false) {}

// Constructeur avec move semantics (pour le chargement)
Player::Player(const std::string& name, int health, Deck&& deck,
               Hand&& hand, DiscardPile&& discardPile)
    : m_name(name), m_health(health), m_gold(0), 
      m_deck(std::move(deck)), m_hand(std::move(hand)), 
      m_discardPile(std::move(discardPile)), m_sacrificeZone(), m_eliminated(false) {
    std::cout << "Constructeur Player avec move semantics: " << m_name << std::endl;
}

// 1. Destructeur
Player::~Player() {
    std::cout << "Destructeur Player: " << m_name << std::endl;
    // Supprimer les cartes de la zone de sacrifice (si présentes)
    for (auto card : m_sacrificeZone) {
        delete card;
    }
    m_sacrificeZone.clear();
}

// 2. Constructeur de copie (profonde)
Player::Player(const Player& other)
    : m_name(other.m_name), m_health(other.m_health), m_gold(other.m_gold),
      m_deck(other.m_deck), m_hand(other.m_hand), 
      m_discardPile(other.m_discardPile), m_playArea(other.m_playArea),
      m_sacrificeZone(), m_eliminated(other.m_eliminated) {
    // Copie profonde de la zone de sacrifice
    for (Card* card : other.m_sacrificeZone) {
        if (card) {
            // Note: Pas de copie profonde des cartes elles-mêmes
            // car elles sont gérées par ailleurs. On ne copie que les pointeurs.
            // MAIS attention: cela signifie que les deux Players partageront
            // les mêmes cartes. Pour une vraie copie profonde, il faudrait cloner.
            m_sacrificeZone.push_back(card);
        }
    }
    std::cout << "Constructeur copie Player: " << m_name << std::endl;
}

// 3. Opérateur d'affectation copie
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        // Nettoyer d'abord la zone de sacrifice existante
        for (auto card : m_sacrificeZone) {
            delete card;
        }
        m_sacrificeZone.clear();
        
        m_name = other.m_name;
        m_health = other.m_health;
        m_gold = other.m_gold;
        m_deck = other.m_deck;
        m_hand = other.m_hand;
        m_discardPile = other.m_discardPile;
        m_playArea = other.m_playArea;
        
        // Copie superficielle de la zone de sacrifice (pointeurs partagés)
        // Note: Pour une vraie copie profonde, il faudrait cloner les cartes
        for (Card* card : other.m_sacrificeZone) {
            if (card) {
                m_sacrificeZone.push_back(card);
            }
        }
        
        m_eliminated = other.m_eliminated;
    }
    std::cout << "Opérateur affectation copie Player: " << m_name << std::endl;
    return *this;
}

// 4. Constructeur de déplacement
Player::Player(Player&& other) noexcept
    : m_name(std::move(other.m_name)), m_health(other.m_health), 
      m_gold(other.m_gold), m_deck(std::move(other.m_deck)),
      m_hand(std::move(other.m_hand)), m_discardPile(std::move(other.m_discardPile)),
      m_playArea(std::move(other.m_playArea)), m_sacrificeZone(std::move(other.m_sacrificeZone)),
      m_eliminated(other.m_eliminated) {
    // Mettre l'autre objet dans un état valide
    other.m_health = 0;
    other.m_gold = 0;
    other.m_eliminated = true;
    other.m_sacrificeZone.clear();
    std::cout << "Constructeur déplacement Player: " << m_name << std::endl;
}

// 5. Opérateur d'affectation déplacement
Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        // Nettoyer d'abord notre zone de sacrifice
        for (auto card : m_sacrificeZone) {
            delete card;
        }
        m_sacrificeZone.clear();
        
        m_name = std::move(other.m_name);
        m_health = other.m_health;
        m_gold = other.m_gold;
        m_deck = std::move(other.m_deck);
        m_hand = std::move(other.m_hand);
        m_discardPile = std::move(other.m_discardPile);
        m_playArea = std::move(other.m_playArea);
        m_sacrificeZone = std::move(other.m_sacrificeZone);
        m_eliminated = other.m_eliminated;
        
        // Mettre l'autre objet dans un état valide
        other.m_health = 0;
        other.m_gold = 0;
        other.m_eliminated = true;
        other.m_sacrificeZone.clear();
    }
    std::cout << "Opérateur affectation déplacement Player: " << m_name << std::endl;
    return *this;
}

// Initialisation du deck de départ
void Player::initializeStarterDeck() {
    m_deck.clear();
    
    // Ajouter 7 cartes Or au deck
    for (int i = 0; i < 7; ++i) {
        std::vector<Effect*> effects;
        effects.push_back(new GoldEffect(1)); // Effet : ajouter 1 Or
        ItemCard* gold = new ItemCard("Or", 0, Faction::None, "Item", effects);
        m_deck.addCard(gold);
    }
    
    // 1 Épée Courte (valeur de Combat = 2, coût = 0)
    std::vector<Effect*> swordEffects;
    swordEffects.push_back(new AttackEffect(2)); // Effet : ajouter 2 Combat
    ItemCard* shortsword = new ItemCard("Épée Courte", 0, Faction::None, "Item", swordEffects);
    m_deck.addCard(shortsword);

    // 1 Dague (valeur de Combat = 1, coût = 0)
    std::vector<Effect*> daggerEffects;
    daggerEffects.push_back(new AttackEffect(1)); // Effet : ajouter 1 Combat
    ItemCard* dagger = new ItemCard("Dague", 0, Faction::None, "Item", daggerEffects);
    m_deck.addCard(dagger);

    // 1 Rubis (valeur d'Or = 2, coût = 0)
    std::vector<Effect*> rubyEffects;
    rubyEffects.push_back(new GoldEffect(2)); // Effet : ajouter 2 Gold
    ItemCard* ruby = new ItemCard("Rubis", 0, Faction::None, "Item", rubyEffects);
    m_deck.addCard(ruby);

    m_deck.shuffle();
    std::cout << m_name << ": deck de départ initialisé (10 cartes)" << std::endl;
}


void Player::discardCard(Card* card) {
    // Ajouter la carte à la défausse
    m_discardPile.add(card);
    std::cout << m_name << " défausse " << card->getName() << "." << std::endl;
}


void Player::discardHand() {
    while (!m_hand.isEmpty()) {
        Card* card = m_hand.draw();
        m_discardPile.add(card);
    }
}

void Player::acquireCard(Card* card, Turn& turn) {
    // Vérifier les flags de manipulation du deck
    bool goesToHand = turn.getNextCardGoesInHand();
    bool goesToTop = turn.getNextCardGoesOnTop();
    bool actionGoesToTop = turn.getNextActionGoesOnTop();
    
    // Réinitialiser les flags après vérification
    turn.resetAcquireFlags();
    
    // Si l'effet "next card in hand" est actif
    if (goesToHand) {
        m_hand.add(card);
        std::cout << "→ " << m_name << " acquiert " << card->getName() << " et la place DIRECTEMENT EN MAIN!" << std::endl;
        return;
    }
    
    // Si l'effet "next card on top" est actif
    if (goesToTop) {
        m_deck.addCardOnTop(card);
        std::cout << "→ " << m_name << " acquiert " << card->getName() << " et la place SUR LE DESSUS DU DECK!" << std::endl;
        return;
    }
    
    // Si l'effet "next action on top" est actif et c'est une Action
    if (actionGoesToTop && card->getType() == "Action") {
        m_deck.addCardOnTop(card);
        std::cout << "→ " << m_name << " acquiert " << card->getName() << "et la place SUR LE DESSUS DU DECK!" << std::endl;
        return;
    }
    
    // Comportement normal : ajouter à la défausse
    m_discardPile.add(card);
    std::cout << m_name << " acquiert " << card->getName() << " et l'ajoute à la défausse." << std::endl;
}

void Player::drawCards(int count) {
    for (int i = 0; i < count; ++i) {
        if (m_deck.isEmpty()) {
            // Mélanger la défausse pour former le nouveau deck
            if (!m_discardPile.isEmpty()) {
                std::cout << m_name << ": deck vide, mélange de la défausse..." << std::endl;
                m_deck = m_discardPile.reshuffleIntoDeck();
            } else {
                std::cout << m_name << ": plus de cartes à piocher !" << std::endl;
                break;
            }
        }
        
        if (!m_deck.isEmpty()) {
            Card* card = m_deck.draw();
            m_hand.add(card);
        }
    }
}

void Player::mobilizeChampions() {
    m_playArea.mobilizeChampions();
}

// Vérifie si le joueur peut être attaqué (pas de Garde mobilisé)
bool Player::canBeAttacked() const {
    return !hasGuardInPlay();
}

// Vérifie si un champion peut être attaqué
bool Player::canAttackChampion(const ChampionCard& champion) const {
    // On ne peut pas attaquer un champion si on a un Garde mobilisé
    // Sauf si le champion ciblé EST un Garde
    if (hasGuardInPlay() && !champion.isGuard()) {
        return false;
    }
    return true;
}

// Attaquer le joueur directement
void Player::attackPlayer(int combatDamage) {
    if (!canBeAttacked()) {
        std::cout << "Impossible d'attaquer " << m_name << " - un Garde protège ! " << std::endl;
        return;
    }
        takeDamage(combatDamage);
    std::cout <<m_name << " attaqué directement pour " << combatDamage << " dégâts!" << std::endl;
}


void Player::takeDamage(int damage) {
    m_health -= damage;
    if (m_health <= 0) {
        m_health = 0;
        m_eliminated = true;
        std::cout << m_name << " est éliminé !" << std::endl;
    }
}

void Player::heal(int amount) {
    m_health += amount;
}

// Attaquer un champion spécifique
void Player::attackChampion(ChampionCard& champion, int combatDamage) {
    if (!canAttackChampion(champion)) {
        std::cout << "Impossible d'attaquer " << champion.getName() << " - protection des Gardes !" << std::endl;
        return;
    }
    
    champion.takeDamage(combatDamage);
    
    // Vérifier si le champion est assommé
    if (champion.isStunned()) {
        stunChampion(champion);
    }
}

ChampionCard* Player::findChampionToAttack() {
    auto& champions = m_playArea.getChampions();
    
    // Priorité 1: Attaquer les Gardes d'abord
    for (auto& champion : champions) {
        if (champion.isGuard() && champion.isReady() && !champion.isStunned()) {
            return &champion;
        }
    }
    
    // Priorité 2: Attaquer les champions normaux
    for (auto& champion : champions) {
        if (champion.isReady() && !champion.isStunned()) {
            return &champion;
        }
    }
    
    return nullptr; // Aucun champion attaquable
}

// Assomme tous les champions qui ont suffisamment de dégâts
void Player::stunChampions() {
    std::vector<ChampionCard>& champions = m_playArea.getChampions();
    
    for(size_t i = 0; i < champions.size(); ) {
        ChampionCard& champion = champions[i];
        if (champion.isStunned()) {
            std::cout << champion.getName() << " est assommé !" << std::endl;
            // Créer une copie sur le tas avant de l'enlever de la zone de jeu
            ChampionCard* discardedChampion = new ChampionCard(champion);
            m_discardPile.add(discardedChampion);
            champions.erase(champions.begin() + i);
        
        } else {
            i++; 
        }
    }
}

// Reset tous les dégâts des champions en fin de tour
void Player::resetChampionDamage() {
    for (auto& champion : m_playArea.getChampions()) {
        champion.resetDamage();
    }
    std::cout << m_name << ": dégâts des champions resetés" << std::endl;
}

bool Player::hasGuardInPlay() const {
    return m_playArea.hasGuardInPlay();
}

void Player::stunChampion(ChampionCard& champion) {
    // Créer une copie sur le tas avant de retirer le champion de la zone de jeu
    ChampionCard* discardedChampion = new ChampionCard(champion);
    m_playArea.removeChampion(champion);
    m_discardPile.add(discardedChampion);
    std::cout << m_name << ": Champion " << champion.getName() << " assommé !" << std::endl;
}

void Player::sacrificeChampion(ChampionCard& champion) {
    m_playArea.removeChampion(champion);
    // Créer une copie du Champion pour la zone de sacrifice
    ChampionCard* sacrificedChampion = new ChampionCard(champion);
    addToSacrificeZone(sacrificedChampion);
    std::cout << m_name << ": Champion " << champion.getName() << " sacrifié !" << std::endl;
}

void Player::addChampionToPlayArea(ChampionCard& champion) {
    m_playArea.addChampion(champion);
}

void Player::displayStatus() const {
    std::cout << m_name << " | PV: " << m_health 
              << " | Main: " << m_hand.size() 
              << " cartes | Deck: " << m_deck.size() 
              << " | Défausse: " << m_discardPile.size()
              << " | Champions: " << m_playArea.getChampionCount() 
              << " | " << (m_eliminated ? "ÉLIMINÉ" : "En jeu") << std::endl;
    
    // Afficher les champions en jeu en utilisant l'affichage de Raphael
    const std::vector<ChampionCard>& champions = const_cast<InPlayArea&>(m_playArea).getChampions();
    if (!champions.empty()) {
        std::cout << "  Champions en jeu:" << std::endl;
        std::vector<Card*> cards;
        for (const auto& champion : champions) {
            cards.push_back(const_cast<ChampionCard*>(&champion));
        }
        // Utiliser le renderer centralisé pour afficher les champions élégamment
        Utils::displayAllCards(cards, 2, 0);
    }
}


// Getters
std::string Player::getName() const { return m_name; }
int Player::getHealth() const { return m_health; }
Deck& Player::getDeck() { return m_deck; }
Hand& Player::getHand() { return m_hand; }
DiscardPile& Player::getDiscardPile() { return m_discardPile; }
InPlayArea& Player::getPlayArea() { return m_playArea; }
std::vector<Card*>& Player::getSacrificeZone() { return m_sacrificeZone; }

bool Player::isEliminated() const { return m_eliminated; }

int Player::getGold(){ return m_gold; }


void Player::addCardToPlayArea(Card* card) {
    if (card->getType() == "Action" || card->getType() == "Item") {
        m_playArea.add(card);
        std::cout << m_name << ": " << card->getName() << " ajoutée à la zone de jeu." << std::endl;
    } else if (card->getType() == "Champion") {
        // Cast en ChampionCard si nécessaire
        ChampionCard* champion = dynamic_cast<ChampionCard*>(card);
        if (champion) {
            addChampionToPlayArea(*champion);
        } else {
            std::cerr << "Erreur: Impossible de caster la carte en ChampionCard." << std::endl;
        }
    } else {
        std::cerr << "Erreur: Type de carte non géré pour la zone de jeu." << std::endl;
    }
}


// Setters
void Player::setName(const std::string& name) { m_name = name; }
void Player::setHealth(int health) { m_health = health; }
void Player::setEliminated(bool eliminated) { m_eliminated = eliminated; }
void Player::setGold(int gold) { m_gold = gold; }

// Gestion de la Zone de Sacrifice
void Player::addToSacrificeZone(Card* card) {
    if (card) {
        m_sacrificeZone.push_back(card);
        std::cout << "→ " << card->getName() << " placée dans la Zone de Sacrifice de " << m_name << std::endl;
    }
}

void Player::viewSacrificeZone() const {
    std::cout << "\n╔═══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         ZONE DE SACRIFICE - " << m_name << std::string(24 - m_name.length(), ' ') << "║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════╝" << std::endl;
    
    if (m_sacrificeZone.empty()) {
        std::cout << "La zone de sacrifice est vide." << std::endl;
    } else {
        std::cout << "Nombre de cartes: " << m_sacrificeZone.size() << std::endl;
        std::cout << "\nCartes sacrifiées:" << std::endl;
        for (size_t i = 0; i < m_sacrificeZone.size(); ++i) {
            std::cout << (i + 1) << ". " << m_sacrificeZone[i]->getName() 
                      << " (" << m_sacrificeZone[i]->getType() << ")" << std::endl;
        }
    }
    std::cout << "═══════════════════════════════════════════════" << std::endl;
}
