//
// Created by Andrei Luca on 14.04.2025.
//

#include "Game.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>

Game::Game(Player &player): player(player) {
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

Game::Game(const Game &other): player(other.player) {
}

Game::Game(Game &&other) noexcept: player(other.player) {
}

Game & Game::operator=(const Game &other) {
    if (this == &other)
        return *this;
    player = other.player;
    return *this;
}

Game & Game::operator=(Game &&other) noexcept {
    if (this == &other)
        return *this;
    player = other.player;
    return *this;
}

void Game::playWordle(const std::string &word, const std::vector<std::string> &validWords) {
    Wordle wordleGame(word, validWords, player);
    wordleGame.play();
}

void Game::playOption2() {
    std::cout << "Option 2 is coming soon...\n";
}

void Game::playOption3() {
    std::cout << "Option 3 is coming soon...\n";
}

void Game::privateChoice() {
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

Game::~Game() {
    std::cout<<"Thank you for playing!\n";
}

int Game::getUserChoice() {
    int choice;
    std::cout << "🧠 Word Challenge Time!\n";
    std::cout << "Pick your difficulty\n";
    std::cout<<"🔹 4-letter words – Easy start\n";
    std::cout<<"🔸 5-letter words – Classic mode\n";
    std::cout << "🔺 6-letter words – For the pros!\n";
    std::cout << "Enter the word length you want to play with: ";
    std::cin >> choice;
    while (choice < 4 || choice > 6) {
        std::cout << "🚫 Oops! That’s not a valid option.\n";
        std::cout<<"You can only choose 4, 5, or 6 letter words. Try again!\n";
        std::cin >> choice;
    }
    return choice;
}

std::vector<std::string> Game::loadWords(int wordLength) {
    std::vector<std::string> words;
    std::string filename = "words" + std::to_string(wordLength) + ".txt";
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
