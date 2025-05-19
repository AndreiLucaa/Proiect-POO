
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
           const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::
           vector<
           std::string>>> &validCountries, Player &player, double latitude, double longitude,
           const std::string &capital,
           long population, const std::string &currency, const std::vector<std::string> &flagColors, bool showMessage);

    virtual void play();

    Globle(const Globle &other);

    Globle(Globle &&other) noexcept;

    Globle &operator=(Globle other);

    Globle & operator=(const Globle &other);

    Globle & operator=(Globle &&other) noexcept;

    virtual ~Globle();

protected:

    Country country;
    Player &player;
    int attempts;

};
std::ostream & operator<<(std::ostream & os, const std::pair<double, double> & rhs);


#endif //GLOBLE_H