#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Menus/MainMenu.h"


auto main() -> int {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Monkey Typer");
    window.setFramerateLimit(60);
    sf::Font font;
    bool inGame = false;
    if (!font.loadFromFile("../fonts/Creative Vibes TTF.ttf")) {
        std::cerr << "Could not load font\n";
        return 1;
    }
    MainMenu mainMenu(font);
    while (window.isOpen()) {
        auto menuResult = mainMenu.showMenu(window);
        switch (menuResult) {
            case MainMenuOption::Play:
                inGame = true;
                break;
            case MainMenuOption::Settings:
                std::cout << "Settings\n";
                break;
            case MainMenuOption::LoadSave:
                std::cout << "Load Save\n";
                break;
            case MainMenuOption::HighScores:
                std::cout << "High Scores\n";
                break;
            case MainMenuOption::Quit:
                window.close();
                break;
        }
    }
    window.display();
    return 0;
}
