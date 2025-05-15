#ifndef COUNTRYEXCEPTIONS_H
#define COUNTRYEXCEPTIONS_H

#include <exception>
#include <string>

// Base exception class for Country-related errors
class CountryException : public std::exception {
public:
    explicit CountryException(const std::string &message);

    const char *what() const noexcept override;

private:
    std::string message;
};


#endif // COUNTRYEXCEPTIONS_H