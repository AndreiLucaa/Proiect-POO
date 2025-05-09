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
#include "Country.h"
#include "Globle.h"
#include <json.hpp>
#include "Wordle.h"

void Game::displayMenu() const {
    std::cout << "Choose a game mode:\n";
    std::cout << "1. Wordle++\n";
    std::cout << "2. Globle++\n";
    std::cout << "3. Option 3 (coming soon...)\n";
    std::cout << "0. Exit :(\n";
}

Game::Game(Player &player): player(player) {
    std::cout << "constructor Game\n";
    std::cout << "====================================\n";
    std::cout << "       Welcome to Offline Games     \n";
    std::cout << "====================================\n";
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

void Game::playGloble(const std::string &country, const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries, double latitude, double longitude) {
    // std::cout << "Option 2 is coming soon...\n";
    Globle globleGame(country, validCountries, player, latitude, longitude);
    globleGame.play();

}

void Game::playOption3() {
    std::cout << "Option 3 is coming soon...\n";
}

void Game::privateChoice() {
    displayMenu(); // Display the menu again before taking input
    std::string choice;
    std::cout << "Enter your choice: ";
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
        std::cout << "You've chosen Globle++\n";
        std::vector<std::pair<std::string, std::pair<double, double>>> countries = loadCountries();
        if (countries.empty()) {
            std::cerr << "Failed to load countries from file." << std::endl;
            return;
        }
        int countryIndex = std::rand() % countries.size();
        std::string randomCountry = countries[countryIndex].first;
        double latitude = countries[countryIndex].second.first;
        double longitude = countries[countryIndex].second.second;
        playGloble(randomCountry, countries, latitude, longitude);
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

std::vector<std::pair<std::string, std::pair<double, double>>> Game::loadCountries() {
    std::vector<std::pair<std::string, std::pair<double, double>>> countries;
    std::ifstream file("countries.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file countries.json" << std::endl;
        return countries;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto &item : jsonData) {
        std::string country = item["country"];
        std::transform(country.begin(), country.end(), country.begin(), ::toupper);
        double latitude = item["latitude"];
        double longitude = item["longitude"];
        countries.emplace_back(country, std::make_pair(latitude, longitude));
    }

    return countries;
}
std::ostream& operator<<(std::ostream& os, const std::pair<std::string, std::pair<double, double>>& country) {
    os << "Country: " << country.first << ", Coordinates: (" << country.second.first << ", " << country.second.second << ")";
    return os;
}

std::ostream & operator<<(std::ostream &os,
    const std::vector<std::pair<std::string, std::pair<double, double>>> &countries) {
    for (const auto& country : countries) {
        os << country << "\n";
    }
    return os;
}


