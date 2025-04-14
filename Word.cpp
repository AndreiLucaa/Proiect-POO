//
// Created by Andrei Luca on 14.04.2025.
//

#include "Word.h"

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

bool Word::isValid(const std::string &guess) const { return privateIsValid(guess); }

bool Word::correctLength(const std::string &guess) const { return privateCorrectLength(guess); }

bool Word::isCorrect(const std::string &guess) const { return privateIsCorrect(guess); }

std::string Word::getHint(const std::string &guess) const { return privateGetHint(guess); }

std::string Word::verifyLetters(const std::string &guess) const { return privateVerifyLetters(guess); }

std::string Word::getLetters(const std::string &guess) { return privateGetLetters(guess); }

Word::~Word() = default;

bool Word::privateIsValid(const std::string &guess) const {
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

bool Word::privateCorrectLength(const std::string &guess) const { return guess.size() == word.size(); }

bool Word::privateIsCorrect(const std::string &guess) const { return guess == word; }

std::string Word::privateGetHint(const std::string &guess) const {
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

std::string Word::privateVerifyLetters(const std::string &guess) const {
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

std::string Word::privateGetLetters(const std::string &guess) {
    for (size_t i = 0; i < guess.size(); ++i) {
        size_t pos = litere.find(guess[i]);
        if (pos != std::string::npos) {
            litere[pos] = '-';
        }
    }
    return litere;
}
