package com.example.gameserver.leaderboard;

public interface LeaderboardList {
    Long getPosition();
    String getNick();
    Long getRanking();
    Long getTotal();
    Long getWins();
    Long getDraws();
}
