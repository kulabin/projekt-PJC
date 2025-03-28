#ifndef PROJEKT_PJC_MAINMENU_H
#define PROJEKT_PJC_MAINMENU_H
#pragma once
#include "BaseMenu.h"

enum class MainMenuOption {
    Play,
    Settings,
    LoadSave,
    HighScores,
    Quit
};

class MainMenu : public BaseMenu {
    void draw(sf::RenderWindow& window) const override;
public:
    MainMenu(const sf::Font& font);
    MainMenuOption showMenu(sf::RenderWindow& window);
    void setFont(const sf::Font &font) {
        BaseMenu::setFont(font);
    }
};


#endif //PROJEKT_PJC_MAINMENU_H
