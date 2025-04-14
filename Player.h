#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>


class Player {
public:
    explicit Player(const std::string& name);

    Player(const Player &other);

    Player(Player &&other) noexcept;

    Player & operator=(const Player &other);

    Player & operator=(Player &&other) noexcept;

    void incrementStreak();

    void resetStreak();

    void addAttempt();

    void addTime(double time);

    void incrementGamesPlayed();

    void incrementGamesWon();

    const std::string& getName() const;

    int getStreak() const;

    int getAttempts() const;

    double getTotalTime() const;

    int getGamesPlayed() const;

    int getGamesWon() const;

    double getWinRate() const;

    ~Player();

private:
    std::string name;
    int streak;
    int attempts;
    double totalTime;
    int gamesPlayed;
    int gamesWon;

    void privateIncrementStreak();

    void privateResetStreak();

    void privateAddAttempt();

    void privateAddTime(double time);

    void privateIncrementGamesPlayed();

    void privateIncrementGamesWon();

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player: " << player.getName() << "\n"
           << "Streak: " << player.getStreak() << "\n"
           << "Attempts: " << player.getAttempts() << "\n"
           << "Total Time: " << player.getTotalTime() << " seconds\n"
           << "Games Played: " << player.getGamesPlayed() << "\n"
           << "Games Won: " << player.getGamesWon() << "\n"
           << "Win Rate: " << player.getWinRate() << "%\n";
        return os;
    }
};



#endif //PLAYER_H
