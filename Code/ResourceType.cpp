#include "ResourceType.h"

std::string ResourceTypeToString(ResourceType r){
        switch (r) {
        case ResourceType::Gold:    return "Gold";
        case ResourceType::Combat:    return "Combat";
        case ResourceType::Health:  return "Health";
        default:                 return "Inconnu";
    }
}