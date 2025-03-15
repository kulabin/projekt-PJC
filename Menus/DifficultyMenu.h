//
// Created by pawel on 15/03/2025.
//

#ifndef PROJEKT_PJC_DIFFICULTYMENU_H
#define PROJEKT_PJC_DIFFICULTYMENU_H
#include "BaseMenu.h"

enum class DifficultyMenuOption{
    Easy,
    Medium,
    Hard,
    Custom,
    Back
};

class DifficultyMenu : public BaseMenu{
private:
    float customSpeed;
    float customSpawnInterval;
    void handleCustomSettings(sf::RenderWindow& window);
public:
    DifficultyMenu(const sf::Font& font);
    DifficultyMenuOption showMenu(sf::RenderWindow& window);

    float getCustomSpeed() const;
    float getcustomSpawnInterval() const;
    void setFont(const sf::Font &font) {
        BaseMenu::setFont(font);
    }
};


#endif //PROJEKT_PJC_DIFFICULTYMENU_H
