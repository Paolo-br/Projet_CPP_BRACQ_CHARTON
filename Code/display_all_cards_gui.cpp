// Test d'affichage 'graphique' utilisant Utils (ANSI + curseur)
#include <iostream>
#include <vector>
#include <string>
#include "CardFactory.h"
#include "Utils.h"

int main() {
    std::vector<std::string> allNames = {
        "Or","Épée Courte","Dague","Rubis","Fire Gem",
        "Arkus, Imperial Dragon","Close Ranks","Command","Darian, War Mage","Domination","Cristov, the Just","Kraka, High Priest",
        "Man-at-Arms","Master Weyan","Rally the Troops","Recruit","Tithe Priest","Taxation","Word of Power",
        "Borg, Ogre Mercenary","Bribe","Death Threat","Deception","Fire Bomb","Hit Job","Intimidation",
        "Myros, Guild Mage","Parov, the Enforcer","Profit","Rake, Master Assassin","Rasmus, the Smuggler","Smash and Grab","Street Thug",
        "Cult Priest","Dark Energy","Dark Reward","Death Cultist","Death Touch","Rayla, Endweaver","Influence",
        "Krythos, Master Vampire","Life Drain","Lys, the Unseen","The Rot","Tyrannor, the Devourer","Varrick, the Necromancer",
        "Broelyn, Loreweaver","Cron, the Berserker","Dire Wolf","Elven Curse","Elven Gift","Grak, Storm Giant",
        "Nature's Bounty","Orc Grunt","Rampage","Torgen Rocksplitter","Spark","Wolf Form","Wolf Shaman"
    };

    std::vector<Card*> cards;
    cards.reserve(allNames.size());

    for (const auto& name : allNames) {
        Card* c = CardFactory::createCard(name);
        if (c) cards.push_back(c);
    }

    // Use the cursor/ANSI rendering but paginate to avoid terminal overflow.
    Utils::clearScreen();
    const int colsPerRow = 4;
    const int spacing = 3; // columns between cards
    const int pageSize = 8; // number of cards per page (4 columns x 2 rows)
    int initialCol = 1;

    size_t total = cards.size();
    for (size_t pageStart = 0; pageStart < total; pageStart += pageSize) {
        Utils::clearScreen();
        int baseRow = 1;
        size_t pageEnd = std::min(total, pageStart + pageSize);

        // Render rows of up to colsPerRow until pageEnd
        for (size_t i = pageStart; i < pageEnd; ) {
            int currentCol = initialCol;
            int rowThisLine = baseRow;
            int maxBottom = rowThisLine;

            // place up to colsPerRow cards in this line
            for (int c = 0; c < colsPerRow && i < pageEnd; ++c, ++i) {
                Card* card = cards[i];
                if (!card) continue;

                auto res = card->display(rowThisLine, currentCol);
                int bottom = std::get<0>(res);
                int width = std::get<1>(res);
                if (bottom > maxBottom) maxBottom = bottom;

                currentCol += width + spacing;
            }

            // next base row is after the tallest card in this line
            baseRow = maxBottom + 2;
        }

        // If more pages remain, prompt user to continue
        if (pageEnd < total) {
            Utils::moveCursor(baseRow + 1, 1);
            std::cout << "--- Page " << (pageStart / pageSize + 1) << " affichée. Appuyez sur Entrée pour continuer..." << std::endl;
            std::cin.get();
        } else {
            Utils::moveCursor(baseRow + 1, 1);
            std::cout << "--- Fin des cartes. Appuyez sur Entrée pour quitter..." << std::endl;
            std::cin.get();
        }
    }

    std::cout << std::endl << "Appuyez sur Entrée pour quitter et libérer la mémoire..." << std::endl;
    std::cin.get();

    for (Card* c : cards) delete c;
    return 0;
}
