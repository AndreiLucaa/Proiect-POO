#include "Globle.h"
#include "Country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <string>
#include <thread>

#include "capitalGame.h"
#include "HaversineResult.h"

Globle::Globle(const std::string &country,
               const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
               Player &player, double latitude, double longitude, const std::string &capital, long population,
               const std::string &currency, const std::vector<std::string> &flagColors, bool showMessage)
    : country(country, validCountries, latitude, longitude, capital, population, currency, flagColors),
      player(player),
      attempts(6) {
    if (showMessage) {
        std::cout << "====================================\n";
        std::cout << "        Welcome to Globle++!        \n";
        std::cout << "====================================\n";
        std::cout << "Test your geography skills and find the mystery country!\n";
        std::cout << "Each turn, enter the name of a valid country.\n\n";

        std::cout << "How to Play:\n";
        std::cout << "🌍 Enter a country name as your guess.\n";
        std::cout << "📏 You'll receive the distance from your guess to the target country.\n";
        std::cout << "🧭 You'll also get the general direction (N, NE, E, SE, S, SW, W, NW).\n\n";

        std::cout << "Use these clues to narrow down the correct country!\n";
        std::cout << "Can you guess the mystery country in as few tries as possible?\n";
        std::cout << "Good luck and have fun exploring the globe! 🌐\n";
    }
    player.incrementGamesPlayed();
}


void Globle::play() {
    std::string guessCountry;
    auto start = std::chrono::high_resolution_clock::now();    while (attempts > 0) {
        std::cout << "Enter your guess: ";
        std::getline(std::cin, guessCountry);

        if (!country.isValidCountry(guessCountry)) {
            std::cout << "Oops! That country doesn’t exist. Give it another shot!" << std::endl;
            continue;
        }

        if (country.isCorrectCountry(guessCountry)) {
            std::cout << "Congratulations! You've guessed the country: " << country.getName() << std::endl;
            player.incrementStreak();
            player.incrementGamesWon();
            std::cout << player << std::endl;
            break;
        }
        else {
            auto [guessLat, guessLon] = country.getCoordinates(guessCountry);
            double targetLat = country.getLatitude();
            double targetLon = country.getLongitude();
            // std::cout << "Your guess: " << guessCountry << " (Lat: " << guessLat << ", Lon: " << guessLon << ")" << std::endl;
            // std::cout << "Target country: " << country.getName() << " (Lat: " << targetLat << ", Lon: " << targetLon << ")" << std::endl;

            HaversineResult* haversineResult = new HaversineResult(country.getName(), country.getValidCountries(), targetLat, targetLon, country.getCapital(), country.getPopulation(), country.getCurrency(), country.getFlagColors());
            haversineResult->displayHaversineResult(guessLat, guessLon, targetLat, targetLon);
            delete haversineResult;
            player.addAttempt();
            --attempts;
            std::cout << "Attempts remaining: " << attempts << std::endl;
        }
        if (attempts == 0) {
            std::cout << "Sorry! You've run out of attempts. The correct country was: " << country.getName() << std::endl;
            player.resetStreak();
            std::cout << player << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    player.addTime(elapsed);

}

Globle::Globle(const Globle &other): country(other.country),
                                     player(other.player),
                                     attempts(other.attempts) {
}

Globle::Globle(Globle &&other) noexcept: country(std::move(other.country)),
                                         player(other.player),
                                         attempts(other.attempts) {
}


Globle& Globle::operator=(Globle other) {
    std::swap(country, other.country);
    std::swap(player, other.player);
    std::swap(attempts, other.attempts);
    return *this;
}

Globle & Globle::operator=(const Globle &other) {
    if (this == &other)
        return *this;
    country = other.country;
    player = other.player;
    attempts = other.attempts;
    return *this;
}

Globle & Globle::operator=(Globle &&other) noexcept {
    if (this == &other)
        return *this;
    country = std::move(other.country);
    player = other.player;
    attempts = other.attempts;
    return *this;
}

Globle::~Globle() {
    std::cout << "Globle game ended. Do you want to keep playing?" << std::endl;
}
