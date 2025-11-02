#include <iostream>
#include <sstream>
#include "Utils.h"
#include "CardsType/ItemCard.h"

std::string Utils::getColorCode(const std::string& color) {
    if (color == "red") return "\033[31m";
    if (color == "green") return "\033[32m";
    if (color == "yellow") return "\033[33m";
    void Utils::printEffect(Card* card, int row, int col, int &indice, int n){
        // Print abilities (or direct card effects for items) with clear separators
        const std::vector<Ability*>& abilities = card->getAbilities();
        if (!abilities.empty()) {
            for (Ability* ability : abilities) {
                // Header for the ability
                Utils::printCentered(ability->getName(), n);
                Utils::moveCursor(row + indice, col);
                indice++;

                const std::vector<Effect*>& effects = ability->getEffect();
                for (Effect* eff : effects) {
                    if (!eff) continue;

                    const std::string& en = eff->getName();
                    if (en == "ChoiceEffect") {
                        printCentered2(eff->getOption1()->getValue(), eff->getOption2()->getValue(), n, " or ", eff->getOption1()->getName(), "", eff->getOption2()->getName(), "");
                    } else if (en == "ConditionalEffect") {
                        const ResourceType* r = eff->getResourceType();
                        const ConditionType* c = eff->getConditionType();
                        if (r != nullptr && c != nullptr) {
                            printCenteredConditionalEffect(n, row, col, indice, eff->getValue(), *r, *c);
                        } else {
                            printValueOrDesc(eff, n);
                        }
                    } else if (en == "DrawThenDiscardEffect") {
                        printCenteredDrawThenDiscard(n, row, col, indice, "");
                    } else if (en == "DiscardOpponentEffect") {
                        printCenteredDiscardOpponent(n, row, col, indice, "");
                    } else if (en == "PrepareChampionEffect") {
                        printCenteredPrepareChampionEffect(n, "");
                    } else if (en == "StunChampionEffect") {
                        printCenteredStunChampion(n, "");
                    } else if (en == "PutFromDiscardOnTopEffect" || en == "PutChampionFromDiscardOnTopEffect") {
                        printCenteredPutFromDiscardOnTopEffect(n, row, col, indice, eff->getIsOptional(), "");
                    } else if (en == "PutNextCardInHandEffect") {
                        printCenteredPutNextCardInHandEffect(n, row, col, indice, "");
                    } else if (en == "OptionalSacrificeEffect") {
                        printCenteredOptionalSacrificeEffect(n, row, col, indice, eff->getCount(), eff->getMaxCount());
                    } else if (en == "PutNextCardOnTopEffect") {
                        const std::string* cardTypeFilter = eff->getCardTypeFilter();
                        if (cardTypeFilter != nullptr) {
                            printCenteredPutNextCardOnTopEffect(*cardTypeFilter, n, row, col, indice, "");
                        } else {
                            printValueOrDesc(eff, n);
                        }
                    } else {
                        printValueOrDesc(eff, n);
                    }

                    Utils::moveCursor(row + indice, col);
                    indice++;
                }

                // Separator after each ability
                Utils::moveCursor(row + indice, col);
                Utils::printBarre(n, 0);
                Utils::moveCursor(row + indice + 1, col);
                indice++;
            }
        } else {
            // Item cards: print effects directly (no ability headers)
            const std::vector<Effect*>& effects = card->getEffect();
            for (Effect* eff : effects) {
                if (!eff) continue;
                const std::string& en = eff->getName();
                if (en == "ChoiceEffect") {
                    printCentered2(eff->getOption1()->getValue(), eff->getOption2()->getValue(), n, " or ", eff->getOption1()->getName(), "", eff->getOption2()->getName(), "");
                } else if (en == "ConditionalEffect") {
                    const ResourceType* r = eff->getResourceType();
                    const ConditionType* c = eff->getConditionType();
                    if (r != nullptr && c != nullptr) {
                        printCenteredConditionalEffect(n, row, col, indice, eff->getValue(), *r, *c);
                    } else {
                        printValueOrDesc(eff, n);
                    }
                } else if (en == "DrawThenDiscardEffect") {
                    printCenteredDrawThenDiscard(n, row, col, indice, "");
                } else if (en == "DiscardOpponentEffect") {
                    printCenteredDiscardOpponent(n, row, col, indice, "");
                } else if (en == "PrepareChampionEffect") {
                    printCenteredPrepareChampionEffect(n, "");
                } else if (en == "StunChampionEffect") {
                    printCenteredStunChampion(n, "");
                } else if (en == "PutFromDiscardOnTopEffect" || en == "PutChampionFromDiscardOnTopEffect") {
                    printCenteredPutFromDiscardOnTopEffect(n, row, col, indice, eff->getIsOptional(), "");
                } else if (en == "PutNextCardInHandEffect") {
                    printCenteredPutNextCardInHandEffect(n, row, col, indice, "");
                } else if (en == "OptionalSacrificeEffect") {
                    printCenteredOptionalSacrificeEffect(n, row, col, indice, eff->getCount(), eff->getMaxCount());
                } else if (en == "PutNextCardOnTopEffect") {
                    const std::string* cardTypeFilter = eff->getCardTypeFilter();
                    if (cardTypeFilter != nullptr) {
                        printCenteredPutNextCardOnTopEffect(*cardTypeFilter, n, row, col, indice, "");
                    } else {
                        printValueOrDesc(eff, n);
                    }
                } else {
                    printValueOrDesc(eff, n);
                }

                Utils::moveCursor(row + indice, col);
                indice++;
            }
        }
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
