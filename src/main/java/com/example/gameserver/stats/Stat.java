package com.example.gameserver.stats;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;
import java.util.Objects;

@Entity
@Table(name = "STAT")
public class Stat {
    @EmbeddedId
    private StatId id;

    @Column(name = "WINS")
    private Integer wins;
    @Column(name = "DRAWS")
    private Integer draws;
    @Column(name = "TOTAL")
    private Integer total;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Stat stat = (Stat) o;
        return id.equals(stat.id) && wins.equals(stat.wins) && draws.equals(stat.draws) && total.equals(stat.total);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, wins, draws, total);
    }

    public StatId getId() {
        return id;
    }

    public void setId(StatId id) {
        this.id = id;
    }

    public Integer getWins() {
        return wins;
    }

    public void setWins(Integer wins) {
        this.wins = wins;
    }

    public Integer getDraws() {
        return draws;
    }

    public void setDraws(Integer draws) {
        this.draws = draws;
    }

    public Integer getTotal() {
        return total;
    }

    public void setTotal(Integer total) {
        this.total = total;
    }

    public Stat(StatId id, Integer wins, Integer draws, Integer total) {
        this.id = id;
        this.wins = wins;
        this.draws = draws;
        this.total = total;
    }

    public Stat() {
    }
}
