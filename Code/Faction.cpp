#include <iostream>
#include "Faction.h"

std::string factionToString(Faction f) {
    switch (f) {
        case Faction::Guilde:    return "Guilde";
        case Faction::Necros:    return "Nécros";
        case Faction::Imperial:  return "Impérial";
        case Faction::Sauvage:   return "Sauvage";
        default:                 return "Inconnu";
    }
}
