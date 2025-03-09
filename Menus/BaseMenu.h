#ifndef PROJEKT_PJC_BASEMENU_H
#define PROJEKT_PJC_BASEMENU_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BaseMenu {
protected:
    sf::Font font;
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;

    virtual void draw(sf::RenderWindow& window) const;
    virtual bool handleEvent(const sf::Event& event);
public:
    BaseMenu(const sf::Font& font);
    virtual ~BaseMenu() = default;
    void addMenuItem(const std::string& text,const sf::Vector2f& position,int fontSize);
    int run(sf::RenderWindow& window);
    void setFont(const sf::Font& Font);
    void setFontSize(int size);
};


#endif //PROJEKT_PJC_BASEMENU_H
