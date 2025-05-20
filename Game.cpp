//
// Created by Andrei Luca on 14.04.2025.
//

#include "Game.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iosfwd>
#include <string>
#include <thread>
#include "Country.h"
#include "Globle.h"
#include <json.hpp>
#include <tuple>
#include "capitalGame.h"
#include "FileReadException.h"
#include "populationGame.h"
#include "Wordle.h"
#include "Player.h"
#include "colorFlagGame.h"
#include "currencyGame.h"


Globle* Game::generateGame(const std::string &country,
                           const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> & validCountries,
                           Player &gamePlayer, double latitude, double longitude, const std::string &capital, long population,
                           const std::string &currency, std::vector<std::string> &flagColors) {
    int randomGame = std::rand() % 4;
    switch (randomGame) {
        case 0:
            return new capitalGame(country, validCountries, gamePlayer, latitude, longitude, capital, population, currency, flagColors);
        case 1:
            return new populationGame(country, validCountries, gamePlayer, latitude, longitude, capital, population, currency, flagColors);
        case 2:
            return new colorFlagGame(country, validCountries, gamePlayer, latitude, longitude, capital, population, currency, flagColors);
        case 3:
        default:
            return new currencyGame(country, validCountries, gamePlayer, latitude, longitude, capital, population, currency, flagColors);
    }
}

void Game::displayMenu() {
    std::cout << "Choose a game mode:\n";
    std::cout << "1. Wordle++\n";
    std::cout << "2. Globle++\n";
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
    Wordle* wordleGame = new Wordle(word, validWords, player);
    wordleGame->play();
    delete wordleGame;
}

void Game::playGloble(const std::string &country,
                      const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std
                      ::vector<std::string>>> &validCountries,
                      double latitude, double longitude,
                      const std::string &capital, long population,
                      const std::string &currency, std::vector<std::string> &flagColors) {
    Globle* globleGame = new Globle(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors, 1);
    globleGame->play();
    delete globleGame;

    char choice;
    std::cout << "Do you want to continue with the extra questions? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice == 'y' || choice == 'Y') {
        Globle* randomGame = generateGame(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors);

        if (auto* capGame = dynamic_cast<capitalGame*>(randomGame)) {
            std::cout << "Random game: Capital Game\n";
            capGame->play();
        } else if (auto* popGame = dynamic_cast<populationGame*>(randomGame)) {
            std::cout << "Random game: Population Game\n";
            popGame->play();
        } else if (auto* colGame = dynamic_cast<colorFlagGame*>(randomGame)) {
            std::cout << "Random game: Color Flag Game\n";
            colGame->play();
        } else if (auto* curGame = dynamic_cast<currencyGame*>(randomGame)) {
            std::cout << "Random game: Currency Game\n";
            curGame->play();
        }
        delete randomGame;
    }

}

void Game::privateChoice() {
    displayMenu();
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
        std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> countries = loadCountries();
        if (countries.empty()) {
            std::cerr << "Failed to load countries from file." << std::endl;
            return;
        }
        // std::cout << "Countries loaded successfully!\n";
        // std::cout << "Total countries loaded: " << countries.size() << "\n";
        // for (const auto &country : countries) {
        //     std::string name = std::get<0>(country);
        //     double latitude = std::get<1>(country).first;
        //     double longitude = std::get<1>(country).second;
        //     std::string capital = std::get<2>(country);
        //     int population = std::get<3>(country);
        //     std::string currency = std::get<4>(country);
        //
        //     std::cout << "Name:" << name
        //               << ", Coordinates:(" << latitude << ", " << longitude << ")"
        //               << ", Capital:" << capital
        //               << ", Population:" << population
        //               << ", Currency:" << currency << "\n";
        // }
        int countryIndex = std::rand() % countries.size();
        std::string randomCountry = std::get<0>(countries[countryIndex]);
        double latitude = std::get<1>(countries[countryIndex]).first;
        double longitude = std::get<1>(countries[countryIndex]).second;
        std::string capital = std::get<2>(countries[countryIndex]);
        int population = std::get<3>(countries[countryIndex]);
        std::string currency = std::get<4>(countries[countryIndex]);
        std::vector<std::string> flagColors = std::get<5>(countries[countryIndex]);
        // std::cout << "Random country selected: " << randomCountry << "\n";
        // std::cout << "Coordinates: (" << latitude << ", " << longitude << ")\n";
        // std::cout << "Capital: " << capital << "\n";
        // std::cout << "Population: " << population << "\n";
        // std::cout << "Currency: " << currency << "\n";
        playGloble(randomCountry, countries, latitude, longitude, capital, population, currency, flagColors);
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
    while (std::cin.fail() || choice < 4 || choice > 6) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "🚫 Oops! That’s not a valid option.\n";
        std::cout << "You can only choose 4, 5, or 6 letter words. Try again!\n";
        std::cin >> choice;
    }
    return choice;
}

std::vector<std::string> Game::loadWords(int wordLength) {
    std::vector<std::string> words;
    std::string filename = "words" + std::to_string(wordLength) + ".txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileReadException(filename);
    }
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        words.push_back(word);
    }
    return words;
}

std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>>
Game::loadCountries() {
    std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> countries;
    std::ifstream file("countries.json");
    if (!file.is_open()) {
        throw FileReadException("countries.json");
    }

    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto &item : jsonData) {
        std::string country = item["country"];
        std::transform(country.begin(), country.end(), country.begin(), ::toupper);
        double latitude = item["latitude"];
        double longitude = item["longitude"];
        std::string capital = item["capital"];
        int population = item["population"];
        std::string currency = item["currency"];
        std::vector<std::string> flagColors = item["flagColors"].get<std::vector<std::string>>();
        countries.emplace_back(country, std::make_pair(latitude, longitude), capital, population, currency, flagColors);
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