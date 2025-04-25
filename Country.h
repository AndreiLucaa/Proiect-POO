//
// Created by Andrei Luca on 15.04.2025.
//

#ifndef COUNTRY_H
#define COUNTRY_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>
#include <cmath>
#include <utility>
constexpr double EARTH_RADIUS_KM = 6371.0;
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;

class Country {
public:
    Country(const std::string &name, const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries, double latitude, double longitude);

    // [[nodiscard]] std::string getName() const;

    // static std::pair<double, double> haversine(double lat1, double lon1, double lat2, double lon2);

    virtual void displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const;

    virtual ~Country() = default;

    std::string getName() const;

    std::vector<std::pair<std::string, std::pair<double, double>>> getValidCountries() const;

    double getLatitude() const;

    double getLongitude() const;

    bool isValidCountry(const std::string &countryName) const;

    bool isCorrectCountry(const std::string &guessCountry) const;

    std::pair<double, double> getCoordinates(const std::string &countryName) const;

private:
    std::string name;
    std::vector<std::pair<std::string, std::pair<double, double>>> validCountries;
    double latitude;
    double longitude;


};


#endif //COUNTRY_H
