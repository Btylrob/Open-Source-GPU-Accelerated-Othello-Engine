#include "leaderboard.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>


void Leaderboard::resetLeaderboard() {
    rank.clear();
}

void Leaderboard::addRankedPlayer(const std::string& playerName, int score) {
    if (rank.find(playerName) == rank.end()) {
        if (score > rank[playerName]) {
            rank[playerName] = score;
        }
    } else {
        rank[playerName] = score;
    }
}

void Leaderboard::displayLeaderboard() const {
    std::vector<std::pair<std::string, int>> sortedPlayer(rank.begin(), rank.end());

    std::sort(sortedPlayer.begin(), sortedPlayer.end(),
        [](const auto& a, const auto& b) {;
            return a.second > b.second;
    });

    std::cout << std::left << std::setw(15) << "Player" << " " << "Score\n";
    std::cout << "------------------------------------------------------------";
}

int Leaderboard::getPlayerRank(const std::string& playerName) const {
    std::vector<std::pair<std::string, int>> sortedPlayers(rank.begin(), rank.end());

    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    for (int i = 0; i < sortedPlayers.size(); ++i) {
        if (sortedPlayers[i].first == playerName) {
            return i + 1;  // 1-based rank
        }
    }
    return -1;  // Player not found
}





