//
// Created by Andrei Luca on 20.05.2025.
//

#ifndef CURRENCYGAME_H
#define CURRENCYGAME_H
#include "Globle.h"


class currencyGame : public Globle {

public:

    currencyGame(const std::string &country,
                 const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std
                 ::
                 vector<std::string>>> &validCountries, Player &player, double latitude, double longitude,
                 const std::string &capital, long population, const std::string &currency,
                 const std::vector<std::string> &flagColors);

    virtual void play() override;


    virtual ~currencyGame() override;
};



#endif //CURRENCYGAME_H
