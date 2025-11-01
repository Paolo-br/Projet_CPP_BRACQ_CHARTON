#include <iostream>
#include <sstream>
#include "Utils.h"
#include "CardsType/ItemCard.h"

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
void Utils::printBarre(int n, int verif){
    if(verif==0){
        std::string tiret = std::string(n, '_');
        std::cout<< tiret;
    }
    else if(verif==1){
        std::string tiret = '|' +std::string(n, '_')+'|';
        std::cout<< tiret;
    }
}

void Utils::displayAllCards(const std::vector<Card*>& cards, int row, int col) {
    int compare=0, temp;
    std::tuple<int,int> result;
    int initialCol = col;
    int currentCol = col;
    int cardIndex = 0;
    
    for (Card* card : cards) {
        // Si ce n'est pas la première carte et qu'on dépasse la limite
        if(cardIndex > 0 && currentCol > 125){
            row = row + compare + 3;
            currentCol = initialCol;
            compare = 0;
        }
        
        result = card->display(row, currentCol);
        temp = std::get<0>(result);
        int cardWidth = std::get<1>(result);
        
        if(temp > compare) compare = temp;
        
        // Calculer la position pour la prochaine carte
        currentCol = currentCol + cardWidth + 3;
        cardIndex++;
    }
    Utils::moveCursor(row + compare + 3, 0);
}

void Utils::printEffect(Card* card, int row, int col, int &indice, int n){
    std::vector<Ability*> liste_abi=card->getAbilities();
    bool isItemCard=false;
    if(liste_abi.empty()){
        isItemCard=true;
    }
    if(isItemCard==false){
        for (Ability* e : liste_abi) {  
        std::vector<Effect*> temp = e->getEffect();
        if(e->getName()=="PrimaryAbility"){
            printCentered("PrimaryAbility",n);
            moveCursor(row+indice,col);
            indice++;
            for (Effect* e1 : temp) {
                if(e1->getName()=="ChoiceEffect"){
                    printCentered2(e1->getOption1()->getValue(),e1->getOption2()->getValue(),n," or ",e1->getOption1()->getName(),"",e1->getOption2()->getName(),"");
                    //Faire la fonction qui affiche avec les bonnes couleurs
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else if(e1->getName()=="DrawThenDiscardEffect"){
                    printCenteredDrawThenDiscard(n,row,col,indice,"");
                }
                else if(e1->getName()=="DiscardOpponentEffect"){
                    printCenteredDiscardOpponent(n,row,col,indice,"");
                }
                else if(e1->getName()=="PrepareChampionEffect"){
                    printCenteredPrepareChampionEffect(n,"");
                }
                else if(e1->getName()=="StunChampionEffect"){
                    printCenteredStunChampion(n,"");
                }
                else if(e1->getName()=="PutFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutChampionFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutNextCardInHandEffect"){
                    printCenteredPutNextCardInHandEffect(n,row,col,indice,"");
                }
                else if(e1->getName()=="OptionalSacrificeEffect"){
                    printCenteredOptionalSacrificeEffect(n,row, col,indice,e1->getCount(),e1->getMaxCount());
                }
                else if(e1->getName()=="PutNextCardOnTopEffect"){
                    const std::string* cardTypeFilter = e1->getCardTypeFilter();
                    if(cardTypeFilter != nullptr){
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter,n,row,col,indice,"");
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else{
                    printCentered(e1->getValue(),n,e1->getName(),"");
                }
                moveCursor(row+indice,col);
                indice++;
            }
        }
        else if(e->getName()=="AllyAbility"){
            printCentered("AllyAbility",n);
            moveCursor(row+indice,col);
            indice++;
            for (Effect* e1 : temp) {
                if(e1->getName()=="ChoiceEffect"){
                    printCentered2(e1->getOption1()->getValue(),e1->getOption2()->getValue(),n," or ",e1->getOption1()->getName(),"",e1->getOption2()->getName(),"");
                    //Faire la fonction qui affiche avec les bonnes couleurs
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else if(e1->getName()=="DrawThenDiscardEffect"){
                    printCenteredDrawThenDiscard(n,row,col,indice,"");
                }
                else if(e1->getName()=="DiscardOpponentEffect"){
                    printCenteredDiscardOpponent(n,row,col,indice,"");
                }
                else if(e1->getName()=="PrepareChampionEffect"){
                    printCenteredPrepareChampionEffect(n,"");
                }
                else if(e1->getName()=="StunChampionEffect"){
                    printCenteredStunChampion(n,"");
                }
                else if(e1->getName()=="PutFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutChampionFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutNextCardInHandEffect"){
                    printCenteredPutNextCardInHandEffect(n,row,col,indice,"");
                }
                else if(e1->getName()=="OptionalSacrificeEffect"){
                    printCenteredOptionalSacrificeEffect(n,row, col,indice,e1->getCount(),e1->getMaxCount());
                }
                else if(e1->getName()=="PutNextCardOnTopEffect"){
                    const std::string* cardTypeFilter = e1->getCardTypeFilter();
                    if(cardTypeFilter != nullptr){
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter,n,row,col,indice,"");
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else{
                    printCentered(e1->getValue(),n,e1->getName(),"");
                }
                moveCursor(row+indice,col);
                indice++;
            }
        }
        else if(e->getName()=="SacrificeAbility"){
            printCentered("SacrificeAbility",n);
            moveCursor(row+indice,col);
            indice++;
            for (Effect* e1 : temp) {
                if(e1->getName()=="ChoiceEffect"){
                    printCentered2(e1->getOption1()->getValue(),e1->getOption2()->getValue(),n," or ",e1->getOption1()->getName(),"",e1->getOption2()->getName(),"");
                    //Faire la fonction qui affiche avec les bonnes couleurs
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else if(e1->getName()=="DrawThenDiscardEffect"){
                    printCenteredDrawThenDiscard(n,row,col,indice,"");
                }
                else if(e1->getName()=="DiscardOpponentEffect"){
                    printCenteredDiscardOpponent(n,row,col,indice,"");
                }
                else if(e1->getName()=="PrepareChampionEffect"){
                    printCenteredPrepareChampionEffect(n,"");
                }
                else if(e1->getName()=="StunChampionEffect"){
                    printCenteredStunChampion(n,"");
                }
                else if(e1->getName()=="PutFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutChampionFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutNextCardInHandEffect"){
                    printCenteredPutNextCardInHandEffect(n,row,col,indice,"");
                }
                else if(e1->getName()=="OptionalSacrificeEffect"){
                    printCenteredOptionalSacrificeEffect(n,row, col,indice,e1->getCount(),e1->getMaxCount());
                }
                else if(e1->getName()=="PutNextCardOnTopEffect"){
                    const std::string* cardTypeFilter = e1->getCardTypeFilter();
                    if(cardTypeFilter != nullptr){
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter,n,row,col,indice,"");
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else{
                    printCentered(e1->getValue(),n,e1->getName(),"");
                }
                moveCursor(row+indice,col);
                indice++;
            }
        }
        else if(e->getName()=="ActivateAbility"){
            printCentered("ActivateAbility",n);
            moveCursor(row+indice,col);
            indice++;
            for (Effect* e1 : temp) {
                if(e1->getName()=="ChoiceEffect"){
                    printCentered2(e1->getOption1()->getValue(),e1->getOption2()->getValue(),n," or ",e1->getOption1()->getName(),"",e1->getOption2()->getName(),"");
                    //Faire la fonction qui affiche avec les bonnes couleurs
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else if(e1->getName()=="DrawThenDiscardEffect"){
                    printCenteredDrawThenDiscard(n,row,col,indice,"");
                }
                else if(e1->getName()=="DiscardOpponentEffect"){
                    printCenteredDiscardOpponent(n,row,col,indice,"");
                }
                else if(e1->getName()=="PrepareChampionEffect"){
                    printCenteredPrepareChampionEffect(n,"");
                }
                else if(e1->getName()=="StunChampionEffect"){
                    printCenteredStunChampion(n,"");
                }
                else if(e1->getName()=="PutFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutChampionFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutNextCardInHandEffect"){
                    printCenteredPutNextCardInHandEffect(n,row,col,indice,"");
                }
                else if(e1->getName()=="OptionalSacrificeEffect"){
                    printCenteredOptionalSacrificeEffect(n,row, col,indice,e1->getCount(),e1->getMaxCount());
                }
                else if(e1->getName()=="PutNextCardOnTopEffect"){
                    const std::string* cardTypeFilter = e1->getCardTypeFilter();
                    if(cardTypeFilter != nullptr){
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter,n,row,col,indice,"");
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else{
                    printCentered(e1->getValue(),n,e1->getName(),"");
                }
                moveCursor(row+indice,col);
                indice++;
            }
        }
    }
    }
    else {
        std::vector<Effect*> liste_effet = card->getEffect();
            for (Effect* e1 : liste_effet) {
                if(e1->getName()=="ChoiceEffect"){
                    printCentered2(e1->getOption1()->getValue(),e1->getOption2()->getValue(),n," or ",e1->getOption1()->getName(),"",e1->getOption2()->getName(),"");
                    //Faire la fonction qui affiche avec les bonnes couleurs
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else if(e1->getName()=="DrawThenDiscardEffect"){
                    printCenteredDrawThenDiscard(n,row,col,indice,"");
                }
                else if(e1->getName()=="DiscardOpponentEffect"){
                    printCenteredDiscardOpponent(n,row,col,indice,"");
                }
                else if(e1->getName()=="PrepareChampionEffect"){
                    printCenteredPrepareChampionEffect(n,"");
                }
                else if(e1->getName()=="StunChampionEffect"){
                    printCenteredStunChampion(n,"");
                }
                else if(e1->getName()=="PutFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutChampionFromDiscardOnTopEffect"){
                    printCenteredPutFromDiscardOnTopEffect(n,row,col,indice,e1->getIsOptional(),"");
                }
                else if(e1->getName()=="PutNextCardInHandEffect"){
                    printCenteredPutNextCardInHandEffect(n,row,col,indice,"");
                }
                else if(e1->getName()=="OptionalSacrificeEffect"){
                    printCenteredOptionalSacrificeEffect(n,row, col,indice,e1->getCount(),e1->getMaxCount());
                }
                else if(e1->getName()=="PutNextCardOnTopEffect"){
                    const std::string* cardTypeFilter = e1->getCardTypeFilter();
                    if(cardTypeFilter != nullptr){
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter,n,row,col,indice,"");
                    } else {
                        printCentered(e1->getValue(),n,e1->getName(),"");
                    }
                }
                else{
                    printCentered(e1->getValue(),n,e1->getName(),"");
                }
                moveCursor(row+indice,col);
                indice++;
            }
    }
}
