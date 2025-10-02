#ifndef __FACTION_H
#define __FACTION_H

enum class Faction {
    Guilde,
    Necros,
    Imperial,
    Sauvage
};


std::string factionToString(Faction f);

#endif
