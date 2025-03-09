#ifndef PROJEKT_PJC_SETTINGSMENU_H
#define PROJEKT_PJC_SETTINGSMENU_H
#pragma once
#include "BaseMenu.h"

class SettingsMenu : public BaseMenu{
private:
    std::vector<std::string> availableLanguages;
    int currentLanguageIndex;
    std::vector<sf::Font> availableFonts;
    int currentFontIndex;
    int currentFontSize;

public:
    SettingsMenu(const sf::Font& font,const std::vector<std::string>& languages,const std::vector<sf::Font>& fonts,int initialFontSize);
    bool handleEvent(const sf::Event& event) override;
    int getFontSize() const{
        return currentFontSize;
    }
    const sf::Font& getCurrentFont() const{
        return availableFonts[currentFontIndex];
    }
    std::string getCurrentLanguage() const{
        return availableLanguages[currentLanguageIndex];
    }
};


#endif //PROJEKT_PJC_SETTINGSMENU_H
