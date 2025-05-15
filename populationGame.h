//
// Created by Andrei Luca on 14.05.2025.
//

#ifndef POPULATIONGAME_H
#define POPULATIONGAME_H

#include "Globle.h"

class populationGame : public Globle {
public:
    populationGame(const std::string &country,
        const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &validCountries,
        Player &player, double latitude, double longitude, const std::string &capital, long population,
        const std::string &currency);

    virtual void play() override;

    virtual ~populationGame();

    static std::string formatNumber(long number);
};

#endif // POPULATIONGAME_H


