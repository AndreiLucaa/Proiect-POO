//
// Created by Andrei Luca on 13.05.2025.
//

#include "Capital.h"

Capital::Capital(const std::string &name,
    const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &
    validCountries, double latitude, double longitude, const std::string &capital, long population,
    const std::string &currency): Country(name, validCountries, latitude, longitude, capital, population, currency) {
}

Capital::Capital(const Capital &other): Country(other) {
}

Capital::Capital(Capital &&other) noexcept: Country(std::move(other)) {
}

Capital & Capital::operator=(const Capital &other) {
    if (this == &other)
        return *this;
    Country::operator =(other);
    return *this;
}

Capital & Capital::operator=(Capital &&other) noexcept {
    if (this == &other)
        return *this;
    Country::operator =(std::move(other));
    return *this;
}

std::ostream & operator<<(std::ostream &os, const Capital &obj) {
    return os << static_cast<const Country &>(obj);
}

bool operator==(const Capital &lhs, const Capital &rhs) {
    return static_cast<const Country &>(lhs) == static_cast<const Country &>(rhs);
}

bool operator!=(const Capital &lhs, const Capital &rhs) {
    return !(lhs == rhs);
}

void swap(Capital &lhs, Capital &rhs) noexcept {
    using std::swap;
    swap(static_cast<Country &>(lhs), static_cast<Country &>(rhs));
}
