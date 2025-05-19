#ifndef HAVERSINERESULT_H
#define HAVERSINERESULT_H

#include "Country.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

class HaversineResult : public Country {
public:

    HaversineResult(const std::string &name,
                    const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string,
                    std
                    ::vector<std::string>>> &validCountries, double latitude, double longitude,
                    const std::string &capital,
                    long population, const std::string &currency);

    void displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const override;

    ~HaversineResult() override = default;

    HaversineResult(const HaversineResult &other);

    HaversineResult(HaversineResult &&other) noexcept;

    HaversineResult & operator=(const HaversineResult &other);

    HaversineResult & operator=(HaversineResult &&other) noexcept;

private:
    std::pair<double, double> haversine(double lat1, double lon1, double lat2, double lon2) const;
    std::string bearingToCompass(double bearing) const;
};

#endif // HAVERSINERESULT_H