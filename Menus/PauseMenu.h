#ifndef PROJEKT_PJC_PAUSEMENU_H
#define PROJEKT_PJC_PAUSEMENU_H
#pragma once
#include "BaseMenu.h"

class PauseMenu : public BaseMenu {
public:
    PauseMenu(const sf::Font &font);
    void setFont(const sf::Font &font) {
        BaseMenu::setFont(font);
    }
};


#endif //PROJEKT_PJC_PAUSEMENU_H
