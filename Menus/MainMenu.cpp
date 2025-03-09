//
// Created by pawel on 09/03/2025.
//

#include "MainMenu.h"
MainMenu::MainMenu(const sf::Font& font) : BaseMenu(font) {
    addMenuItem("Play", {800, 310}, 50);
    addMenuItem("Settings", {800, 425}, 50);
    addMenuItem("Load Save", {800, 540}, 50);
    addMenuItem("High Scores", {800, 655}, 50);
    addMenuItem("Quit", {800, 770}, 50);
}
MainMenuOption MainMenu::showMenu(sf::RenderWindow& window) {
    int result = run(window);
    return static_cast<MainMenuOption>(result);
}

void MainMenu::draw(sf::RenderWindow& window) const {
    BaseMenu::draw(window);
    sf::Text title ("Monkey Typer", font, 100);
    title.setPosition(500, 110);
    window.draw(title);

}