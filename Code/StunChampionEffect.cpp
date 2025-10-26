#include "StunChampionEffect.h"
#include "Player.h"
#include "InPlayArea.h"
#include "ChampionCard.h"
#include <iostream>
#include <vector>

StunChampionEffect::StunChampionEffect() : Effect(0) {}

void StunChampionEffect::apply(Player& player, Turn& turn) {
    std::cout << "EFFET: Assommer un champion adverse lancé par " << player.getName() << std::endl;
    
    // Vérifier si un adversaire est défini dans le tour
    if (!turn.hasOpponent()) {
        std::cout << "Aucun adversaire défini dans le tour actuel." << std::endl;
        std::cout << "Cet effet sera ignoré (règle: faire autant que possible)" << std::endl;
        return;
    }
    
    Player* opponent = turn.getOpponent();
    InPlayArea& playArea = opponent->getPlayArea();
    std::vector<ChampionCard>& champions = playArea.getChampions();
    
    // Filtrer les champions non-assommés
    std::vector<ChampionCard*> validTargets;
    for (ChampionCard& champion : champions) {
        if (!champion.isStunned()) {
            validTargets.push_back(&champion);
        }
    }
    
    // Vérifier s'il y a des cibles valides
    if (validTargets.empty()) {
        std::cout << opponent->getName() << " n'a aucun champion à assommer !" << std::endl;
        std::cout << "(Règle: faire autant que possible - cet effet est ignoré)" << std::endl;
        return;
    }
    
    // Afficher les champions disponibles
    std::cout << "\nChampions de " << opponent->getName() << " pouvant être assommés:" << std::endl;
    for (size_t i = 0; i < validTargets.size(); ++i) {
        std::cout << (i + 1) << ". " << validTargets[i]->getName()
                  << " (Def: " << validTargets[i]->getRemainingDefense() << ")";
        if (validTargets[i]->isGuard()) {
            std::cout << " [GARDE]";
        }
        std::cout << std::endl;
    }
    
    // Demander au joueur de choisir une cible
    int choice = -1;
    bool validChoice = false;
    
    while (!validChoice) {
        std::cout << player.getName() << ", choisissez un champion à assommer (1-" 
                  << validTargets.size() << "): ";
        std::cin >> choice;
        
        // Vérifier si la saisie est valide
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrée invalide ! Veuillez entrer un nombre." << std::endl;
            continue;
        }
        
        if (choice >= 1 && choice <= static_cast<int>(validTargets.size())) {
            validChoice = true;
        } else {
            std::cout << "Choix invalide ! Choisissez entre 1 et " 
                      << validTargets.size() << std::endl;
        }
    }
    
    // Assommer le champion choisi
    ChampionCard* targetChampion = validTargets[choice - 1];
    std::cout << "\n💥 " << targetChampion->getName() << " est ASSOMMÉ et va en défausse !" << std::endl;
    opponent->stunChampion(*targetChampion);
}

Effect* StunChampionEffect::clone() const {
    return new StunChampionEffect();
}

std::string StunChampionEffect::getName() const {
    return "StunChampionEffect";
}
