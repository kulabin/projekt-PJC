#include "BaseMenu.h"
BaseMenu::BaseMenu(const sf::Font& font): font(font), selectedItemIndex(0) {
}

void BaseMenu::addMenuItem(const std::string& text, const sf::Vector2f& position, int fontSize) {
    sf::Text menuItem(text, font, fontSize);
    menuItem.setPosition(position);
    menuItems.push_back(menuItem);
}

int BaseMenu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                return -1;
            }
            if (handleEvent(event)) {
                return selectedItemIndex;
            }
        }
        draw(window);
        window.display();
    }
    return selectedItemIndex;
}

bool BaseMenu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up && selectedItemIndex > 0) {
            selectedItemIndex--;
        } else if (event.key.code == sf::Keyboard::Down && selectedItemIndex < menuItems.size() - 1) {
            selectedItemIndex++;
        }else if (event.key.code == sf::Keyboard::Enter) {
            return true;
        }
    }
    return false;
}

void BaseMenu::draw(sf::RenderWindow& window) const {
    window.clear(sf::Color::Black);
    for(size_t i =0; i < menuItems.size(); ++i){
        sf::Text item = menuItems[i];
        item.setFillColor(selectedItemIndex == i ? sf::Color::Red : sf::Color::White);
        window.draw(item);
    }
}

void BaseMenu::setFont(const sf::Font& Font) {
    font = Font;
    for(auto& item: menuItems){
        item.setFont(font);
    }
}

void BaseMenu::setFontSize(int size) {
    for(auto& item: menuItems){
        item.setCharacterSize(size);
    }
}