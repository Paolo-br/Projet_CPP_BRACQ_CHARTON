#include "ConditionType.h"

std::string conditionTypeToString(ConditionType t){
    switch(t){
        case ConditionType::ChampionCount: return "ChampionCount";
        case ConditionType::FactionCardCount: return "FactionCardCount";
        case ConditionType::GuardCount: return "GuardCount";
        case ConditionType::OtherChampionCount: return "OherChampionCount";
        case ConditionType::OtherGuardCount: return "OtherGuardCount";
        default: return "None";
    }
}