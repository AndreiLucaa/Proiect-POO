//
// Created by Andrei Luca on 14.04.2025.
//

#ifndef WORDLE_H
#define WORDLE_H
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "Player.h"
#include "Word.h"


class Wordle {
public:
    Wordle(const std::string& word, const std::vector<std::string>& validWords, Player& player);

    void play();

    Wordle(const Wordle &other);

    Wordle(Wordle &&other) noexcept;

    Wordle & operator=(const Wordle &other);

    Wordle & operator=(Wordle &&other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Wordle& game) {
        os << "Wordle Game\n" << game.word << "\n"
        << "Attempts: " << game.attempts << "\n"
        << "Player:" << game.player << "\n";
        return os;
    }


    ~Wordle();

private:
    Word word;
    int attempts;
    Player& player;
};
std::ostream &operator<<(std::ostream &os, const std::pair<std::string, std::string> &p);


#endif //WORDLE_H
