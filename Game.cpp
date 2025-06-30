//
// Created by Andrei Luca on 14.04.2025.
//

#include "Game.h"
#include "TemplateUtils.h"
#include "Logger.h"
#include "GameFactory.h"

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


Game::Game(Player &player): player(player) {
    std::cout << "constructor Game\n";
    std::cout << "====================================\n";
    std::cout << "       Welcome to Offline Games     \n";
    std::cout << "====================================\n";
}

void Game::displayMenu() {
    Logger::getInstance().log("About to show main menu");
    std::cout << "Choose a game mode:\n";
    std::cout << "1. Wordle++\n";
    std::cout << "2. Globle++\n";
    std::cout << "3. Currency Game\n";
    std::cout << "4. Population Game\n";
    std::cout << "5. Flag Color Game\n";
    std::cout << "6. Capital Game\n";                  // added
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
    Wordle* wordleGame = new Wordle(word, validWords, player);
    wordleGame->play();
    {
        int rem = wordleGame->getRemainingAttempts();
        delete wordleGame;
        int score = (rem > 0 ? rem * 10 : -10);
        if (rem > 0) player.incrementStreak();
        else         player.resetStreak();
        player.addScore(score);
    }
}

void Game::playGloble(const std::string &country,
                      const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
                      double latitude, double longitude,
                      const std::string &capital, long population,
                      const std::string &currency, std::vector<std::string> &flagColors) {
    Globle* globleGame = new Globle(country, validCountries, player,
                                    latitude, longitude, capital,
                                    population, currency, flagColors, 1);
    globleGame->play();
    {
        int rem = globleGame->getRemainingAttempts();
        delete globleGame;
        int score = (rem > 0 ? rem * 10 : -10);
        if (rem > 0) player.incrementStreak();
        else         player.resetStreak();
        player.addScore(score);
    }

    char choice;
    std::cout << "Do you want to continue with the extra questions? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice == 'y' || choice == 'Y') {
        Globle* randomGame = GameFactory::createRandomGame(
            country, validCountries, player,
            latitude, longitude, capital, population, currency, flagColors);
        randomGame->play();
        {
            int remExtra = randomGame->getRemainingAttempts();
            delete randomGame;
            int scoreExtra = (remExtra > 0 ? remExtra * 10 : -10);
            player.addScore(scoreExtra);
        }
    }

}

void Game::privateChoice() {
    displayMenu();
    std::string choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    Logger::getInstance().log("User chose: " + choice);

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
    } else if (choice == "3") {
        std::cout << "You've chosen Currency Game\n";
        auto countries = loadCountries();
        if (countries.empty()) return;
        int idx = std::rand() % countries.size();
        auto& t = countries[idx];
        std::string name = std::get<0>(t);
        double lat = std::get<1>(t).first, lon = std::get<1>(t).second;
        std::string cap = std::get<2>(t);
        int pop = std::get<3>(t);
        std::string curr = std::get<4>(t);
        std::vector<std::string> colors = std::get<5>(t);

        currencyGame* cg = new currencyGame(name, countries, player, lat, lon, cap, pop, curr, colors);
        cg->play();
        int rem = cg->getRemainingAttempts();
        delete cg;
        int score = (rem > 0 ? rem * 10 : -10);
        player.addScore(score);
    } else if (choice == "4") {
        std::cout << "You've chosen Population Game\n";
        auto countries = loadCountries();
        if (countries.empty()) return;
        int idx = std::rand() % countries.size();
        auto& t = countries[idx];
        std::string name = std::get<0>(t);
        double lat = std::get<1>(t).first, lon = std::get<1>(t).second;
        std::string cap = std::get<2>(t);
        int pop = std::get<3>(t);
        std::string curr = std::get<4>(t);
        std::vector<std::string> colors = std::get<5>(t);

        populationGame* pg = new populationGame(name, countries, player, lat, lon, cap, pop, curr, colors);
        pg->play();
        int rem = pg->getRemainingAttempts();
        delete pg;
        int score = (rem > 0 ? rem * 10 : -10);
        player.addScore(score);
    } else if (choice == "5") {
        std::cout << "You've chosen Flag Color Game\n";
        auto countries = loadCountries();
        if (countries.empty()) return;
        int idx = std::rand() % countries.size();
        auto& t = countries[idx];
        std::string name = std::get<0>(t);
        double lat = std::get<1>(t).first, lon = std::get<1>(t).second;
        std::string cap = std::get<2>(t);
        int pop = std::get<3>(t);
        std::string curr = std::get<4>(t);
        std::vector<std::string> colors = std::get<5>(t);

        colorFlagGame* fg = new colorFlagGame(name, countries, player, lat, lon, cap, pop, curr, colors);
        fg->play();
        int rem = fg->getRemainingAttempts();
        delete fg;
        int score = (rem > 0 ? rem * 10 : -10);
        player.addScore(score);
    } else if (choice == "6") {                           // added
        std::cout << "You've chosen Capital Game\n";
        auto countries = loadCountries();
        if (countries.empty()) return;
        int idx = std::rand() % countries.size();
        auto& t = countries[idx];
        std::string name       = std::get<0>(t);
        double lat             = std::get<1>(t).first;
        double lon             = std::get<1>(t).second;
        std::string cap        = std::get<2>(t);
        int pop                = std::get<3>(t);
        std::string curr       = std::get<4>(t);
        std::vector<std::string> colors = std::get<5>(t);

        capitalGame* cg = new capitalGame(name, countries, player, lat, lon, cap, pop, curr, colors);
        cg->play();
        int rem = cg->getRemainingAttempts();
        delete cg;
        int score = (rem > 0 ? rem * 10 : -10);
        player.addScore(score);
    } else if (choice == "0") {
        std::cout << "Goodbye!\n";
    } else {
        std::cout << "Invalid choice! Please enter a valid choice.\n";
    }
}

Game::~Game() {
    int finalScore = player.getScore();
    int high;
    std::ifstream in("highscore.in");
    if (in >> high) in.close();

    std::ofstream out("highscore.in", std::ios::trunc);
    out << std::max(finalScore, high);
    out.close();

    compareScores(finalScore, high);

    std::cout << "Thank you for playing!\n";
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