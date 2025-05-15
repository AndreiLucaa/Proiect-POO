//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef CAPITALGAME_H
#define CAPITALGAME_H
#include "Globle.h"


#include "capitalGame.h"
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
                const std::string &currency);

    virtual void play() override;

    virtual ~capitalGame() override;
};

#endif //CAPITALGAME_H