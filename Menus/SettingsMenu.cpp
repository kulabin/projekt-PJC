#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(const sf::Font& font, const std::vector<std::string>& languages, const std::vector<sf::Font>& fonts, int initialFontSize)
    : BaseMenu(font), availableLanguages(languages), availableFonts(fonts), currentFontSize(initialFontSize){
    currentLanguageIndex = 0;
    currentFontIndex = 0;
    addMenuItem("Change Font", {800, 310}, 50);
    addMenuItem("Change ingame font size", {800, 425}, 50);
    addMenuItem("Language", {800, 540}, 50);
    addMenuItem("Back", {800, 655}, 50);
}

bool SettingsMenu::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            if (selectedItemIndex == 0) {//jezyk
                currentLanguageIndex = (currentLanguageIndex + 1) % availableFonts.size();
            } else {
                currentLanguageIndex = (currentLanguageIndex - 1) % availableFonts.size();
            }
        } else if (selectedItemIndex == 1) {//czcionka
            if (event.key.code == sf::Keyboard::Right) {
                currentFontIndex = (currentFontIndex + 1) % availableFonts.size();
            } else {
                currentFontIndex = (currentFontIndex - 1) % availableFonts.size();
            }
        } else if (selectedItemIndex == 2) {
            if (event.key.code == sf::Keyboard::Right) {
                currentFontSize++;
            } else {
                currentFontSize--;
            }
            menuItems[2].setString("Font size: " + std::to_string(currentFontSize));
            setFontSize(currentFontSize);
            return true;
        }
    }
    return BaseMenu::handleEvent(event);
}