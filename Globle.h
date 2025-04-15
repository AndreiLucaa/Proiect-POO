
#ifndef GLOBLE_H
#define GLOBLE_H

#include <iostream>
#include <vector>
#include <string>

#include "Country.h"
#include "Player.h"

class Globle {
public:
    Globle(const std::string &country, const std::vector<std::string> &validCounrties, Player &player);

    void play();

private:
    Country country;
    Player &player;
    int attempts;

};


#endif //GLOBLE_H
