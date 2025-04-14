//
// Created by Andrei Luca on 14.04.2025.
//

#include "Player.h"

Player::Player(const std::string &name): name(name), streak(0), attempts(0), totalTime(0), gamesPlayed(0), gamesWon(0) {
    std::cout << "constructor Player\n";
}

Player::Player(const Player &other): name(other.name),
                                     streak(other.streak),
                                     attempts(other.attempts),
                                     totalTime(other.totalTime),
                                     gamesPlayed(other.gamesPlayed),
                                     gamesWon(other.gamesWon) {
}

Player::Player(Player &&other) noexcept: name(std::move(other.name)),
                                         streak(other.streak),
                                         attempts(other.attempts),
                                         totalTime(other.totalTime),
                                         gamesPlayed(other.gamesPlayed),
                                         gamesWon(other.gamesWon) {
}

Player & Player::operator=(const Player &other) {
    if (this == &other)
        return *this;
    name = other.name;
    streak = other.streak;
    attempts = other.attempts;
    totalTime = other.totalTime;
    gamesPlayed = other.gamesPlayed;
    gamesWon = other.gamesWon;
    return *this;
}

Player & Player::operator=(Player &&other) noexcept {
    if (this == &other)
        return *this;
    name = std::move(other.name);
    streak = other.streak;
    attempts = other.attempts;
    totalTime = other.totalTime;
    gamesPlayed = other.gamesPlayed;
    gamesWon = other.gamesWon;
    return *this;
}

void Player::incrementStreak() { privateIncrementStreak(); }

void Player::resetStreak() { privateResetStreak(); }

void Player::addAttempt() { privateAddAttempt(); }

void Player::addTime(double time) { privateAddTime(time); }

void Player::incrementGamesPlayed() { privateIncrementGamesPlayed(); }

void Player::incrementGamesWon() { privateIncrementGamesWon(); }

const std::string & Player::getName() const { return name; }

int Player::getStreak() const { return streak; }

int Player::getAttempts() const { return attempts; }

double Player::getTotalTime() const { return totalTime; }

int Player::getGamesPlayed() const { return gamesPlayed; }

int Player::getGamesWon() const { return gamesWon; }

double Player::getWinRate() const { return gamesPlayed > 0 ? static_cast<double>(gamesWon) / gamesPlayed * 100.0 : 0.0; }

Player::~Player() {
    std::cout << "destructor Player\n";
}

void Player::privateIncrementStreak() { ++streak; }

void Player::privateResetStreak() { streak = 0; }

void Player::privateAddAttempt() { ++attempts; }

void Player::privateAddTime(double time) { totalTime += time; }

void Player::privateIncrementGamesPlayed() { ++gamesPlayed; }

void Player::privateIncrementGamesWon() { ++gamesWon; }
