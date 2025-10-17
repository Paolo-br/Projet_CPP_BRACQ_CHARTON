#include "StunChampionEffect.h"
#include "Player.h"
#include "Game.h"
#include "ChampionCard.h"
#include <iostream>

StunChampionEffect::StunChampionEffect() : Effect(0) {}

void StunChampionEffect::apply(Player& player, Turn& turn) {
    (void)turn; // Unused
    (void)player; // Unused - nécessite le contexte du jeu
    
    std::cout << "Effet: Assommer un champion adverse (à implémenter dans Game)" << std::endl;
    //NOTE A MOI MEME : Nécessite l'accès aux adversaires
    // Elle devra être implémentée au niveau de Game, pas directement dans Effect
}

Effect* StunChampionEffect::clone() const {
    return new StunChampionEffect();
}

std::string StunChampionEffect::getName() const {
    return "StunChampionEffect";
}
