//
// Created by pawel on 15/03/2025.
//

#include "DifficultyMenu.h"

DifficultyMenu::DifficultyMenu(const sf::Font& font) : BaseMenu(font) {
    addMenuItem("Easy", {800, 310}, 50);
    addMenuItem("Medium", {800, 425}, 50);
    addMenuItem("Hard", {800, 540}, 50);
    addMenuItem("Custom", {800, 655}, 50);
    addMenuItem("Back", {800, 770}, 50);
}

DifficultyMenuOption DifficultyMenu::showMenu(sf::RenderWindow& window) {
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                return DifficultyMenuOption::Back;
            }
            if(handleEvent(event)){
                switch (selectedItemIndex) {
                    case 0: return DifficultyMenuOption::Easy;
                    case 1: return DifficultyMenuOption::Medium;
                    case 2: return DifficultyMenuOption::Hard;
                    case 3: // Custom
                        handleCustomSettings(window);
                        return DifficultyMenuOption::Custom;
                    case 4: // Back
                        return DifficultyMenuOption::Back;
                    default:
                        return static_cast<DifficultyMenuOption>(selectedItemIndex);
                }
            }
        }
        window.clear();
        draw(window);
        sf::Text title("Choose Difficulty", font, 100);
        title.setPosition(500, 110);
        window.draw(title);
        window.display();
    }
    return DifficultyMenuOption::Back;
}

void DifficultyMenu::handleCustomSettings(sf::RenderWindow &window) {
    sf::Text speedPrompt("Enter speed (50 - 500):", font, 50);
    speedPrompt.setPosition(300, 310);
    sf::Text intervalPrompt("Enter spawn interval (0.5 - 5):", font, 50);
    intervalPrompt.setPosition(300, 425);

    std::string speedInput;
    std::string intervalInput;
    bool speedSet = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) { // Enter key
                    if (!speedSet) {
                        try {
                            float tempSpeed = std::stof(speedInput);
                            if (tempSpeed >= 50.0f && tempSpeed <= 500.0f) {
                                customSpeed = tempSpeed;
                                speedSet = true;
                            } else {
                                speedInput.clear();
                            }
                        } catch (std::exception exception) {
                            speedInput.clear();
                        }
                    } else {
                        try {
                            float tempInterval = std::stof(intervalInput);
                            if (tempInterval >= 0.5f && tempInterval <= 5.0f) {
                                customSpawnInterval = tempInterval;
                                return; // Exit function after setting interval
                            } else {
                                intervalInput.clear();
                            }
                        } catch (std::exception exception) {
                            intervalInput.clear();
                        }
                    }
                } else if (event.text.unicode == 8) { // Backspace key
                    if (!speedSet && !speedInput.empty()) {
                        speedInput.pop_back();
                    } else if (speedSet && !intervalInput.empty()) {
                        intervalInput.pop_back();
                    }
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) { // Printable characters
                    if (!speedSet) {
                        speedInput += static_cast<char>(event.text.unicode);
                    } else {
                        intervalInput += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }
        window.clear();
        window.draw(speedPrompt);
        window.draw(intervalPrompt);

        sf::Text speedText(speedInput, font, 50);
        speedText.setPosition(600, 310);
        window.draw(speedText);

        sf::Text intervalText(intervalInput, font, 50);
        intervalText.setPosition(600, 425);
        window.draw(intervalText);

        window.display();
    }
}

float DifficultyMenu::getCustomSpeed() const {
    return customSpeed;
}

float DifficultyMenu::getcustomSpawnInterval() const {
    return customSpawnInterval;
}
