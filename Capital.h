//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef CAPITAL_H
#define CAPITAL_H
#include <ostream>

#include "Country.h"


class Capital : public Country {
public:
    Capital(const std::string &name,
        const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &
        validCountries, double latitude, double longitude, const std::string &capital, long population,
        const std::string &currency);

    friend std::ostream & operator<<(std::ostream &os, const Capital &obj);

    friend bool operator==(const Capital &lhs, const Capital &rhs);

    friend bool operator!=(const Capital &lhs, const Capital &rhs);

    friend void swap(Capital &lhs, Capital &rhs) noexcept;

    Capital(const Capital &other);

    Capital(Capital &&other) noexcept;

    Capital & operator=(const Capital &other);

    Capital & operator=(Capital &&other) noexcept;
};



#endif //CAPITAL_H
