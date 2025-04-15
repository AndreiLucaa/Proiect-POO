#include "Globle.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>

Globle::Globle(const std::string &country, const std::vector<std::string> &validCountries, Player &player)
    : country(country, validCountries), player(player), attempts(6) {
    // Constructor body...
}

void Globle::play() {
    // Implement the game logic here
    std::cout << "Playing Globle...\n";
}
