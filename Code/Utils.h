#ifndef __UTILS_H
#define __UTILS_H
#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>

class Effect;
class Ability;

class Utils {
    public:
    static std::string getColorCode(const std::string& color);
    template<typename T>
    static int countSpaces(const T&  str) {
        int count = 0;
        for (char c : str) {
            if (c == ' ') {
                ++count;
            }
        }
        return count;
    }
    static std::string getStyleCode(const std::string& style);
    template<typename T>
    static void printCentered(const T& content, int totalWidth, const std::string& color="",const std::string& style="", bool verif=true) {
        std::ostringstream oss;
        oss << content;
        std::string str = oss.str();
        
        int padding = totalWidth - str.length();
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string colorCode = getColorCode(color);
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        if(verif){
        std::cout << "|" << std::string(left, ' ')
        << colorCode << styleCode << str << resetCode
        << std::string(right, ' ') << "|" << std::endl;
        }
        else{
        std::cout << "|" << std::string(left, ' ')
        << colorCode << styleCode << str << resetCode
        << std::string(right, ' ') << "|";
        }
    }
        template<typename T>
    static void addEffect(std::vector<Effect*>& effects, int value, std::string typeAbility="") {
        if(typeAbility=="")
        effects.push_back(new T(value));
    }

    template<typename T>
    static void addAbility(std::vector<Ability*>& abilities, std::vector<Effect*> effs) {
        abilities.push_back(new T(effs));
    }
    
    template<typename T>
    static int countChar(const T& value) {
        std::ostringstream oss;
        oss << value;
        std::string str = oss.str();
        return str.length();
    }

    static void printVide(int n, bool plusieurs=false);
    static void printBarre(int n, bool plusieurs=false);
    void printVidePlusieurs(int espacement);
};


#endif