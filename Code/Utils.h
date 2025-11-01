#ifndef __UTILS_H
#define __UTILS_H
#include <iostream>
#include <typeinfo>
#ifdef __GNUG__
#include <cxxabi.h>
#endif
#include <string>
#include <sstream>
#include <vector>
#include "CardsType/ChampionCard.h"
#include "CardsType/ItemCard.h"
#include "CardsType/ActionCard.h"
#include "ResourceType.h"
#include "ConditionType.h"
#include "Effects/ConditionalEffect.h"
#include <memory>

class Effect;
class Ability;
class ItemCard;

class Utils {
    public:
    static void displayAllCards(const std::vector<Card*>& cards, int row, int col);

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
    static void printCentered(const T& content, int totalWidth, const std::string& color="",const std::string& style="") {
        std::string colorCode;
        std::string styleCode = getStyleCode(style);
        if(color=="AttackEffect"){colorCode = getColorCode("red");}
        else if(color=="HealEffect"){colorCode = getColorCode("green");}
        else if(color=="DrawEffect"){colorCode = getColorCode("blue");}
        else if(color=="GoldEffect"){colorCode = getColorCode("yellow");}
        else if(color=="SacrificeEffect"){colorCode = getColorCode("grey");}

        std::ostringstream oss;
        oss << content;
        std::string str = oss.str();
        
        int padding = totalWidth - str.length();
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string resetCode = "\033[0m";
        std::cout << "|" << std::string(left, ' ')
        << colorCode << styleCode << str << resetCode
        << std::string(right, ' ') << "|";
    }
    template<typename T>
    static void printCenteredName(const T& content, int totalWidth, int cost) {

        std::ostringstream oss;
        oss << content;
        std::string str = oss.str();
        
        int padding = totalWidth - str.length()-2;
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string resetCode = "\033[0m";
        std::cout << "|" << std::string(left, ' ') << getStyleCode("bold")
        << str << getColorCode("yellow")
        << std::string(right, ' ')<< " " << cost << resetCode << "|";
    }
    static void printEffect(Card* card, int row, int col, int &indice, int n);
    static void printCenteredPrepareChampionEffect(int totalWidth,const std::string& style="") {
        std::string colorCode;
        std::string styleCode = getStyleCode(style);
        colorCode = getColorCode("magenta");
        std::string str = "Prepare Champion";
        int padding = totalWidth - str.length();
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string resetCode = "\033[0m";
        std::cout << "|" << std::string(left, ' ')
        << colorCode << styleCode << str << resetCode
        << std::string(right, ' ') << "|";
    }
    //A faire
    static void printCenteredStunChampion(int totalWidth,const std::string& style="") {
        std::string colorCode;
        std::string styleCode = getStyleCode(style);
        colorCode = getColorCode("magenta");
        std::string str = "Stun Champion";
        int padding = totalWidth - str.length();
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string resetCode = "\033[0m";
        std::cout << "|" << std::string(left, ' ')
        << colorCode << styleCode << str << resetCode
        << std::string(right, ' ') << "|";
    }
    static void printCenteredDrawThenDiscard(int totalWidth, int row, int col, int &indice,const std::string& style="") {
        std::string colorCode = getColorCode("blue");
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        std::string str1 = "draw n cards";
        std::string str2 = "discard n cards";

        if(totalWidth<15) totalWidth = 15;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - str2.length();
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;
        
        std::cout << "|" << std::string(left1, ' ')
        << colorCode << styleCode << str1 << resetCode
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;

        std::cout << "|" << std::string(left2, ' ')
        << colorCode << styleCode << str2 << resetCode
        << std::string(right2, ' ') << "|";
    }
    static void printCenteredConditionalEffect(int totalWidth, int row, int col, int &indice,int value,ResourceType resourceType, ConditionType conditionType) {
        std::string colorCode;
        std::string resetCode = "\033[0m";
        std::string str1,str2;
        std::string colorCode1 = getColorCode("magenta");
        if(ResourceTypeToString(resourceType)=="Health"){colorCode = getColorCode("green");}
        else if(ResourceTypeToString(resourceType)=="Gold"){colorCode = getColorCode("yellow");}
        else if(ResourceTypeToString(resourceType)=="Combat"){colorCode = getColorCode("red");}
        if(conditionTypeToString(conditionType)=="ChampionCount"){str1 = " for YOUR";str2 = "champion count";}
        else if(conditionTypeToString(conditionType)=="FactionCardCount"){str1 = " for YOUR";str2 ="faction card count";}
        else if(conditionTypeToString(conditionType)=="GuardCount"){str1 = " for YOUR";str2 ="guard count";}
        else if(conditionTypeToString(conditionType)=="OherChampionCount"){str1 = " for OTHER";str2 ="champion count";}
        else if(conditionTypeToString(conditionType)=="OtherGuardCount"){str1 = " for OTHER";str2 ="guard count";}

        
        // Ensure totalWidth is at least as wide as the content
        if(totalWidth<18) totalWidth = 18;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - str2.length();
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;
        
        std::cout << "|" << std::string(left1-1, ' ')
        << colorCode << value << resetCode << colorCode1 <<  str1 << resetCode  
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;

        std::cout << "|" << std::string(left2, ' ')
        <<  colorCode1 <<  str2 << resetCode   << std::string(right2, ' ') << "|";
        // moveCursor(row+indice,col);indice++;
    }
    static void printCenteredPutFromDiscardOnTopEffect(int totalWidth, int row, int col, int &indice, const bool isOptional,const std::string& style="") {
        std::string str1 = "";
        std::string option ="";
        if(isOptional) str1 ="(optional)";
        std::string colorCode = getColorCode("blue");
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        std::string str2 = "Put on the top";
        std::string str3 = "from the discard pile";

        if(totalWidth<20) totalWidth = 20;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - str2.length();
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;

        int padding3 = totalWidth - str3.length();
        if (padding3 < 0) padding3 = 0;
        
        int left3 = padding3 / 2;
        int right3 = padding3 - left3;
        
        std::cout << "|" << std::string(left1, ' ')
        << colorCode << styleCode << str1 << resetCode
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;
        
        std::cout << "|" << std::string(left2, ' ')
        << colorCode << styleCode << str2 << resetCode
        << std::string(right2, ' ') << "|";
        moveCursor(row+indice,col);indice++;

        std::cout << "|" << std::string(left3, ' ')
        << colorCode << styleCode << str3 << resetCode
        << std::string(right3, ' ') << "|";
    }
    
    static void printCenteredOptionalSacrificeEffect(int totalWidth, int row, int col, int &indice,int count, int maxCount) {
        std::string colorCode = getColorCode("grey");
        std::string resetCode = "\033[0m";
        std::string str1 = "Optional Sacrifice";
        std::string str2 = "";
        std::ostringstream oss;
        if(totalWidth<20) totalWidth = 20;
        if(maxCount>1){
            oss << count << " up to " << maxCount;
            std::string str2 = oss.str();
            int padding1 = totalWidth - str1.length();
            if (padding1 < 0) padding1 = 0;
            
            int left1 = padding1 / 2;
            int right1 = padding1 - left1;
    
            int padding2 = totalWidth - str2.length();
            if (padding2 < 0) padding2 = 0;
            
            int left2 = padding2 / 2;
            int right2 = padding2 - left2;
            
            std::cout << "|" << std::string(left1, ' ')
            << colorCode << str1 << resetCode
            << std::string(right1, ' ') << "|";
            moveCursor(row+indice,col);indice++;
            
            std::cout << "|" << std::string(left2, ' ')
            << colorCode << str2 << resetCode
            << std::string(right2, ' ') << "|";
        }
        else{
            oss << count;
            str2 = oss.str();
            int padding1 = totalWidth - str1.length();
            if (padding1 < 0) padding1 = 0;
            
            int left1 = padding1 / 2;
            int right1 = padding1 - left1;

            int padding2 = totalWidth - str2.length();
            if (padding2 < 0) padding2 = 0;
            
            int left2 = padding2 / 2;
            int right2 = padding2 - left2;
            
            std::cout << "|" << std::string(left1, ' ')
            << colorCode << str1 << resetCode
            << std::string(right1, ' ') << "|";
            moveCursor(row+indice,col);indice++;
            
            std::cout << "|" << std::string(left2, ' ')
            << colorCode << str2 << resetCode
            << std::string(right2, ' ') << "|";
        }
    }
    
    static void printCenteredPutNextCardInHandEffect(int totalWidth, int row, int col, int &indice,const std::string& style="") {
        std::string option ="";
        std::string colorCode = getColorCode("blue");
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        std::string str1 = "Put next card";
        std::string str2 = "in hand";

        if(totalWidth<20) totalWidth = 20;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - str2.length();
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;
        
        std::cout << "|" << std::string(left1, ' ')
        << colorCode << styleCode << str1 << resetCode
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;
        
        std::cout << "|" << std::string(left2, ' ')
        << colorCode << styleCode << str2 << resetCode
        << std::string(right2, ' ') << "|";
        // moveCursor(row+indice,col);indice++;
    }
    static void printCenteredPutNextCardOnTopEffect(std::string cardTypeFilter,int totalWidth, int row, int col, int &indice,const std::string& style="") {
        std::string option ="";
        std::string colorCode = getColorCode("blue");
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        std::string str1 = "Put next card";
        std::string str2 = "on the top";

        if(totalWidth<20) totalWidth = 20;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - cardTypeFilter.length()-2;
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;

        int padding3 = totalWidth - str2.length();
        if (padding3 < 0) padding3 = 0;
        
        int left3 = padding3 / 2;
        int right3 = padding3 - left3;
        
        
        std::cout << "|" << std::string(left1, ' ')
        << colorCode << styleCode << str1 << resetCode
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;
        
        std::cout << "|" << std::string(left2, ' ')
        <<colorCode << "(" << cardTypeFilter <<")" << resetCode
        << std::string(right2, ' ') << "|";
        moveCursor(row+indice,col);indice++;

        std::cout << "|" << std::string(left3, ' ')
        <<colorCode <<  str2 << resetCode
        << std::string(right3, ' ') << "|";
    }
    static void printCenteredDiscardOpponent(int totalWidth, int row, int col, int &indice,const std::string& style="") {
        std::string colorCode = getColorCode("blue");
        std::string styleCode = getStyleCode(style);
        std::string resetCode = "\033[0m";
        std::string str1 = "discard 1 card";
        std::string str2 = "opponent";

        if(totalWidth<14) totalWidth = 14;
        int padding1 = totalWidth - str1.length();
        if (padding1 < 0) padding1 = 0;
        
        int left1 = padding1 / 2;
        int right1 = padding1 - left1;

        int padding2 = totalWidth - str2.length();
        if (padding2 < 0) padding2 = 0;
        
        int left2 = padding2 / 2;
        int right2 = padding2 - left2;
        
        std::cout << "|" << std::string(left1, ' ')
        << colorCode << styleCode << str1 << resetCode
        << std::string(right1, ' ') << "|";
        moveCursor(row+indice,col);indice++;

        std::cout << "|" << std::string(left2, ' ')
        << colorCode << styleCode << str2 << resetCode
        << std::string(right2, ' ') << "|";
    }
    template<typename T>
    static void printCentered2(const T& content, const T& content1, int totalWidth,std::string name, const std::string color="",const std::string& style="",const std::string color1="",const std::string& style1="") {
        std::string colorCode,colorCode1;
        std::string styleCode = getStyleCode(style);
        std::string styleCode1 = getStyleCode(style1);
        if(color=="AttackEffect"){colorCode = getColorCode("red");}
        else if(color=="HealEffect"){colorCode = getColorCode("green");}
        else if(color=="DrawEffect"){colorCode = getColorCode("blue");}
        else if(color=="SacrificeEffect"){colorCode = getColorCode("grey");}
        else if(color=="GoldEffect"){colorCode = getColorCode("yellow");}

        if(color1=="AttackEffect"){colorCode1 = getColorCode("red");}
        if(color1=="GoldEffect"){colorCode1 = getColorCode("yellow");}
        else if(color1=="HealEffect"){colorCode1 = getColorCode("green");}
        else if(color1=="DrawEffect"){colorCode1 = getColorCode("blue");}
        else if(color1=="SacrificeEffect"){colorCode1 = getColorCode("grey");}
        std::ostringstream oss;
        oss << content;
        std::string str = oss.str();
        std::ostringstream oss1;
        oss1 << content1;
        std::string str1 = oss1.str();
        
        int padding = totalWidth - str.length();
        if (padding < 0) padding = 0;
        
        int left = padding / 2;
        int right = padding - left;
        
        std::string resetCode = "\033[0m";
        std::cout << "|" << std::string(left-2, ' ')
        << colorCode << styleCode << str << resetCode << name << colorCode1 << styleCode1 << str1 << resetCode
        << std::string(right-3, ' ') << "|";
    }
    template<typename T>
    static std::string EntireName(const T& content,int cost){
        std::ostringstream oss;
        oss << "| " << content << " " << cost << " |";
        std::string str = oss.str();
        return str;
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
    static void addCard(const T& card, std::vector<Card*> cards) {
        cards.push_back(card);
    }
    
    template<typename T>
    static int countChar(const T& value) {
        std::ostringstream oss;
        oss << value;
        std::string str = oss.str();
        return str.length();
    }
    template<typename T>
    static void printCards(const T& cards){
        std::cout << demangle_type(cards.at(0))<< std::endl;
    }

        
    static void clearScreen() {
        std::cout << "\033[2J";
    }

    // Positionner le curseur
    static void moveCursor(int row, int col) {
        std::cout << "\033[" << row << ";" << col << "H";
    }

    // Effacer la ligne actuelle
    static void clearLine() {
        std::cout << "\033[2K";
    }

    // Couleurs du texte
    static void setColor(int color) {
        std::cout << "\033[" << color << "m";
    }

    // Réinitialiser les couleurs
    static void resetColor() {
        std::cout << "\033[0m";
    }
    template<typename T>
    static std::string demangle_type(const T& obj) {
        const char* mangled_name = typeid(obj).name();
        
#ifdef __GNUG__
        // GCC/Clang: utilisation de __cxa_demangle pour obtenir le nom lisible
        int status = 0;
        std::unique_ptr<char, void(*)(void*)> demangled(
            abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status),
            std::free
        );
        return (status == 0) ? demangled.get() : mangled_name;
#else
        // MSVC: typeid().name() retourne déjà un nom lisible
        return mangled_name;
#endif
    }

    static void printChoiceEffect(int n);
    static void printVide(int n, bool plusieurs=false);
    static void printBarre(int n,int verif);
    void printVidePlusieurs(int espacement);
};


#endif