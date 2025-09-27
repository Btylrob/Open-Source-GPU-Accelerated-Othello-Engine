#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <map>

class Leaderboard {
private:
    std::map<std::string, int> rank;

public:
    void addRankedPlayer(const std::string& playerName, int score);
    void displayLeaderboard() const;
    void resetLeaderboard();
    int getPlayerRank(const std::string& playerName) const;
};

#endif // LEADERBOARD_H
