//
// Created by pawel on 15/03/2025.
//

#ifndef PROJEKT_PJC_WORDMANAGER_H
#define PROJEKT_PJC_WORDMANAGER_H
#include <SFML/Graphics.hpp>
#include "Word.h"
#include <vector>
#include <string>
#include <random>

class wordManager {
public:
    wordManager(const sf::Font& font, int fontSize, float wordSpeed,int windowHeight, float spawnInterval, const std::string& filename, int wordsPerSpawn);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    bool removeWord(const std::string& input);
    bool isGameOver() const;
    void setGameOver(bool state);
    bool removeOutOfBoundsWords();
    void reset();
    void setInitialWords(const std::vector<Word>& initialWords);

private:
    void spawnWord();
    void loadWordsFromFile(const std::string& filename);

    const sf::Font& font;
    int fontSize;
    float wordSpeed;
    int windowWidth;
    int windowHeight;
    float spawnInterval;
    float spawnTimer;
    bool gameOver;
    int wordsPerSpawn;
    std::vector<Word> words;
    std::vector<std::string> wordList;

};


#endif //PROJEKT_PJC_WORDMANAGER_H
