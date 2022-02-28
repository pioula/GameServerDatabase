package com.example.gameserver.records;

import com.example.gameserver.games.Game;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.Date;
import java.util.List;

public interface RecordRepository extends JpaRepository<Record, Long> {
    List<Record> findByGameIdOrderByDateAsc(Long gameId);

    List<Record> findByGameIdOrderByDateDesc(Long gameId);

    String query = "SELECT *" +
            " FROM RECORD" +
            " WHERE" +
            " GAME_ID = :gameId AND" +
            " :dateBeg <= RECORD.GAME_DATE AND" +
            " :dateEnd >= RECORD.GAME_DATE AND" +
            " NICK_ONE LIKE CONCAT('%', CONCAT(:nickOne, '%')) AND" +
            " NICK_TWO LIKE CONCAT('%', CONCAT(:nickTwo, '%')) AND" +
            " (WINNER = :draw OR WINNER = :oneWin OR WINNER = :twoWin)";

    @Query(value=query +
            " ORDER BY GAME_DATE DESC",
            nativeQuery = true)
    List<Record> findByQueryDesc(@Param("draw") Long draw,
                             @Param("oneWin") Long oneWin,
                             @Param("twoWin") Long twoWin,
                             @Param("gameId") Long gameId,
                             @Param("dateBeg") Date dateBeg,
                             @Param("dateEnd") Date dateEnd,
                             @Param("nickOne") String nickOne,
                             @Param("nickTwo") String nickTwo);
    @Query(value=query +
            " ORDER BY GAME_DATE",
            nativeQuery = true)
    List<Record> findByQueryAsc(@Param("draw") Long draw,
                                 @Param("oneWin") Long oneWin,
                                 @Param("twoWin") Long twoWin,
                                 @Param("gameId") Long gameId,
                                 @Param("dateBeg") Date dateBeg,
                                 @Param("dateEnd") Date dateEnd,
                                 @Param("nickOne") String nickOne,
                                 @Param("nickTwo") String nickTwo);
}
