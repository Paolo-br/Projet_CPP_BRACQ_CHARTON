#include <iostream>
#include <sstream>
#include "Utils.h"

std::string Utils::getColorCode(const std::string& color) {
    if (color == "red") return "\033[31m";
    if (color == "green") return "\033[32m";
    if (color == "yellow") return "\033[33m";
    if (color == "blue") return "\033[34m";
    if (color == "magenta") return "\033[35m";
    if (color == "cyan") return "\033[36m";
    if (color == "white") return "\033[37m";
    if (color == "grey") return "\033[90m";
    return ""; // couleur par défaut (pas de couleur)
}

std::string Utils::getStyleCode(const std::string& style) {
    if (style == "bold") return "\033[1m";
    if (style == "italic") return "\033[3m";
    if (style == "underline") return "\033[4m";
    return "";
}

void Utils::printVide(int n, bool plusieurs){
    if(plusieurs){
        std::string espaces = std::string(n, ' ');
        std::cout << "|" << espaces << "|";
    }
    else{
        std::string espaces = std::string(n, ' ');
        std::cout << "|" << espaces << "|" << std::endl;
    }
}

void Utils::printVidePlusieurs(int espacement){
    std::string espaces = std::string(espacement, ' ');
    std::cout << espaces;
}
void Utils::printBarre(int n, bool plusieurs){
    if(plusieurs){
        std::string tiret = std::string(n, '_');
        std::cout<< tiret;
    }
    else{
        std::string tiret = std::string(n, '_');
        std::cout<< tiret<< std::endl;
    }
}
    
