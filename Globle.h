
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
           const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries,
           Player &player, double latitude, double longitude);

    void play();

private:
    Country country;
    Player &player;
    int attempts;

};
std::ostream & operator<<(std::ostream & os, const std::pair<double, double> & rhs);


#endif //GLOBLE_H
