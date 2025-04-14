//
// Created by Andrei Luca on 14.04.2025.
//

#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "Player.h"
#include "Wordle.h"


class Game {
public:
    explicit Game(Player& player);

    Game(const Game &other);

    Game(Game &&other) noexcept;

    Game & operator=(const Game &other);

    Game & operator=(Game &&other) noexcept;

    void playWordle(const std::string& word, const std::vector<std::string>& validWords);

    // Placeholder functions for other games
    void playOption2();

    void playOption3();

    void privateChoice();

    ~Game();

private:
    Player& player;

    int getUserChoice();

    std::vector<std::string> loadWords(int wordLength);
};



#endif //GAME_H
