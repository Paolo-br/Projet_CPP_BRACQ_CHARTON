CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: test.o Player.o Deck.o Card.o ChampionCard.o Ability.o SacrificeAbility.o Hand.o InPlayArea.o DiscardPile.o Market.o AllyAbility.o ActivateAbility.o Faction.o Game.o GameSettings.o PrimaryAbility.o Turn.o \
      ActionCard.o ItemCard.o Effect.o GoldEffect.o AttackEffect.o HealEffect.o DrawEffect.o SacrificeEffect.o
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run clean

run: test
	./test

clean:
	rm -f *.o *~ *.core test
