CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: test.o Player.o Deck.o Card.o ChampionCard.o Ability.o SacrificeAbility.o
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run clean

run: test
	./test

clean:
	rm -f *.o *~ *.core test
