//
// Created by Andrei Luca on 24.04.2025.
//

#ifndef HAVERSINERESULT_H
#define HAVERSINERESULT_H

#include "Country.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>


class HaversineResult : public Country {
public:
    HaversineResult(const std::string &name,
                    const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries,
                    double latitude, double longitude);

    void displayHaversineResult(double lat1, double lon1, double lat2, double lon2);

    std::pair<double, double> haversine(double lat1, double lon1, double lat2, double lon2);

    std::string bearingToCompass(double bearing);

private:
    std::pair<double, double> result;
};

#endif // HAVERSINERESULT_H