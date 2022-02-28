package com.example.gameserver.records;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.Parameter;

import javax.persistence.*;
import java.util.Date;
import java.util.Objects;

@Entity
@Table(name = "Record")
public class Record {
    @GenericGenerator(
            name = "userSequenceGenerator",
            strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
            parameters = {
                    @Parameter(name = "sequence_name", value = "userSequence"),
                    @Parameter(name = "initial_value", value = "2000"),
                    @Parameter(name = "increment_size", value = "1")
            }
    )
    @Id
    @GeneratedValue(generator = "userSequenceGenerator")
    @Column(name = "ID", nullable = false)
    private Long id;

    @Column(name = "GAME_DATE", nullable = false)
    @Temporal(TemporalType.DATE)
    private Date date;
    @Column(name = "MOVES", nullable = false)
    private String moves;
    @Column(name = "GAME_ID", nullable = false)
    private Long gameId;
    @Column(name = "NICK_ONE", nullable = false)
    private String nickOne;
    @Column(name = "NICK_TWO", nullable = false)
    private String nickTwo;
    @Column(name = "WINNER", nullable = false)
    private Long winner;

    public Record() {
    }

    public Record(Long id, Date date, String moves, Long gameId, String nickOne, String nickTwo, Long winner) {
        this.id = id;
        this.date = date;
        this.moves = moves;
        this.gameId = gameId;
        this.nickOne = nickOne;
        this.nickTwo = nickTwo;
        this.winner = winner;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getMoves() {
        return moves;
    }

    public void setMoves(String moves) {
        this.moves = moves;
    }

    public Long getGameId() {
        return gameId;
    }

    public void setGameId(Long gameId) {
        this.gameId = gameId;
    }

    public String getNickOne() {
        return nickOne;
    }

    public void setNickOne(String nickOne) {
        this.nickOne = nickOne;
    }

    public String getNickTwo() {
        return nickTwo;
    }

    public void setNickTwo(String nickTwo) {
        this.nickTwo = nickTwo;
    }

    public Long getWinner() {
        return winner;
    }

    public void setWinner(Long winner) {
        this.winner = winner;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Record record = (Record) o;
        return id.equals(record.id) && date.equals(record.date) && moves.equals(record.moves) && gameId.equals(record.gameId) && nickOne.equals(record.nickOne) && nickTwo.equals(record.nickTwo) && winner.equals(record.winner);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, date, moves, gameId, nickOne, nickTwo, winner);
    }

    @Override
    public String toString() {
        return "Record{" +
                "id=" + id +
                ", date=" + date +
                ", moves='" + moves + '\'' +
                ", gameId=" + gameId +
                ", nickOne='" + nickOne + '\'' +
                ", nickTwo='" + nickTwo + '\'' +
                ", winner=" + winner +
                '}';
    }
}
