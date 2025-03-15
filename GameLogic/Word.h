//
// Created by pawel on 15/03/2025.
//

#ifndef PROJEKT_PJC_WORD_H
#define PROJEKT_PJC_WORD_H
#include <SFML/Graphics.hpp>
#include <string>

class Word {
public:
    Word(const std::string& text, const sf::Font& font,int fontSize, float speed, float posY);
    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;
    const std::string& getText() const;
    void removeCharacters(int count);
    sf::FloatRect getBounds() const;
    bool operator==(const Word& other) const;
    void setPosition(float x, float y);
private:
    std::string text;
    float speed;
    sf::Text sfText;

};


#endif //PROJEKT_PJC_WORD_H
