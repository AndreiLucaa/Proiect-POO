//
// Created by Andrei Luca on 15.04.2025.
//

#include "Country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>

Country::Country(const std::string &name, const std::vector<std::string> &validCountries) {
    // Initialize members here...
    std::cout<<"constructor Country\n";
}

void Country::display() const {
    std::cout << "Country: " << name<<"\n";
}

std::string Country::getName() const {
    return name;
}
