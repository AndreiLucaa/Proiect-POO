
#ifndef GLOBLE_H
#define GLOBLE_H

#include <iostream>
#include <vector>
#include <string>

#include "Country.h"
#include "Player.h"

class Globle {

public:

    Globle(const std::string &country,
           const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &validCountries,
           Player &player, double latitude, double longitude, const std::string &capital, long population,
           const std::string &currency, bool showMessage = true);

    virtual void play();

protected:

    Country country;
    Player &player;
    int attempts;

};
std::ostream & operator<<(std::ostream & os, const std::pair<double, double> & rhs);


#endif //GLOBLE_H