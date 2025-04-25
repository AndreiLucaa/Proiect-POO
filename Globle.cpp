#include "Globle.h"
#include "Country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>
#include "HaversineResult.h"

Globle::Globle(const std::string &country, const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries, Player &player, double latitude, double longitude)
    : country(country, validCountries, latitude, longitude), player(player), attempts(6) {
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
    player.incrementGamesPlayed();
}



void Globle::play() {
    std::string guessCountry;
    auto start = std::chrono::high_resolution_clock::now();
    while (attempts > 0) {
        std::cout << "Enter your guess: ";
        std::getline(std::cin, guessCountry);

        player.addAttempt();
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

            HaversineResult haversineResult(country.getName(), country.getValidCountries(), targetLat, targetLon);
            haversineResult.displayHaversineResult(guessLat, guessLon, targetLat, targetLon);

            --attempts;
            std::cout << "Attempts remaining: " << attempts << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    player.addTime(elapsed.count());
}
