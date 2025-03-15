//
// Created by pawel on 15/03/2025.
//

#include "wordManager.h"
#include <fstream>
#include <algorithm>
#include <set>

wordManager::wordManager(const sf::Font& font, int fontsize, float wordSpeed, int windowHeight, float spawnInterval, const std::string& filename, int wordsPerSpawn)
        : font(font), fontSize(fontsize), wordSpeed(wordSpeed), windowHeight(windowHeight), spawnInterval(spawnInterval), spawnTimer(0), gameOver(false), wordsPerSpawn(wordsPerSpawn) {
    srand(static_cast<unsigned int>(time(0)));
    loadWordsFromFile(filename);
}

void wordManager::loadWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            wordList.push_back(word);
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file");
    }
}
void wordManager::update(float deltaTime) {
    if (gameOver) return;

    for (auto& word : words) {
        word.update(deltaTime);
    }

    // Spawning new words based on the spawn interval
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        spawnWord();
    }

    // Remove words that have gone out of screen bounds
    words.erase(std::remove_if(words.begin(), words.end(), [](const Word& word) {
        return word.getBounds().left + word.getBounds().width < 0; // Word is completely out of screen on the left
    }), words.end());
}

void wordManager::render(sf::RenderWindow& window) {
    for (const auto& word : words) {
        word.render(window);
    }
}

bool wordManager::removeWord(const std::string& input) {
    // Find the closest word to the right of the screen
    auto closestWordIter = std::min_element(words.begin(), words.end(), [](const Word& a, const Word& b) {
        return a.getBounds().left > b.getBounds().left;
    });

    if (closestWordIter != words.end() && closestWordIter->getText().substr(0, input.size()) == input) {
        closestWordIter->removeCharacters(input.size());
        if (closestWordIter->getText().empty()) {
            words.erase(closestWordIter);
        }
        return true;
    }
    return false;
}

bool wordManager::isGameOver() const {
    return gameOver;
}

void wordManager::setGameOver(bool state) {
    gameOver = state;
}

void wordManager::spawnWord() {
    // Sprawdź, czy lista słów nie jest pusta
    if (wordList.empty()) return;

    // Zbiór aktualnie aktywnych słów (do unikania duplikatów)
    std::set<std::string> currentWords;
    for (const auto& word : words) {
        currentWords.insert(word.getText());
    }

    // Spawnuj określoną liczbę słów
    for (int i = 0; i < wordsPerSpawn; ++i) {
        std::string wordText;
        int attempts = 0;
        const int maxAttempts = 10; // Maksymalna liczba prób znalezienia unikalnego słowa

        // Unikaj duplikatów
        do {
            wordText = wordList[rand() % wordList.size()]; // Losowe słowo z listy
            attempts++;
        } while (currentWords.find(wordText) != currentWords.end() && attempts < maxAttempts);

        // Jeśli nie udało się znaleźć unikalnego słowa, pomiń to słowo
        if (attempts >= maxAttempts) {
            continue;
        }

        // Wybierz pozycję Y, unikając nakładania się z istniejącymi słowami
        float positionY;
        attempts = 0;
        bool overlap;

        do {
            positionY = static_cast<float>(rand() % (windowHeight - 60)); // Losowa pozycja Y
            overlap = false;

            // Sprawdź, czy nowe słowo nakłada się na istniejące
            for (const auto& word : words) {
                if (abs(word.getBounds().top - positionY) < 50) { // Minimalna odległość między słowami
                    overlap = true;
                    break;
                }
            }

            attempts++;
        } while (overlap && attempts < maxAttempts);

        // Jeśli nie udało się znaleźć pozycji bez nakładania, pomiń to słowo
        if (attempts >= maxAttempts) {
            continue;
        }

        // Dodaj nowe słowo do listy
        words.emplace_back(wordText, font, fontSize, wordSpeed, positionY);
        currentWords.insert(wordText); // Dodaj słowo do zbioru aktywnych słów
    }
}

void wordManager::setInitialWords(const std::vector<Word>& initialWords) {
    words = initialWords;
    spawnTimer = 0;
}

void wordManager::reset() {
    words.clear();
    gameOver = false;
    spawnTimer = 0;
}