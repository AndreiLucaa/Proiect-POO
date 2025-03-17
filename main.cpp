#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

#include <Helper.h>

//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////

class Word {
public:
    Word(const std::string& word, const std::vector<std::string>& validWords)
        : word(word), validWords(validWords) {
        std::cout<<"constructor Word\n";

    }

    std::string getWord() const { return word; }

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
                //std::cout<<"The letter"<<" "<<guess[i]<<" "<<"is on the right position\n";
                hint += guess[i];
            }
            else if(word.find(guess[i]) != std::string::npos) {
                //std::cout<<"The letter"<<" "<<guess[i]<<" "<<"is in the word but not on the right position\n";
                hint += '+';
            }
            else {
                //std::cout<<"The letter"<<" "<<guess[i]<<" "<<"is not in the word\n";
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
            } else if (word.find(guess[i]) != std::string::npos) {
                result += "The letter " + std::string(1, guess[i]) + " is in the word but not on the right position\n";
            } else {
                result += "The letter " + std::string(1, guess[i]) + " is not in the word\n";
            }
        }
        return result;
    }
    std::string getLitere(const std::string& guess) const {
        std::string litere = "abcdefghijklmnopqrstuvwxyz";
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
};

class Game {
public:
    Game(const std::string& word, const std::vector<std::string>& validWords)
        : word(word, validWords), attempts(6) {}

    void play() {
        std::string guess;
        while (attempts > 0) {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
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
                return;
            } else {
                std::cout<<word.verifyLetters(guess)<<std::endl;
                std::cout << "Hint: " << word.getHint(guess) << std::endl;
                --attempts;
                std::cout << "Attempts remaining: " << attempts << std::endl;
                std::cout<<"Literele folosite sunt: "<<" "<<word.getLitere(guess)<<"\n";
            }
        }
        std::cout << "Game over! The word was: " << word.getWord() << std::endl;
    }

private:
    Word word;
    int attempts;
};

std::vector<std::string> loadWords(const std::string& filename) {
    std::vector<std::string> words;
    std::string path = "../";
    path+=filename;
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
    std::vector<std::string> words = loadWords("words.txt");
    if (words.empty()) {
        std::cerr << "Failed to load words from file." << std::endl;
        return 1;
    }

    std::srand(std::time(0));
    std::string randomWord = words[std::rand() % words.size()];

    Game game(randomWord, words);
    game.play();

    Helper helper;
    helper.help();

    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;  // comentarea acestui rând ar trebui să ducă la semnalarea unui mem leak

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

    while(window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if(e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if(shouldExit) {
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
