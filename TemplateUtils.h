//
// Created by Andrei Luca on 29.06.2025.
//

#ifndef TEMPLATEUTILS_H
#define TEMPLATEUTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

template<typename T>
class Container {
public:
    explicit Container(const T& v) : value(v) {}
private:
    T value;
};


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

int levenshteinDistance(const std::string& s1, const std::string& s2);

template<typename Range>
std::string findClosest(const std::string& word, const Range& list) {
    auto toLower = [](const std::string& s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        return r;
    };

    std::string wlower = toLower(word);
    int best = INT_MAX;
    std::string match;
    for (const auto& cand : list) {
        std::string clower = toLower(cand);

        if (clower == wlower) return cand;
        int d = levenshteinDistance(wlower, clower);
        if (d < best) {
            best = d;
            match = cand;
        }
    }
    return match;
}

#endif // TEMPLATEUTILS_H
