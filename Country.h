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

constexpr double EARTH_RADIUS_KM = 6371.0;
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;

class Country {
public:
    Country(const std::string &name, const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &validCountries, double latitude, double longitude, const std::string &capital, long population, const std::string &currency);
    // [[nodiscard]] std::string getName() const;

    // static std::pair<double, double> haversine(double lat1, double lon1, double lat2, double lon2);

    virtual void displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const;

    virtual ~Country() = default;

    std::string const& getName() const;

    std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> getValidCountries() const;

    double getLatitude() const;

    double getLongitude() const;

    std::string getCapital() const;

    long getPopulation() const;

    std::string getCurrency() const;

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

    friend bool operator==(const Country &lhs, const Country &rhs) {
        return lhs.name == rhs.name &&
               lhs.latitude == rhs.latitude &&
               lhs.longitude == rhs.longitude &&
               lhs.capital == rhs.capital &&
               lhs.population == rhs.population &&
               lhs.currency == rhs.currency;
    }

private:
    std::string name;
    std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> validCountries;
    double latitude;
    double longitude;
    std::string capital;
    long population;
    std::string currency;


};


#endif //COUNTRY_H
