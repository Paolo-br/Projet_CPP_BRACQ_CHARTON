CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

# Définir les répertoires source
CARDS_DIR=Cards
CARDS_TYPE_DIR=CardsType
EFFECTS_DIR=Effects
ABILITIES_DIR=Abilities

# Liste des fichiers objets avec chemins
CARDS_OBJ=$(CARDS_DIR)/Deck.o $(CARDS_DIR)/Hand.o $(CARDS_DIR)/DiscardPile.o $(CARDS_DIR)/Market.o
CARDS_TYPE_OBJ=$(CARDS_TYPE_DIR)/Card.o $(CARDS_TYPE_DIR)/ActionCard.o $(CARDS_TYPE_DIR)/ItemCard.o $(CARDS_TYPE_DIR)/ChampionCard.o
EFFECTS_OBJ=$(EFFECTS_DIR)/Effect.o $(EFFECTS_DIR)/GoldEffect.o $(EFFECTS_DIR)/AttackEffect.o $(EFFECTS_DIR)/HealEffect.o $(EFFECTS_DIR)/DrawEffect.o \
			$(EFFECTS_DIR)/SacrificeEffect.o $(EFFECTS_DIR)/PrepareChampionEffect.o $(EFFECTS_DIR)/StunChampionEffect.o $(EFFECTS_DIR)/DiscardOpponentEffect.o \
			$(EFFECTS_DIR)/ConditionalEffect.o $(EFFECTS_DIR)/ChoiceEffect.o $(EFFECTS_DIR)/DrawThenDiscardEffect.o $(EFFECTS_DIR)/PutNextCardOnTopEffect.o \
			$(EFFECTS_DIR)/PutNextCardInHandEffect.o $(EFFECTS_DIR)/PutFromDiscardOnTopEffect.o $(EFFECTS_DIR)/PutChampionFromDiscardOnTopEffect.o $(EFFECTS_DIR)/OptionalSacrificeEffect.o
ABILITIES_OBJ=$(ABILITIES_DIR)/Ability.o $(ABILITIES_DIR)/SacrificeAbility.o $(ABILITIES_DIR)/AllyAbility.o $(ABILITIES_DIR)/ActivateAbility.o $(ABILITIES_DIR)/PrimaryAbility.o
ROOT_OBJ=Player.o InPlayArea.o Faction.o Game.o Turn.o ResourceType.o ConditionType.o Utils.o SaveManager.o GodMode.o CardFactory.o

ALL_OBJ=$(CARDS_OBJ) $(CARDS_TYPE_OBJ) $(EFFECTS_OBJ) $(ABILITIES_OBJ) $(ROOT_OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@


main: main.o $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

display_all_cards_gui: display_all_cards_gui.o $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: run clean

run: main
	./main

clean:
	rm -f *.o *~ *.core main
	rm -f $(CARDS_DIR)/*.o $(CARDS_TYPE_DIR)/*.o $(EFFECTS_DIR)/*.o $(ABILITIES_DIR)/*.o
	rm -f display_all_cards_gui display_all_cards_gui.o