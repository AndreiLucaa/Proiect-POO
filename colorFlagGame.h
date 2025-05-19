//
// Created by Andrei Luca on 19.05.2025.
//

#ifndef COLORFLAGGAME_H
#define COLORFLAGGAME_H
#include "Globle.h"


class colorFlagGame : public Globle {

public:
    colorFlagGame(const std::string &country,
                  const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
                  Player &player, double latitude, double longitude,
                  const std::string &capital, long population, const std::string &currency,
                  const std::vector<std::string> &flagColors);

    virtual void play() override;

    virtual ~colorFlagGame() override;

};



#endif //COLORFLAGGAME_H
