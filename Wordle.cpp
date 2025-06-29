//
// Created by Andrei Luca on 14.04.2025.
//

#include "Wordle.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <utility>

#include "InvalidCharacterException.h"
#include "InvalidWordLengthException.h"
#include "InvalidWordList.h"
#include "WordExceptions.h"

class WordException;

Wordle::Wordle(const std::string &word, const std::vector<std::string> &validWords, Player &player): word(word, validWords), attempts(6), player(player) {
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
    player.incrementGamesPlayed();
}

void Wordle::play() {
    std::string guess;
    auto start = std::chrono::high_resolution_clock::now();
    while (attempts > 0) {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
        player.addAttempt();
        try {
            if (!word.isValid(guess)) {
                throw InvalidCharacterException("The word contains invalid characters.");
            }
            if (!word.correctLength(guess)) {
                throw InvalidWordLengthException("The word has an incorrect length.");
            }
            if (!word.isValidWordList(guess)) {
                throw InvalidWordList("The word is not in the valid words list.");
            }
        } catch (const InvalidCharacterException &e) {
            std::cout << "Error: " << e.what() << std::endl;
            continue;
        } catch (const InvalidWordLengthException &e) {
            std::cout << "Error: " << e.what() << std::endl;
            continue;
        } catch (const InvalidWordList &e) {
            std::cout<< "Error: " << e.what() << std::endl;
            continue;
        }
        if (word.isCorrect(guess)) {
            std::cout << "Congratulations! You've guessed the word: " << word.getWord() << std::endl;
            player.incrementStreak();
            player.incrementGamesWon();
            std::cout << player << std::endl;
            break;
        } else {
            std::pair<std::string, std::string> result = word.verifyLetters(guess);
            std::cout << result << std::endl;
            --attempts;
            std::cout << "Attempts remaining: " << attempts << std::endl;
            std::cout << "Remaining letters are: " << word.getLetters(guess) << "\n";
        }
    }
    if (attempts == 0) {
        std::cout << "Game over! The word was: " << word.getWord() << std::endl;
        std::cout << player << std::endl;
        player.resetStreak();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    player.addTime(elapsed.count());
}

Wordle::Wordle(const Wordle &other): word(other.word),
                                     attempts(other.attempts),
                                     player(other.player) {
}

Wordle::Wordle(Wordle &&other) noexcept: word(std::move(other.word)),
                                         attempts(other.attempts),
                                         player(other.player) {
}

Wordle & Wordle::operator=(const Wordle &other) {
    if (this == &other)
        return *this;
    word = other.word;
    attempts = other.attempts;
    player = other.player;
    return *this;
}

Wordle & Wordle::operator=(Wordle &&other) noexcept {
    if (this == &other)
        return *this;
    word = std::move(other.word);
    attempts = other.attempts;
    player = other.player;
    return *this;
}

Wordle::~Wordle() = default;

std::ostream & operator<<(std::ostream &os, const std::pair<std::string, std::string> &p) {
    os << "Hint: "<<" "<< p.first << "\n" << p.second;
    return os;
}

std::ostream & operator<<(std::ostream &os, const Wordle &game) {
    os << "Wordle Game\n" << game.word << "\n"
            << "Attempts: " << game.attempts << "\n"
            << "Player:" << game.player << "\n";
    return os;
}

int Wordle::getRemainingAttempts() const {
    return attempts;
}
