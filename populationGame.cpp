//
// Created by Andrei Luca on 14.05.2025.
//

#include "populationGame.h"

#include <random>
#include <sstream>
#include <iomanip>
populationGame::populationGame(const std::string &country,
                               const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &
                               validCountries, Player &player, double latitude, double longitude, const std::string &capital, long population,
                               const std::string &currency, const std::vector<std::string> &flagColors): Globle(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors, false
                                   ) {
}

void populationGame::play() {
    long correctPopulation = country.getPopulation();

    std::vector<std::pair<long, long>> intervals;
    intervals.emplace_back(correctPopulation - 500000, correctPopulation + 500000);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> offsetDist(100000, 1000000);

    while (intervals.size() < 4) {
        long offset = offsetDist(gen);
        long start = correctPopulation + offset * (gen() % 2 == 0 ? -1 : 1);
        long end = start + 500000;

        if (start > correctPopulation + 500000 || end < correctPopulation - 500000) {
            intervals.emplace_back(start, end);
        }
    }

    std::shuffle(intervals.begin(), intervals.end(), gen);

    std::cout << "Guess the population of: " << country.getName() << "\n";
    for (size_t i = 0; i < intervals.size(); ++i) {
        std::cout << i + 1 << ". " << formatNumber(intervals[i].first) << " - " << formatNumber(intervals[i].second) << "\n";
    }

    int choice;
    std::cout << "Enter your choice (1-4): ";
    std::cin >> choice;

    if (choice >= 1 && choice <= 4) {
        auto [start, end] = intervals[choice - 1];
        if (correctPopulation >= start && correctPopulation <= end) {
            std::cout << "Correct! The population is in the interval: " << formatNumber(start) << " - " << formatNumber(end) << "\n";
        } else {
            std::cout << "Wrong! The correct population was: " << formatNumber(correctPopulation) << "\n";
        }
    } else {
        std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
    }
}

populationGame::~populationGame() {
    std::cout << "Destructor populationGame\n";
}

std::string populationGame::formatNumber(long number) {
    std::ostringstream oss;
    if (number >= 1000000) {
        oss << std::fixed << std::setprecision(1) << (number / 1000000.0) << " mil";
    } else if (number >= 1000) {
        oss << (number / 1000) << "k";
    } else {
        oss << number;
    }
    return oss.str();
}
