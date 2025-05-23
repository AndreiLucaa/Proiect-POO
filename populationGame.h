//
// Created by Andrei Luca on 14.05.2025.
//

#ifndef POPULATIONGAME_H
#define POPULATIONGAME_H

#include "Globle.h"

class populationGame : public Globle {
public:

    populationGame(const std::string &country,
                   const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string,
                   std::
                   vector<std::string>>> &validCountries, Player &player, double latitude, double longitude,
                   const std::string &capital, long population, const std::string &currency,
                   const std::vector<std::string> &flagColors);

    virtual void play() override;

    virtual ~populationGame() override;

    static std::string formatNumber(long number);
};

#endif // POPULATIONGAME_H


