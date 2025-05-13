//
// Created by Andrei Luca on 13.05.2025.
//

#include "capitalGame.h"

capitalGame::capitalGame(const std::string &country,
    const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &
    validCountries, Player &player, double latitude, double longitude, const std::string &capital, long population,
    const std::string &currency): Globle(country, validCountries, player, latitude, longitude, capital, population, currency, false) {}

void capitalGame::play() {
    std::string correctCapital = country.getCapital();

    std::vector<std::string> allCapitals;
    for (const auto &entry : country.getValidCountries()) {
        allCapitals.push_back(std::get<2>(entry));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allCapitals.begin(), allCapitals.end(), gen);

    std::vector<std::string> options;
    options.push_back(correctCapital);
    for (const auto &capital : allCapitals) {
        if (options.size() == 4) break;
        if (capital != correctCapital) {
            options.push_back(capital);
        }
    }

    std::shuffle(options.begin(), options.end(), gen);

    std::cout << "Guess the correct capital of: "<< country.getName() << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }

    int choice;
    std::cout << "Enter your choice (1-4): ";
    std::cin >> choice;

    if (choice >= 1 && choice <= 4 && options[choice - 1] == correctCapital) {
        std::cout << "Correct! The capital is: " << correctCapital << "\n";
    } else {
        std::cout << "Wrong! The correct capital was: " << correctCapital << "\n";
    }
}