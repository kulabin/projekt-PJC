#include "PauseMenu.h"

PauseMenu::PauseMenu(const sf::Font &font) : BaseMenu(font) {
    addMenuItem("Resume", {800, 310}, 50);
    addMenuItem("Save", {800, 425}, 50);
    addMenuItem("Retry", {800, 540}, 50);
    addMenuItem("Main Menu", {800, 655}, 50);
    addMenuItem("Quit", {800, 770}, 50);
}