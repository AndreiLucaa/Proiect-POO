#include "HaversineResult.h"

HaversineResult::HaversineResult(const std::string &name,
                                 const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> &validCountries,
                                 double latitude, double longitude,
                                 const std::string &capital, long population, const std::string &currency, const std::vector<std::string> &flagColors)
    : Country(name, validCountries, latitude, longitude, capital, population, currency, flagColors) {}

void HaversineResult::displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const {
    auto [distance, bearing] = haversine(lat1, lon1, lat2, lon2);
    std::cout << "Haversine Distance: " << std::ceil(distance) << " km\n";
    std::cout << "Bearing: " << bearingToCompass(bearing) << "\n";
}

HaversineResult::HaversineResult(const HaversineResult &other): Country(other) {
}

HaversineResult::HaversineResult(HaversineResult &&other) noexcept: Country(std::move(other)) {
}

HaversineResult & HaversineResult::operator=(const HaversineResult &other) {
    if (this == &other)
        return *this;
    Country::operator =(other);
    return *this;
}

HaversineResult & HaversineResult::operator=(HaversineResult &&other) noexcept {
    if (this == &other)
        return *this;
    Country::operator =(std::move(other));
    return *this;
}

std::pair<double, double> HaversineResult::haversine(double lat1, double lon1, double lat2, double lon2) const {
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
    double bearing = std::atan2(y, x) * RAD_TO_DEG;

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