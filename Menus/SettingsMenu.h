#ifndef PROJEKT_PJC_SETTINGSMENU_H
#define PROJEKT_PJC_SETTINGSMENU_H
#pragma once
#include "BaseMenu.h"

#include "BaseMenu.h"
#include <vector>

class SettingsMenu : public BaseMenu {
private:
    std::vector<sf::Font> fonts;
    int currentFontIndex;
    int fontSize;
    int backIndex;

public:
    SettingsMenu(const sf::Font& font, const std::vector<sf::Font>& fonts, int initialFontSize, int initialFontIndex);
    bool handleEvent(const sf::Event& event) override;

    int getFontSize() const;
    const sf::Font& getCurrentFont() const;
    int getCurrentFontIndex() const;
};


#endif //PROJEKT_PJC_SETTINGSMENU_H
