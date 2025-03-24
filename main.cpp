#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Menus/MainMenu.h"
#include "Menus/SettingsMenu.h"
#include "Menus/PauseMenu.h"
#include "Menus/DifficultyMenu.h"
#include "GameLogic/WordManager.h"

const auto WINDOW_WIDTH = 1920;
const auto WINDOW_HEIGHT = 1080;

auto main() -> int {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Monkey Typer");
    window.setFramerateLimit(60);

    // Ładowanie czcionek
    std::vector<sf::Font> fonts;
    sf::Font font1, font2, font3, font4;
    std::vector<std::string> fontPaths = {
            "../Fonts/CreativeVibesTTF.ttf",
            "../Fonts/JetBrainsMono.ttf",
            "../Fonts/Minecraft.ttf",
            "../Fonts/RobotoMono.ttf"
    };

    for (const auto& path : fontPaths) {
        sf::Font font;
        if (!font.loadFromFile(path)) {
            std::cerr << "Error loading font: " << path << "\n";
        }
        fonts.push_back(font);
    }
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<std::string> backgroundPaths = {
            "../Backgrounds/font1image.png",
            "../Backgrounds/font2image.jpg",
            "../Backgrounds/font3image.jpg",
            "../Backgrounds/font4image.jpg"
    };

// Załaduj domyślne tło (np. dla pierwszej czcionki)
    if (!backgroundTexture.loadFromFile(backgroundPaths[0])) {
        std::cerr << "Could not load background!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    auto currentFontIndex = 0;
    auto currentFontSize = 30;
    sf::Font currentGameFont = fonts[currentFontIndex];

    // Inicjalizacja menu
    MainMenu mainMenu(currentGameFont);

    // Główna pętla gry
    while (window.isOpen()) {
        // Ekran główny
        auto menuResult = mainMenu.showMenu(window);

        switch (menuResult) {
            case MainMenuOption::Play: {
                // Wybór trudności
                DifficultyMenu difficultyMenu(currentGameFont);
                DifficultyMenuOption chosenDifficulty = difficultyMenu.showMenu(window);

                // Ustawienia gry na podstawie wybranej trudności
                float wordSpeed = 150.0f; // Domyślna prędkość
                float spawnInterval = 1.5f; // Domyślny interwał

                switch (chosenDifficulty) {
                    case DifficultyMenuOption::Easy:
                        wordSpeed = 100.0f;
                        spawnInterval = 2.0f;
                        break;
                    case DifficultyMenuOption::Medium:
                        wordSpeed = 200.0f;
                        spawnInterval = 1.0f;
                        break;
                    case DifficultyMenuOption::Hard:
                        wordSpeed = 300.0f;
                        spawnInterval = 0.5f;
                        break;
                    case DifficultyMenuOption::Custom:
                        wordSpeed = difficultyMenu.getCustomSpeed();
                        spawnInterval = difficultyMenu.getcustomSpawnInterval();
                        break;
                    case DifficultyMenuOption::Back:
                        continue;
                }

                // Inicjalizacja WordManager z wybranymi ustawieniami
                wordManager wordManager(currentGameFont,currentFontSize,wordSpeed, WINDOW_HEIGHT, spawnInterval, "../Words/Eng.txt",1);

                // Rozpocznij grę
                bool inGame = true;
                std::string currentInput; // Przechowuje aktualne wprowadzone znaki

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
                                    wordManager.reset(); // Reset gry
                                    break;
                                case 3: // Main Menu
                                    inGame = false;
                                    break;
                                case 4: // Quit
                                    window.close();
                                    break;
                            }
                        }

                        // Obsługa wprowadzania tekstu
                        if (event.type == sf::Event::TextEntered) {
                            if (event.text.unicode == 8 && !currentInput.empty()) { // Backspace
                                currentInput.pop_back();
                            } else if (event.text.unicode == 13) { // Enter
                                if (wordManager.removeWord(currentInput)) {
                                    currentInput.clear(); // Wyczyść input po poprawnym usunięciu słowa
                                }
                            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) { // Znaki drukowalne
                                currentInput += static_cast<char>(event.text.unicode);
                            }
                        }
                    }

                    // Aktualizacja stanu gry
                    wordManager.update(1.0f / 60.0f);

                    // Sprawdź, czy gra się zakończyła
                    if (wordManager.isGameOver()) {
                        std::cout << "Game Over!\n";
                        inGame = false;
                    }

                    // Renderowanie gry
                    window.clear();
                    window.draw(backgroundSprite);
                    wordManager.render(window);

                    // Renderowanie aktualnego inputu
                    sf::Text inputText(currentInput, currentGameFont, currentFontSize);
                    inputText.setPosition(50, WINDOW_HEIGHT - 100);
                    inputText.setFillColor(sf::Color::White);
                    window.draw(inputText);

                    window.display();
                }
                break;
            }

            case MainMenuOption::Settings: {
                SettingsMenu settings(fonts[currentFontIndex], fonts, currentFontSize, currentFontIndex);
                settings.run(window);

                // Aktualizuj ustawienia po zamknięciu menu
                currentFontSize = settings.getFontSize();
                currentFontIndex = settings.getCurrentFontIndex();
                currentGameFont = settings.getCurrentFont();

                // Aktualizuj tło
                if (currentFontIndex >= 0 && currentFontIndex < backgroundPaths.size()) {
                    if (!backgroundTexture.loadFromFile(backgroundPaths[currentFontIndex])) {
                        std::cerr << "Error loading background: " << backgroundPaths[currentFontIndex] << "\n";
                    }
                    backgroundSprite.setTexture(backgroundTexture);
                }

                mainMenu.setFont(currentGameFont);
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
    return 0;
}