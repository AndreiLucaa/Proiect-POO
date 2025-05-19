//
// Created by Andrei Luca on 19.05.2025.
//

#include "colorFlagGame.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <string>
#include <utility>
#include <vector>


colorFlagGame::colorFlagGame(const std::string &country,
                             const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
                             Player &player, double latitude, double longitude,
                             const std::string &capital, long population, const std::string &currency,
                             const std::vector<std::string> &flagColors)
    : Globle(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors, false) {

}

colorFlagGame::~colorFlagGame() {

}

void colorFlagGame::play() {
    std::vector<std::string> allColors = {"Red", "Blue", "Green", "Yellow", "Black", "White", "Orange", "Purple", "Brown", "Pink"};

    std::vector<std::string> flagColors = country.getFlagColors();
    std::vector<std::string> remainingColors = flagColors;
    std::transform(flagColors.begin(), flagColors.end(), remainingColors.begin(),
                   [](const std::string &color) {
                       std::string colorCopy = color;
                       std::transform(colorCopy.begin(), colorCopy.end(), colorCopy.begin(), ::tolower);
                       return colorCopy;
                   });
    int attempts_ = flagColors.size() + 3;

    std::cout << "Guess the colors of the flag for: " << country.getName() << "\n";
    std::cout << country.getName() << " has " << country.getFlagColors().size() << " colors in its flag.\n";
    std::cout << "You have " << attempts_ << " attempts to guess the colors.\n";
    std::cout << "Available colors: ";
    for (const auto &color : allColors) {
        std::cout << color << " ";
    }
    std::cout << "\n";

    while (attempts_ > 0 && !remainingColors.empty()) {
        std::cout << "You have " << attempts_ << " attempts remaining.\n";
        std::cout << "Enter a color: ";
        std::string guessedColor;
        std::cin >> guessedColor;
        std::transform(guessedColor.begin(), guessedColor.end(), guessedColor.begin(), ::tolower);

        auto it = std::find(remainingColors.begin(), remainingColors.end(), guessedColor);
        if (it != remainingColors.end()) {
            remainingColors.erase(it);
            std::cout << "Correct! You have " << remainingColors.size() << " colors remaining.\n";
        } else {
            std::cout << "Wrong guess! Try again.\n";
        }

        --attempts_;
    }

    if (remainingColors.empty()) {
        std::cout << "Congratulations! You guessed all the colors of the flag.\n";
    } else {
        std::cout << "Game over! You ran out of attempts. The correct colors were: ";
        for (const auto &color : flagColors) {
            std::cout << color << " ";
        }
        std::cout << "\n";
    }
}
