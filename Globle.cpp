#include "Globle.h"
#include "Country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>

#include "HaversineResult.h"

Globle::Globle(const std::string &country, const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries, Player &player, double latitude, double longitude)
    : country(country, validCountries, latitude, longitude), player(player), attempts(6) {
    std::cout << "====================================\n";
    std::cout << "        Welcome to Globle++!        \n";
    std::cout << "====================================\n";
    std::cout << "Test your geography skills and find the mystery country!\n";
    std::cout << "Each turn, enter the name of a valid country.\n\n";

    std::cout << "How to Play:\n";
    std::cout << "🌍 Enter a country name as your guess.\n";
    std::cout << "📏 You'll receive the distance from your guess to the target country.\n";
    std::cout << "🧭 You'll also get the general direction (N, NE, E, SE, S, SW, W, NW).\n\n";

    std::cout << "Use these clues to narrow down the correct country!\n";
    std::cout << "Can you guess the mystery country in as few tries as possible?\n";
    std::cout << "Good luck and have fun exploring the globe! 🌐\n";
}



void Globle::play() {

    HaversineResult haversineResult(
        country.getName(),
        country.getValidCountries(),
        country.getLatitude(),
        country.getLongitude()
    );

    double lat1 = 41.3275;  // Albania latitude
    double lon1 = 19.8189;  // Albania longitude
    double lat2 = 44.4268;  // Romania latitude
    double lon2 = 26.1025;  // Romania longitude

    haversineResult.displayHaversineResult(lat1, lon1, lat2, lon2);
}

std::ostream & operator<<(std::ostream &os, const std::pair<double, double> &rhs) {
    os << "Distance: " << rhs.first << ", Bearing: " << rhs.second;
    return os;
}
