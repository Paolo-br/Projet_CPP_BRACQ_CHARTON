#ifndef __FACTION_H
#define __FACTION_H
#include <string>

enum class Faction {
    None,
    Guilde,
    Necros,
    Imperial,
    Sauvage
};


std::string factionToString(Faction f);

#endif
