package com.example.gameserver.leaderboard;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Embeddable
public class LeaderboardId implements Serializable {
    @Column(name="NICK")
    private String nick;
    @Column(name="GAME_ID")
    private Long gameId;
    @Column(name="RANKING_ID")
    private Long rankingId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LeaderboardId that = (LeaderboardId) o;
        return nick.equals(that.nick) && gameId.equals(that.gameId) && rankingId.equals(that.rankingId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nick, gameId, rankingId);
    }

    public String getNick() {
        return nick;
    }

    public void setNick(String nick) {
        this.nick = nick;
    }

    public Long getGameId() {
        return gameId;
    }

    public void setGameId(Long gameId) {
        this.gameId = gameId;
    }

    public Long getRankingId() {
        return rankingId;
    }

    public void setRankingId(Long rankingId) {
        this.rankingId = rankingId;
    }

    public LeaderboardId(String nick, Long gameId, Long rankingId) {
        this.nick = nick;
        this.gameId = gameId;
        this.rankingId = rankingId;
    }

    public LeaderboardId() {
    }
}
