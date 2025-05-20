//
// Created by Andrei Luca on 14.04.2025.
//

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <string>
#include "Globle.h"
#include "Player.h"
#include <memory>
#include "capitalGame.h"
#include "populationGame.h"
#include "colorFlagGame.h"
#include "currencyGame.h"

class Game {
public:


    Globle* generateGame(const std::string &country,
                           const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::string>>> & validCountries,
                           Player &gamePlayer, double latitude, double longitude, const std::string &capital, long population,
                           const std::string &currency, std::vector<std::string> &flagColors);




    static void displayMenu();

    explicit Game(Player& player);

    Game(const Game &other);

    Game(Game &&other) noexcept;

    Game & operator=(const Game &other);

    Game & operator=(Game &&other) noexcept;

    void playWordle(const std::string& word, const std::vector<std::string>& validWords);

    void playGloble(const std::string &country,
                    const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std
                    ::vector<std::string>>> &validCountries, double latitude, double longitude,
                    const std::string &capital,
                    long population, const std::string &currency, std::vector<std::string> &flagColors);


    void privateChoice();

    ~Game();

private:
    Player& player;

    int getUserChoice();

    std::vector<std::string> loadWords(int wordLength);

    std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string, std::vector<std::
    string>>> loadCountries();
};

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, std::pair<double, double>>& country);

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<std::string, std::pair<double, double>>>& countries);
#endif //GAME_H