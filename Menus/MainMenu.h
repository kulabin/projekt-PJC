//
// Created by pawel on 09/03/2025.
//

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

};


#endif //PROJEKT_PJC_MAINMENU_H
