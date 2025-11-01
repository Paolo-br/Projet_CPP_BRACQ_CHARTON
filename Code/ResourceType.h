#ifndef __RESOURCETYPE_H
#define __RESOURCETYPE_H

#include <string>

enum class ResourceType {
    Gold,       
    Combat,     
    Health      
};


std::string ResourceTypeToString(ResourceType r);

#endif