//
// Created by Andrei Luca on 15.04.2025.
//

#ifndef COUNTRY_H
#define COUNTRY_H
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>
#include <cmath>
#include <utility>
#include <tuple>

constexpr double EARTH_RADIUS_KM = 6371.0;
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;

class Country {
public:


    Country(const std::string &name,
            const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::
            vector<
            std::string>>> &validCountries, double latitude, double longitude, const std::string &capital,
            long population,
            const std::string &currency, const std::vector<std::string> &flagColors);

    virtual void displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const;

    virtual ~Country() = default;

    std::string const& getName() const;

    const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &getValidCountries() const;


    double getLatitude() const;

    double getLongitude() const;

    std::string const& getCapital() const;

    long getPopulation() const;

    std::string const& getCurrency() const;

    const std::vector<std::string> &getFlagColors() const;

    bool isValidCountry(const std::string &countryName) const;

    bool isCorrectCountry(const std::string &guessCountry) const;

    std::pair<double, double> getCoordinates(const std::string &countryName) const;

    friend std::ostream &operator<<(std::ostream &os, const Country &obj) {
        os << "Country: " << obj.name
           << ", Capital: " << obj.capital
           << ", Population: " << obj.population
           << ", Currency: " << obj.currency
           << ", Coordinates: (" << obj.latitude << ", " << obj.longitude << ")";
        return os;
    }

    friend bool operator==(const Country &lhs, const Country &rhs);

    std::vector<std::string> getValidCountryNames() const;

private:
    std::string name;
    std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::
    string>>> validCountries;
    double latitude;
    double longitude;
    std::string capital;
    long population;
    std::string currency;
    std::vector<std::string> flagColors;


};

// inline definition to avoid missing symbol at link time
inline std::vector<std::string> Country::getValidCountryNames() const {
    std::vector<std::string> names;
    names.reserve(validCountries.size());
    for (const auto &entry : validCountries) {
        names.push_back(std::get<0>(entry));
    }
    return names;
}


#endif //COUNTRY_H
