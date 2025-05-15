//
// Created by Andrei Luca on 14.04.2025.
//

#include "Word.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>

#include "InvalidCharacterException.h"
#include "InvalidGuessException.h"
#include "InvalidWordLengthException.h"
#include "InvalidWordList.h"
#include "WordExceptions.h"

Word::Word(const std::string &word, const std::vector<std::string> &validWords): word(word), validWords(validWords), litere("ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
    std::cout << "constructor Word\n";
}

Word::Word(const Word &other): word(other.word),
                               validWords(other.validWords),
                               litere(other.litere) {
}

Word::Word(Word &&other) noexcept: word(std::move(other.word)),
                                   validWords(std::move(other.validWords)),
                                   litere(std::move(other.litere)) {
}

Word & Word::operator=(const Word &other) {
    if (this == &other)
        return *this;
    word = other.word;
    validWords = other.validWords;
    litere = other.litere;
    return *this;
}

Word & Word::operator=(Word &&other) noexcept {
    if (this == &other)
        return *this;
    word = std::move(other.word);
    validWords = std::move(other.validWords);
    litere = std::move(other.litere);
    return *this;
}

const std::string & Word::getWord() const { return word; }

bool Word::isValid(const std::string &guess) { return privateIsValid(guess); }

bool Word::correctLength(const std::string &guess) const { return privateCorrectLength(guess); }

bool Word::isValidWordList(const std::string &guess) { return privateIsValidWordList(guess); }

bool Word::isCorrect(const std::string &guess) const { return privateIsCorrect(guess); }

// std::string Word::getHint(const std::string &guess) const { return privateGetHint(guess); }

std::pair<std::string, std::string> Word::verifyLetters(const std::string &guess) const { return privateVerifyLetters(guess); }

std::string Word::getLetters(const std::string &guess) { return privateGetLetters(guess); }

Word::~Word() = default;

bool Word::privateIsValid(const std::string &guess) {

    for (char c : guess) {
        if (!std::isalpha(c)) {
            throw InvalidCharacterException("The word '" + guess + "' contains non-alphabetic characters.");
        }
    }

    return true;
}

bool Word::privateIsValidWordList(const std::string &guess) {
    if (std::find(validWords.begin(), validWords.end(), guess) == validWords.end()) {
        throw InvalidWordList("The word '" + guess + "' is not in the valid words list.");
    }
    return true;
}

bool Word::privateCorrectLength(const std::string &guess) const {
    if (guess.size() != word.size()) {
        throw InvalidWordLengthException("Expected length " + std::to_string(word.size()) +
                                         ", but got " + std::to_string(guess.size()) + ".");
    }
    return true;
}
bool Word::privateIsCorrect(const std::string &guess) const { return guess == word; }

// std::string Word::privateGetHint(const std::string &guess) const {
//     std::string hint;
//     for (size_t i = 0; i < word.size(); ++i) {
//         if (i < guess.size() && guess[i] == word[i]) {
//             hint += guess[i];
//         } else if (i < guess.size() && word.find(guess[i]) != std::string::npos) {
//             hint += '+';
//         } else {
//             hint += '_';
//         }
//     }
//     return hint;
// }
//
std::pair<std::string, std::string> Word::privateVerifyLetters(const std::string &guess) const {
    std::string hint;
    std::string result;
    for (size_t i = 0; i < word.size(); ++i) {
        if (i < guess.size() && guess[i] == word[i]) {
            hint += guess[i];
            result += "The letter " + std::string(1, guess[i]) + " is on the right position\n";
        } else if (i < guess.size() && word.find(guess[i]) != std::string::npos) {
            hint += "+";
            result += "The letter " + std::string(1, guess[i]) + " is in the word but not on the right position\n";
        } else if (i < guess.size()) {
            hint += "-";
            result += "The letter " + std::string(1, guess[i]) + " is not in the word\n";
        }
    }
    return {hint, result};
}



std::string Word::privateGetLetters(const std::string &guess) {
    for (size_t i = 0; i < guess.size(); ++i) {
        size_t pos = litere.find(guess[i]);
        if (pos != std::string::npos) {
            litere[pos] = '-';
        }
    }
    return litere;
}
