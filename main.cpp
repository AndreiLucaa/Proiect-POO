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
    explicit Player(const std::string& name)
        : name(name), streak(0), attempts(0), totalTime(0) {
        std::cout << "constructor Player\n";
    }

    Player(const Player &other)
        : name(other.name),
          streak(other.streak),
          attempts(other.attempts),
          totalTime(other.totalTime) {
    }

    Player(Player &&other) noexcept
        : name(std::move(other.name)),
          streak(other.streak),
          attempts(other.attempts),
          totalTime(other.totalTime) {
    }

    Player & operator=(const Player &other) {
        if (this == &other)
            return *this;
        name = other.name;
        streak = other.streak;
        attempts = other.attempts;
        totalTime = other.totalTime;
        return *this;
    }

    Player & operator=(Player &&other) noexcept {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        streak = other.streak;
        attempts = other.attempts;
        totalTime = other.totalTime;
        return *this;
    }

    void incrementStreak() { privateIncrementStreak(); }
    void resetStreak() { privateResetStreak(); }
    void addAttempt() { privateAddAttempt(); }
    void addTime(double time) { privateAddTime(time); }

    const std::string& getName() const { return name; }
    int getStreak() const { return streak; }
    int getAttempts() const { return attempts; }
    double getTotalTime() const { return totalTime; }

    // void saveStatistics() const {
    //     std::ofstream file("player_stats.txt", std::ios::app);
    //     if (file.is_open()) {
    //         file << "Player: " << name << "\n";
    //         file << "Streak: " << streak << "\n";
    //         file << "Attempts: " << attempts << "\n";
    //         file << "Total Time: " << totalTime << " seconds\n";
    //         file << "--------------------------\n";
    //         file.close();
    //     } else {
    //         std::cerr << "Error: Could not open file to save statistics.\n";
    //     }
    // }

    ~Player() {
        std::cout << "destructor Player\n";
    };

private:
    std::string name;
    int streak;
    int attempts;
    double totalTime;

    void privateIncrementStreak() { ++streak; }
    void privateResetStreak() { streak = 0; }
    void privateAddAttempt() { ++attempts; }
    void privateAddTime(double time) { totalTime += time; }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player: " << player.getName() << "\n"
           << "Streak: " << player.getStreak() << "\n"
           << "Attempts: " << player.getAttempts() << "\n"
           << "Total Time: " << player.getTotalTime() << " seconds\n";
        return os;
    }
};


class Word {
public:
    Word(const std::string& word, const std::vector<std::string>& validWords)
        : word(word), validWords(validWords), litere("ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
        std::cout << "constructor Word\n";
    }

    Word(const Word &other)
        : word(other.word),
          validWords(other.validWords),
          litere(other.litere) {
    }

    Word(Word &&other) noexcept
        : word(std::move(other.word)),
          validWords(std::move(other.validWords)),
          litere(std::move(other.litere)) {
    }

    Word & operator=(const Word &other) {
        if (this == &other)
            return *this;
        word = other.word;
        validWords = other.validWords;
        litere = other.litere;
        return *this;
    }

    Word & operator=(Word &&other) noexcept {
        if (this == &other)
            return *this;
        word = std::move(other.word);
        validWords = std::move(other.validWords);
        litere = std::move(other.litere);
        return *this;
    }

    const std::string& getWord() const { return word; }

    bool isValid(const std::string& guess) const { return privateIsValid(guess); }
    bool correctLength(const std::string& guess) const { return privateCorrectLength(guess); }
    bool isCorrect(const std::string& guess) const { return privateIsCorrect(guess); }
    std::string getHint(const std::string& guess) const { return privateGetHint(guess); }
    std::string verifyLetters(const std::string& guess) const { return privateVerifyLetters(guess); }
    std::string getLetters(const std::string& guess) { return privateGetLetters(guess); }

    ~Word() = default;

private:
    std::string word;
    std::vector<std::string> validWords;
    std::string litere;

    bool privateIsValid(const std::string& guess) const {
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

    bool privateCorrectLength(const std::string& guess) const { return guess.size() == word.size(); }
    bool privateIsCorrect(const std::string& guess) const { return guess == word; }
    std::string privateGetHint(const std::string& guess) const {
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

    std::string privateVerifyLetters(const std::string& guess) const {
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

    std::string privateGetLetters(const std::string& guess) {
        for (size_t i = 0; i < guess.size(); ++i) {
            if (word.find(guess[i]) == std::string::npos) {
                litere[litere.find(guess[i])] = '-';
            }
        }
        return litere;
    }

    friend std::ostream& operator<<(std::ostream& os, const Word& word) {
        os << "Word: " << word.word << "\n"
           << "Valid Words: ";
        for (const auto& validWord : word.validWords) {
            os << validWord << " ";
        }
        os << "\n";
        return os;
    }
};

class Wordle {
public:
    Wordle(const std::string& word, const std::vector<std::string>& validWords, Player& player)
        : word(word, validWords), attempts(6), player(player) {
        std::cout << "====================================\n";
        std::cout << "       Welcome to Wordle++!        \n";
        std::cout << "====================================\n";
        std::cout << "Get ready to test your word-guessing skills!\n";
        std::cout << "Your goal is to find the hidden word by making guesses.\n";
        std::cout << "Each guess must be a valid word of the correct length.\n\n";

        std::cout << "How to Play:\n";
        std::cout << "✅ '+' → The letter is in the word but in the wrong position.\n";
        std::cout << "❌ '_' → The letter is not in the word at all.\n\n";

        std::cout << "Use these hints to refine your guesses and crack the code!\n";
        std::cout << "Good luck and have fun! 🎉\n";
    }

    void play() {
        std::string guess;
        auto start = std::chrono::high_resolution_clock::now();
        while (attempts > 0) {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
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
                std::cout << "Used letters are: " << word.getLetters(guess) << "\n";
            }
        }
        if (attempts == 0) {
            std::cout << "Game over! The word was: " << word.getWord() << std::endl;
            player.resetStreak();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        player.addTime(elapsed.count());
    }

    Wordle(const Wordle &other)
        : word(other.word),
          attempts(other.attempts),
          player(other.player) {
    }

    Wordle(Wordle &&other) noexcept
        : word(std::move(other.word)),
          attempts(other.attempts),
          player(other.player) {
    }

    Wordle & operator=(const Wordle &other) {
        if (this == &other)
            return *this;
        word = other.word;
        attempts = other.attempts;
        player = other.player;
        return *this;
    }

    Wordle & operator=(Wordle &&other) noexcept {
        if (this == &other)
            return *this;
        word = std::move(other.word);
        attempts = other.attempts;
        player = other.player;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Wordle& game) {
        os << "Wordle Game\n" << game.word << "\n"
        << "Attempts: " << game.attempts << "\n"
        << "Player:" << game.player << "\n";
        return os;
    }

    ~Wordle() = default;

private:
    Word word;
    int attempts;
    Player& player;
};

class Game {
public:
    Game(Player& player) : player(player) {
        std::cout << "constructor Game\n";
        std::cout << "====================================\n";
        std::cout << "       Welcome to Offline Games     \n";
        std::cout << "====================================\n";
        std::cout << "Choose a game mode:\n";
        std::cout << "1. Wordle++\n";
        std::cout << "2. Option 2 (coming soon...)\n";
        std::cout << "3. Option 3 (coming soon...)\n";
        std::cout << "0. Exit :(\n";
    }

    Game(const Game &other)
        : player(other.player) {
    }

    Game(Game &&other) noexcept
        : player(other.player) {
    }

    Game & operator=(const Game &other) {
        if (this == &other)
            return *this;
        player = other.player;
        return *this;
    }

    Game & operator=(Game &&other) noexcept {
        if (this == &other)
            return *this;
        player = other.player;
        return *this;
    }

    void playWordle(const std::string& word, const std::vector<std::string>& validWords) {
        Wordle wordleGame(word, validWords, player);
        wordleGame.play();
    }

    // Placeholder functions for other games
    void playOption2() {
        std::cout << "Option 2 is coming soon...\n";
    }

    void playOption3() {
        std::cout << "Option 3 is coming soon...\n";
    }

    void privateChoice() {
        std::string choice;
        std::cout<<"Enter your choice: ";
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "You've chosen Wordle++\n";
            int wordLength = getUserChoice();
            std::vector<std::string> words = loadWords(wordLength);
            if (words.empty()) {
                std::cerr << "Failed to load words from file." << std::endl;
                return;
            }
            std::string randomWord = words[std::rand() % words.size()];
            playWordle(randomWord, words);
        } else if (choice == "2") {
            playOption2();
        } else if (choice == "3") {
            playOption3();
        } else if (choice == "0") {
            std::cout << "Goodbye!\n";
            exit(0);
        } else {
            std::cout << "Invalid choice! Please enter a valid choice.\n";
        }
    }

    ~Game() {
        std::cout<<"Thank you for playing!\n";
    };

private:
    Player& player;

    int getUserChoice() {
        int choice;
        std::cout << "Enter the word length you want to play with: ";
        std::cin >> choice;
        return choice;
    }

    std::vector<std::string> loadWords(int wordLength) {
        std::vector<std::string> words;
        std::string filename = "../words" + std::to_string(wordLength) + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return words;
        }
        std::string word;
        while (file >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            words.push_back(word);
        }
        return words;
    }
};

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;
    Player player(playerName);

    Game game(player);

    char playAgain;
    do {
        std::cout << player << std::endl;
        game.privateChoice();
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