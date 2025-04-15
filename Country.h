//
// Created by Andrei Luca on 15.04.2025.
//

#ifndef COUNTRY_H
#define COUNTRY_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>

class Country {
public:
    Country(const std::string &name, const std::vector<std::string> &validCountries);
    void display() const;

    std::string getName() const;

private:
    std::string name;
    std::string validCountries;

};


#endif //COUNTRY_H
