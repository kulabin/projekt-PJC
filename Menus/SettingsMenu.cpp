#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(const sf::Font& font, const std::vector<sf::Font>& fonts, int initialFontSize, int initialFontIndex)
        : BaseMenu(font), fonts(fonts), currentFontIndex(initialFontIndex), fontSize(initialFontSize) {

    float posY = 300.f;
    const float spacing = 60.f;

    // Dodaj opcje czcionek
    for (size_t i = 0; i < fonts.size(); ++i) {
        addMenuItem("Font " + std::to_string(i+1), sf::Vector2f(700.f, posY), 40);
        posY += spacing;
    }

    // Dodaj opcje zmiany rozmiaru czcionki
    addMenuItem("Increase Font Size", sf::Vector2f(700.f, posY), 40);
    posY += spacing;
    addMenuItem("Decrease Font Size", sf::Vector2f(700.f, posY), 40);
    posY += spacing;

    // Dodaj przycisk powrotu
    addMenuItem("Back", sf::Vector2f(700.f, posY), 40);
    backIndex = menuItems.size() - 1;
}

bool SettingsMenu::handleEvent(const sf::Event& event) {
    bool baseResult = BaseMenu::handleEvent(event);

    if (baseResult) {
        if (selectedItemIndex == backIndex) {
            return true; // Zamknij menu
        } else {
            if (selectedItemIndex < fonts.size()) {
                currentFontIndex = selectedItemIndex;
            } else if (selectedItemIndex == fonts.size()) {
                fontSize += 2;
                setFontSize(fontSize);
            } else if (selectedItemIndex == fonts.size() + 1) {
                fontSize = std::max(12, fontSize - 2);
                setFontSize(fontSize);
            }
            return false; // Pozostań w menu
        }
    }
    return false;
}

int SettingsMenu::getFontSize() const {
    return fontSize;
}

const sf::Font& SettingsMenu::getCurrentFont() const {
    return fonts[currentFontIndex];
}

int SettingsMenu::getCurrentFontIndex() const {
    return currentFontIndex;
}
