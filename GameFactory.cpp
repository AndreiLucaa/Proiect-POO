//
// Created by Andrei Luca on 29.06.2025.
//

#include "GameFactory.h"
#include "capitalGame.h"
#include "populationGame.h"
#include "colorFlagGame.h"
#include "currencyGame.h"
#include <cstdlib>

Globle* GameFactory::createRandomGame(
    const std::string &country,
    const std::vector<std::tuple<std::string, std::pair<double,double>, std::string, int, std::string, std::vector<std::string>>>& validCountries,
    Player &player,
    double latitude, double longitude,
    const std::string &capital, long population,
    const std::string &currency, std::vector<std::string> &flagColors)
{
    int rnd = std::rand() % 4;
    switch (rnd) {
        case 0: return new capitalGame(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors);
        case 1: return new populationGame(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors);
        case 2: return new colorFlagGame(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors);
        default:return new currencyGame(country, validCountries, player, latitude, longitude, capital, population, currency, flagColors);
    }
}
