#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <SFML/Graphics.hpp>

#include <Helper.h>

class SomeClass {
public:
    explicit SomeClass(int) {}
};

std::unique_ptr<SomeClass> getC() {
    return std::make_unique<SomeClass>(2);
}

class Player {
public:
    Player(const std::string& name)
        : name(name), streak(0), attempts(0), totalTime(0) {
        std::cout << "constructor Player\n";
    }

    void incrementStreak() { ++streak; }
    void resetStreak() { streak = 0; }
    void addAttempt() { ++attempts; }
    void addTime(double time) { totalTime += time; }

    const std::string& getName() const { return name; }
    int getStreak() const { return streak; }
    int getAttempts() const { return attempts; }
    double getTotalTime() const { return totalTime; }

    void saveStatistics() const {
        std::ofstream file("player_stats.txt", std::ios::app);
        if (file.is_open()) {
            file << "Player: " << name << "\n";
            file << "Streak: " << streak << "\n";
            file << "Attempts: " << attempts << "\n";
            file << "Total Time: " << totalTime << " seconds\n";
            file << "--------------------------\n";
            file.close();
        } else {
            std::cerr << "Error: Could not open file to save statistics.\n";
        }
    }

    ~Player() = default;

private:
    std::string name;
    int streak;
    int attempts;
    double totalTime;
};

class Word {
public:
    Word(const std::string& word, const std::vector<std::string>& validWords)
        : word(word), validWords(validWords), litere("abcdefghijklmnopqrstuvwxyz") {
        std::cout << "constructor Word\n";
    }

    const std::string& getWord() const { return word; }

    bool isValid(const std::string& guess) const {
        if (std::find(validWords.begin(), validWords.end(), guess) == validWords.end()) {
            return false;
        }
        for (char c : guess) {
            if (!std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    bool correctLength(const std::string& guess) const { return guess.size() == word.size(); }
    bool isCorrect(const std::string& guess) const { return guess == word; }
    std::string getHint(const std::string& guess) const {
        std::string hint;
        for (size_t i = 0; i < word.size(); ++i) {
            if (i < guess.size() && guess[i] == word[i]) {
                hint += guess[i];
            } else if (i < guess.size() && word.find(guess[i]) != std::string::npos) {
                hint += '+';
            } else {
                hint += '_';
            }
        }
        return hint;
    }

    std::string verifyLetters(const std::string& guess) const {
        std::string result;
        for (size_t i = 0; i < word.size(); ++i) {
            if (i < guess.size() && guess[i] == word[i]) {
                result += "The letter " + std::string(1, guess[i]) + " is on the right position\n";
            } else if (i < guess.size() && word.find(guess[i]) != std::string::npos) {
                result += "The letter " + std::string(1, guess[i]) + " is in the word but not on the right position\n";
            } else if (i < guess.size()) {
                result += "The letter " + std::string(1, guess[i]) + " is not in the word\n";
            }
        }
        return result;
    }

    std::string getLitere(const std::string& guess) {
        for (size_t i = 0; i < guess.size(); ++i) {
            if (word.find(guess[i]) == std::string::npos) {
                litere[litere.find(guess[i])] = '-';
            }
        }
        return litere;
    }

    ~Word() = default;

private:
    std::string word;
    std::vector<std::string> validWords;
    std::string litere;
};

class Game {
public:
    Game(const std::string& word, const std::vector<std::string>& validWords, Player& player)
        : word(word, validWords), attempts(6), player(player) {
        std::cout << "constructor Game\n";
    }

    void play() {
        std::string guess;
        auto start = std::chrono::high_resolution_clock::now();
        while (attempts > 0) {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            player.addAttempt();
            if (!word.isValid(guess)) {
                std::cout << "Invalid guess! Please enter a valid word from the list." << std::endl;
                continue;
            }
            if (!word.correctLength(guess)) {
                std::cout << "Invalid guess! The word has " << word.getWord().size() << " letters." << std::endl;
                continue;
            }
            if (word.isCorrect(guess)) {
                std::cout << "Congratulations! You've guessed the word: " << word.getWord() << std::endl;
                player.incrementStreak();
                break;
            } else {
                std::cout << word.verifyLetters(guess) << std::endl;
                std::cout << "Hint: " << word.getHint(guess) << std::endl;
                --attempts;
                std::cout << "Attempts remaining: " << attempts << std::endl;
                std::cout << "Used letters are: " << word.getLitere(guess) << "\n";
            }
        }
        if (attempts == 0) {
            std::cout << "Game over! The word was: " << word.getWord() << std::endl;
            player.resetStreak();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        player.addTime(elapsed.count());
        player.saveStatistics();
        showStatistics();
    }

    void showStatistics() const {
        std::cout << "Player: " << player.getName() << "\n";
        std::cout << "Streak: " << player.getStreak() << "\n";
        std::cout << "Attempts: " << player.getAttempts() << "\n";
        std::cout << "Total Time: " << player.getTotalTime() << " seconds\n";
    }

    ~Game() = default;

private:
    Word word;
    int attempts;
    Player& player;
};

std::vector<std::string> loadWords(const std::string& filename) {
    std::vector<std::string> words;
    std::string path = "../";
    path += filename;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return words;
    }
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;
    Player player(playerName);

    std::vector<std::string> words = loadWords("words.txt");
    if (words.empty()) {
        std::cerr << "Failed to load words from file." << std::endl;
        return 1;
    }

    std::srand(std::time(0));
    char playAgain;
    do {
        std::string randomWord = words[std::rand() % words.size()];
        Game game(randomWord, words, player);
        game.play();
        std::cout << "Do you want to play another game? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    Helper helper;
    helper.help();

    auto c = getC();
    std::cout << c.get() << "\n";

    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    window.setVerticalSyncEnabled(true);                                    ///
    /// window.setFramerateLimit(60);                                       ///
    ///////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if (e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if (shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }
    return 0;
}