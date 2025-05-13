//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef CAPITALGAME_H
#define CAPITALGAME_H
#include "Globle.h"


#include "capitalGame.h"
#include "Capital.h"
#include "Country.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class capitalGame : public Globle {
public:
    capitalGame(const std::string &country,
                const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &validCountries,
                Player &player, double latitude, double longitude, const std::string &capital, long population,
                const std::string &currency)
        : Globle(country, validCountries, player, latitude, longitude, capital, population, currency) {}

    void play() override {
        // Extract the correct capital
        std::string correctCapital = country.getCapital();

        // Collect all capitals from valid countries
        std::vector<std::string> allCapitals;
        for (const auto &entry : country.getValidCountries()) {
            allCapitals.push_back(std::get<2>(entry)); // Extract the capital
        }

        // Shuffle and pick 3 random capitals (excluding the correct one)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(allCapitals.begin(), allCapitals.end(), gen);

        std::vector<std::string> options;
        options.push_back(correctCapital);
        for (const auto &capital : allCapitals) {
            if (options.size() == 4) break; // Limit to 4 options
            if (capital != correctCapital) {
                options.push_back(capital);
            }
        }

        // Shuffle the options
        std::shuffle(options.begin(), options.end(), gen);

        // Display the options
        std::cout << "Guess the correct capital of: "<< country.getName() << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i + 1 << ". " << options[i] << "\n";
        }

        // Get the user's choice
        int choice;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        // Check if the choice is correct
        if (choice >= 1 && choice <= 4 && options[choice - 1] == correctCapital) {
            std::cout << "Correct! The capital is: " << correctCapital << "\n";
        } else {
            std::cout << "Wrong! The correct capital was: " << correctCapital << "\n";
        }
    }


};

#endif //CAPITALGAME_H
