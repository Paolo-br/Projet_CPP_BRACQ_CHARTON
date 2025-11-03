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

void Utils::printColorLegend(int row, int col) {
    // Small, non-intrusive legend printed at the requested position
    std::string reset = "\033[0m";
    Utils::moveCursor(row, col);
    std::cout << "Légende: ";
    std::cout << Utils::getColorCode("red") << "Combat" << reset << "  ";
    std::cout << Utils::getColorCode("green") << "Heal" << reset << "  ";
    std::cout << Utils::getColorCode("blue") << "Draw" << reset << "  ";
    std::cout << Utils::getColorCode("yellow") << "Gold" << reset << "  ";
    std::cout << Utils::getColorCode("grey") << "Sacrifice" << reset << "  ";
    std::cout << Utils::getColorCode("magenta") << "Prepare" << reset;
    std::cout << std::endl;
}

std::string Utils::describeEffect(Effect* e) {
    if (auto ce = dynamic_cast<ConditionalEffect*>(e)) {
        int val = ce->getValue();
        ResourceType rt = *(ce->getResourceType());
        ConditionType ct = *(ce->getConditionType());
        std::string resStr = ResourceTypeToString(rt);
        std::string condStr;
        switch (ct) {
            case ConditionType::ChampionCount: condStr = "par champion"; break;
            case ConditionType::FactionCardCount: condStr = "par carte de faction"; break;
            case ConditionType::GuardCount: condStr = "par garde"; break;
            case ConditionType::OtherChampionCount: condStr = "par champion adverse"; break;
            case ConditionType::OtherGuardCount: condStr = "par garde adverse"; break;
            default: condStr = "selon condition"; break;
        }

        
        std::string colorCode;
        if (ResourceTypeToString(rt) == "Health") colorCode = Utils::getColorCode("green");
        else if (ResourceTypeToString(rt) == "Gold") colorCode = Utils::getColorCode("yellow");
        else if (ResourceTypeToString(rt) == "Combat") colorCode = Utils::getColorCode("red");
        else colorCode = "";
        std::string reset = "\033[0m";

    
        return colorCode + std::string("+") + std::to_string(val) + reset + " " + condStr;
    }

    std::string name = e->getName();
    // Use French descriptions where appropriate
    if (name == "DiscardOpponentEffect") {
        return std::string("Faire défausser 1 carte à l'adversaire");
    }
    if (name == "PutFromDiscardOnTopEffect") {
        return e->getIsOptional() ? "(Optionnel) Placer une carte de la défausse sur le dessus" : "Placer une carte de la défausse sur le dessus";
    }
    if (name == "PutChampionFromDiscardOnTopEffect") {
        return e->getIsOptional() ? "(Optionnel) Remettre un Champion de la défausse sur le dessus" : "Remettre un Champion de la défausse sur le dessus";
    }
    if (name == "PutNextCardInHandEffect") {
        return std::string("Mettre la prochaine carte en main");
    }
    if (name == "PutNextCardOnTopEffect") {
        const std::string* filter = e->getCardTypeFilter();
        if (filter) return std::string("Mettre la prochaine carte (") + *filter + ") sur le dessus";
        return std::string("Mettre la prochaine carte sur le dessus");
    }
    if (name == "OptionalSacrificeEffect") {
        int count = e->getCount();
        int maxc = e->getMaxCount();
        if (maxc > 1) return std::string("Sacrifice optionnel: ") + std::to_string(count) + " jusqu'à " + std::to_string(maxc);
        return std::string("Sacrifice optionnel: ") + std::to_string(count);
    }
    if (name == "PrepareChampionEffect") return std::string("Préparer un Champion");
    if (name == "StunChampionEffect") return std::string("Assommer un Champion");
    if (name == "SacrificeEffect") return std::string("Sacrifier cette carte");
    if (name == "ChoiceEffect") {
        // For ChoiceEffect we prefer to show the two option descriptions (handled elsewhere), but return a placeholder
        return std::string("Choix (voir options)");
    }
    // Fallback: return the effect name
    return name;
}

// Helper: print either the numeric colored value for core effects
// or a descriptive phrase for other effects.
static void printValueOrDesc(Effect* e, int n) {
    if (!e) return;
    std::string en = e->getName();
    if (en == "AttackEffect" || en == "HealEffect" || en == "DrawEffect" || en == "GoldEffect" || en == "SacrificeEffect" || en == "PrepareChampionEffect") {
        Utils::printCentered(e->getValue(), n, en, "");
    } else {
        std::string desc = Utils::describeEffect(e);
        Utils::printCentered(desc, n, "", "");
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

void Utils::displayAllCardsWithIndices(const std::vector<Card*>& cards, int row, int col) {
    if (cards.empty()) return;

    int initialCol = col;
    int currentCol = initialCol;
    std::vector<std::tuple<int,int,int>> layout; // startCol, bottomRow, width
    int maxBottom = 0;

    for (Card* card : cards) {
        if (!card) continue;
        auto result = card->display(row, currentCol);
        int bottom = std::get<0>(result);
        int width = std::get<1>(result);
        layout.emplace_back(currentCol, bottom, width);
        if (bottom > maxBottom) maxBottom = bottom;
        currentCol += width + 3;
    }

    // Print centered indices under each card
    int indexRow = maxBottom + 1;
    for (size_t i = 0; i < layout.size(); ++i) {
        int startCol = std::get<0>(layout[i]);
        int width = std::get<2>(layout[i]);
        int centerCol = startCol + width / 2;
        Utils::moveCursor(indexRow, centerCol);
        std::cout << (i + 1);
    }

    Utils::moveCursor(maxBottom + 3, 0);
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
                            std::string en = e1->getName();
                            if (en == "AttackEffect" || en == "HealEffect" || en == "DrawEffect" || en == "GoldEffect" || en == "SacrificeEffect" || en == "PrepareChampionEffect") {
                                printCentered(e1->getValue(), n, en, "");
                            } else {
                                printValueOrDesc(e1, n);
                            }
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
                        std::string en = e1->getName();
                        if (en == "AttackEffect" || en == "HealEffect" || en == "DrawEffect" || en == "GoldEffect" || en == "SacrificeEffect" || en == "PrepareChampionEffect") {
                            printCentered(e1->getValue(), n, en, "");
                        } else {
                            printValueOrDesc(e1, n);
                        }
                    }
                }
                else{
                    printValueOrDesc(e1, n);
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
                  
                }
                else if(e1->getName()=="ConditionalEffect"){
                    const ResourceType* r = e1->getResourceType();
                    const ConditionType* c = e1->getConditionType();
                    if(r != nullptr && c != nullptr){
                        printCenteredConditionalEffect(n,row,col,indice,e1->getValue(), *r, *c);
                    } else {
                        std::string en = e1->getName();
                        if (en == "AttackEffect" || en == "HealEffect" || en == "DrawEffect" || en == "GoldEffect" || en == "SacrificeEffect" || en == "PrepareChampionEffect") {
                            printCentered(e1->getValue(), n, en, "");
                        } else {
                            printValueOrDesc(e1, n);
                        }
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
                        std::string en = e1->getName();
                        if (en == "AttackEffect" || en == "HealEffect" || en == "DrawEffect" || en == "GoldEffect" || en == "SacrificeEffect" || en == "PrepareChampionEffect") {
                            printCentered(e1->getValue(), n, en, "");
                        } else {
                            printValueOrDesc(e1, n);
                        }
                    }
                }
                else{
                    printValueOrDesc(e1, n);
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
                            printValueOrDesc(e1, n);
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
                            printValueOrDesc(e1, n);
                        }
                }
                else{
                    printValueOrDesc(e1, n);
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
                        printValueOrDesc(e1, n);
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
                            printValueOrDesc(e1, n);
                    }
                }
                else{
                    printValueOrDesc(e1, n);
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
                            printValueOrDesc(e1, n);
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
                        printValueOrDesc(e1, n);
                    }
                }
                else{
                        printValueOrDesc(e1, n);
                }
                moveCursor(row+indice,col);
                indice++;
            }
    }
}
