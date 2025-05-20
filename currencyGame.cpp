//
// Created by Andrei Luca on 20.05.2025.
//

#include "currencyGame.h"

#include <random>
#include <unordered_set>

currencyGame::currencyGame(const std::string &country,
                           const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
                           Player &player, double latitude, double longitude,
                           const std::string &capital, long population, const std::string &currency,
                           const std::vector<std::string> &flagColors)
    : Globle(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors, false) {

}

void currencyGame::play() {

    std::string correctCurrency = country.getCurrency();
    std::vector<std::string> allCurrencies;
    for (const auto &entry : country.getValidCountries()) {
        allCurrencies.push_back(std::get<4>(entry));
    }
    std::random_device rd;
    std::mt19937 gen(rd());

    std::ranges::shuffle(allCurrencies.begin(), allCurrencies.end(), gen);



    std::vector<std::string> options;
    std::unordered_set<std::string> uniqueCurrencies;
    uniqueCurrencies.insert(correctCurrency);
    options.push_back(correctCurrency);

    for (const auto &currency : allCurrencies) {
        if (options.size() == 4) break;
        if (uniqueCurrencies.find(currency) == uniqueCurrencies.end()) {
            options.push_back(currency);
            uniqueCurrencies.insert(currency);
        }
    }
    std::ranges::shuffle(options.begin(), options.end(), gen);
    std::cout << "Guess the correct currency of: " << country.getName() << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    int choice;
    std::cout << "Enter your choice (1-4): ";
    std::cin >> choice;
    if (choice >= 1 && choice <= 4 && options[choice - 1] == correctCurrency) {
        std::cout << "Correct! The currency is: " << correctCurrency << "\n";
    } else {
        std::cout << "Wrong! The correct currency was: " << correctCurrency << "\n";
    }


}

currencyGame::~currencyGame() {
    std::cout << "Destructor currencyGame\n";
}


