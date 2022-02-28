package com.example.gameserver.stats;

import javax.persistence.Column;
import javax.persistence.Embeddable;
import java.io.Serializable;
import java.util.Objects;

@Embeddable
public class StatId implements Serializable {
    @Column(name="NICK")
    private String nick;
    @Column(name="GAME_ID")
    private Long gameId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        StatId statId = (StatId) o;
        return nick.equals(statId.nick) && gameId.equals(statId.gameId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nick, gameId);
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

    public StatId(String nick, Long gameId) {
        this.nick = nick;
        this.gameId = gameId;
    }

    public StatId() {
    }
}