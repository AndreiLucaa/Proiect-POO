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
                    const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries,
                    double latitude, double longitude);

    void displayHaversineResult(double lat1, double lon1, double lat2, double lon2) const override;

private:
    std::pair<double, double> haversine(double lat1, double lon1, double lat2, double lon2) const;
    std::string bearingToCompass(double bearing) const;
};

#endif // HAVERSINERESULT_H