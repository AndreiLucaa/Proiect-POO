//
// Created by Andrei Luca on 29.06.2025.
//

#ifndef TEMPLATEUTILS_H
#define TEMPLATEUTILS_H

#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Container {
public:
    explicit Container(const T& v) : value(v) {}
    T getValue() const { return value; }
private:
    T value;
};

template<typename T>
T maxValue(const T& a, const T& b) {
    return (a > b) ? a : b;
}


template<typename T>
void printVector(const std::vector<T>& vec, const std::string& name = "") {
    std::cout << name << ": ";
    for(const auto& e : vec) std::cout << e << " ";
    std::cout << std::endl;
}


template<typename T>
void compareScores(const T& current, const T& high) {
    std::cout << "Your score: " << current << ", High score: " << high << "\n";
    if (current > high) {
        std::cout << "🎉 New high score! 🎉\n";
    } else if (current == high) {
        std::cout << "🔗 You tied the high score.\n";
    } else {
        std::cout << "🏁 Try again to beat it!\n";
    }
}

#endif // TEMPLATEUTILS_H
