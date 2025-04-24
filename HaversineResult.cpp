//
// Created by Andrei Luca on 24.04.2025.
//

#include "HaversineResult.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <string>
#include <vector>


HaversineResult::HaversineResult(const std::string &name,
                                 const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries,
                                 double latitude, double longitude)
    : Country(name, validCountries, latitude, longitude) {}



void HaversineResult::displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const {
    std::pair<double, double> result_ = haversine(lat1, lon1, lat2, lon2);
    std::cout << "Haversine Distance: " << ceil(result_.first) << " km\n";
    std::cout << "Bearing: " << bearingToCompass(result_.second) << "\n";
}

std::pair<double, double> HaversineResult::haversine(double lat1, double lon1, double lat2, double lon2) const {
    // Convert degrees to radians
    lat1 *= DEG_TO_RAD;
    lon1 *= DEG_TO_RAD;
    lat2 *= DEG_TO_RAD;
    lon2 *= DEG_TO_RAD;

    // Haversine distance formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::pow(std::sin(dlat / 2), 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::pow(std::sin(dlon / 2), 2);

    double c = 2 * std::asin(std::sqrt(a));
    double distance = EARTH_RADIUS_KM * c;

    // Bearing formula (initial heading)
    double y = std::sin(dlon) * std::cos(lat2);
    double x = std::cos(lat1) * std::sin(lat2) -
               std::sin(lat1) * std::cos(lat2) * std::cos(dlon);
    double bearing = std::atan2(y, x) * RAD_TO_DEG;

    // Normalize bearing to 0-360
    bearing = std::fmod((bearing + 360.0), 360.0);

    return {distance, bearing};
}

std::string HaversineResult::bearingToCompass(double bearing) const {
    // Normalize the bearing to 0-360 degrees
    bearing = std::fmod((bearing + 360.0), 360.0);

    // Define compass directions
    const std::string directions[] = {
        "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
        "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"
    };

    // Calculate the index for the compass direction
    int index = static_cast<int>((bearing + 11.25) / 22.5) % 16;

    return directions[index];
}
