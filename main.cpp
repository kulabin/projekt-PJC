#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Menus/MainMenu.h"
#include "Menus/SettingsMenu.h"
#include "Menus/PauseMenu.h"


auto main() -> int {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Monkey Typer");
    window.setFramerateLimit(60);

    // Ładowanie czcionek
    sf::Font font1, font2,font3,font4;
    std::vector<sf::Font> fonts;

    if (!font1.loadFromFile("../fonts/CreativeVibesTTF.ttf")) {
        std::cerr << "Could not load font1!\n";
        return 1;
    }


    // Inicjalizacja menu
    MainMenu mainMenu(font1);
    std::vector<std::string> languages = {"English", "Polski"};
    int currentFontSize = 30;
    sf::Font currentGameFont = font1;

    // Główna pętla gry
    while (window.isOpen()) {
        // Ekran główny
        auto menuResult = mainMenu.showMenu(window);

        switch (menuResult) {
            case MainMenuOption::Play: {
                // Rozpocznij grę
                bool inGame = true;
                while (inGame && window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }

                        // Obsługa pauzy
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                            PauseMenu pauseMenu(currentGameFont);
                            int pauseResult = pauseMenu.run(window);

                            switch (pauseResult) {
                                case 0: // Resume
                                    break;
                                case 1: // Save
                                    std::cout << "Game saved!\n";
                                    break;
                                case 2: // Retry
                                    inGame = true;
                                    // Reset gry
                                    break;
                                case 3: // Main Menu
                                    inGame = false;
                                    break;
                                case 4: // Quit
                                    window.close();
                                    break;
                            }
                        }
                    }

                    // Renderowanie gry
                    window.clear();
                    // ... kod renderujący grę ...
                    window.display();
                }
                break;
            }

            case MainMenuOption::Settings: {
                SettingsMenu settings(font1, languages, fonts, currentFontSize);
                int settingsResult = settings.run(window);

                // Aktualizuj ustawienia jeśli wybrano "Back"
                if (settingsResult == 3) {
                    currentFontSize = settings.getFontSize();
                    currentGameFont = settings.getCurrentFont();
                    mainMenu.setFont(currentGameFont);
                }
                break;
            }

            case MainMenuOption::LoadSave:
                std::cout << "Loading save...\n";
                // ... kod ładowania ...
                break;

            case MainMenuOption::HighScores:
                std::cout << "Showing high scores...\n";
                // ... kod wyników ...
                break;

            case MainMenuOption::Quit:
                window.close();
                break;
        }
    }
    window.display();
    return 0;
}
