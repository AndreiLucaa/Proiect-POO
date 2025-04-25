#include "HaversineResult.h"

HaversineResult::HaversineResult(const std::string &name,
                                 const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries,
                                 double latitude, double longitude)
    : Country(name, validCountries, latitude, longitude) {}

void HaversineResult::displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const {
    auto [distance, bearing] = haversine(lat1, lon1, lat2, lon2);
    std::cout << "Haversine Distance: " << std::ceil(distance) << " km\n";
    std::cout << "Bearing: " << bearingToCompass(bearing) << "\n";
}

std::pair<double, double> HaversineResult::haversine(double lat1, double lon1, double lat2, double lon2) const {
    constexpr double DEG_TO_RAD = M_PI / 180.0;
    constexpr double EARTH_RADIUS_KM = 6371.0;

    lat1 *= DEG_TO_RAD;
    lon1 *= DEG_TO_RAD;
    lat2 *= DEG_TO_RAD;
    lon2 *= DEG_TO_RAD;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::pow(std::sin(dlat / 2), 2) +
               std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::asin(std::sqrt(a));
    double distance = EARTH_RADIUS_KM * c;

    double y = std::sin(dlon) * std::cos(lat2);
    double x = std::cos(lat1) * std::sin(lat2) -
               std::sin(lat1) * std::cos(lat2) * std::cos(dlon);
    double bearing = std::atan2(y, x) * (180.0 / M_PI);

    return {distance, std::fmod((bearing + 360.0), 360.0)};
}

std::string HaversineResult::bearingToCompass(double bearing) const {
    const std::string directions[] = {
        "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
        "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"
    };
    int index = static_cast<int>((bearing + 11.25) / 22.5) % 16;
    return directions[index];
}