#ifndef __CONDITIONTYPE_H
#define __CONDITIONTYPE_H

#include <iostream>
#include <string>

enum class ConditionType {
    ChampionCount,          
    GuardCount,             
    FactionCardCount,       
    OtherChampionCount,     
    OtherGuardCount         
};

std::string conditionTypeToString(ConditionType t);

#endif