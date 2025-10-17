#ifndef __CHOICEEFFECT_H
#define __CHOICEEFFECT_H

#include "Effect.h"
#include <vector>
#include <string>

class Player;
class Turn;

class ChoiceEffect : public Effect {
private:
    Effect* m_option1;
    Effect* m_option2;
    std::string m_description1;
    std::string m_description2;

public:
    ChoiceEffect(Effect* option1, const std::string& desc1, 
                 Effect* option2, const std::string& desc2);
    
    ~ChoiceEffect() override;
    
    // Règle des 5
    ChoiceEffect(const ChoiceEffect& other);
    ChoiceEffect& operator=(const ChoiceEffect& other);
    ChoiceEffect(ChoiceEffect&& other) noexcept;
    ChoiceEffect& operator=(ChoiceEffect&& other) noexcept;
    
    void apply(Player& player, Turn& turn) override;
    std::string getName() const override;
    ChoiceEffect* clone() const override;
    
    // Getters
    Effect* getOption1() const { return m_option1; }
    Effect* getOption2() const { return m_option2; }
    std::string getDescription1() const { return m_description1; }
    std::string getDescription2() const { return m_description2; }
};

#endif
