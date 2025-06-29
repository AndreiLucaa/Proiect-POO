//
// Created by Andrei Luca on 29.06.2025.
//

#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "Globle.h"
#include "Player.h"
#include <string>
#include <vector>
#include <tuple>

class GameFactory {
public:
    static Globle* createRandomGame(
        const std::string& country,
        const std::vector<std::tuple<std::string, std::pair<double,double>, std::string, int, std::string, std::vector<std::string>>>& validCountries,
        Player& player,
        double latitude, double longitude,
        const std::string& capital, long population,
        const std::string& currency,
        std::vector<std::string>& flagColors);
};

#endif // GAMEFACTORY_H
