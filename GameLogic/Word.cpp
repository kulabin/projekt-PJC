//
// Created by pawel on 15/03/2025.
//

#include "Word.h"

Word::Word(const std::string &text, const sf::Font &font, int fontSize, float speed, float posY) : text(text),speed(speed) {
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(sf::Color::White);
    sfText.setPosition(0, posY);
}

void Word::update(float deltaTime) {
    sfText.move(speed * deltaTime, 0);
}

void Word::render(sf::RenderWindow &window) const {
    window.draw(sfText);
}

const std::string &Word::getText() const {
    return text;
}

void Word::removeCharacters(int count) {
    text.erase(0, count);
    sfText.setString(text);
}

sf::FloatRect Word::getBounds() const {
    return sfText.getGlobalBounds();
}

bool Word::operator==(const Word &other) const {
    return text == other.text && sfText.getPosition() == other.sfText.getPosition();
}

void Word::setPosition(float x, float y) {
    sfText.setPosition(x, y);
}


