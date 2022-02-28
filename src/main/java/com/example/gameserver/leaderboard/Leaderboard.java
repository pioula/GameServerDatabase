package com.example.gameserver.leaderboard;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "LEADERBOARD")
public class Leaderboard {
    @EmbeddedId
    private LeaderboardId id;

    @Column(name = "RANKING_VALUE")
    private Integer rankingValue;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Leaderboard that = (Leaderboard) o;
        return id.equals(that.id) && rankingValue.equals(that.rankingValue);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, rankingValue);
    }

    public LeaderboardId getId() {
        return id;
    }

    public void setId(LeaderboardId id) {
        this.id = id;
    }

    public Integer getRankingValue() {
        return rankingValue;
    }

    public void setRankingValue(Integer rankingValue) {
        this.rankingValue = rankingValue;
    }

    public Leaderboard(LeaderboardId id, Integer rankingValue) {
        this.id = id;
        this.rankingValue = rankingValue;
    }

    public Leaderboard() {
    }
}

