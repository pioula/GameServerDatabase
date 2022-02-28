package com.example.gameserver.leaderboard;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface LeaderboardRepository extends JpaRepository<Leaderboard, LeaderboardId> {
    String LIST = "WITH LIST(NICK, RANKING_VALUE, TOTAL, WINS, DRAWS) AS (" +
            " SELECT A.NICK AS NICK, A.RANKING_VALUE AS RANKING_VALUE, B.TOTAL AS TOTAL, B.WINS AS WINS, B.DRAWS AS DRAWS" +
            " FROM" +
            " LEADERBOARD A" +
            " LEFT JOIN" +
            " STAT B" +
            " ON A.GAME_ID = B.GAME_ID AND A.NICK = B.NICK" +
            " WHERE A.GAME_ID = ?1 AND A.RANKING_ID = ?2" +
            " )";

    String RANKING_LIST = " SELECT (COUNT(B.RANKING_VALUE)+1) AS POSITION, A.NICK AS NICK, A.RANKING_VALUE AS RANKING, A.TOTAL AS TOTAL, A.WINS AS WINS, A.DRAWS AS DRAWS" +
            " FROM" +
            " LIST A" +
            " LEFT JOIN" +
            " LIST B" +
            " ON A.RANKING_VALUE < B.RANKING_VALUE" +
            " GROUP BY A.NICK, A.RANKING_VALUE, A.TOTAL, A.WINS, A.DRAWS" +
            " ORDER BY POSITION";

    @Query(value = LIST +
            RANKING_LIST,
    nativeQuery = true)
    List<LeaderboardList> getLeaderboard(Long gameId, Long rankingId);

    @Query(value = LIST +
            ", RANKING_LIST(POSITION, NICK, RANKING_VALUE, TOTAL, WINS, DRAWS) AS (" +
            RANKING_LIST + ")" +
            " SELECT POSITION, NICK, RANKING_VALUE AS RANKING, TOTAL, WINS, DRAWS" +
            " FROM RANKING_LIST" +
            " WHERE" +
            " POSITION >= ?3 AND POSITION <= ?4 AND" +
            " NICK LIKE CONCAT(CONCAT('%',?5),'%') AND" +
            " RANKING_VALUE >= ?6 AND RANKING_VALUE <= ?7 AND" +
            " TOTAL >= ?8 AND TOTAL <= ?9 AND" +
            " WINS >= ?10 AND WINS <= ?11 AND" +
            " DRAWS >= ?12 AND DRAWS <= ?13",
        nativeQuery = true)
    List<LeaderboardList> getLeaderboardQuery(Long gameId, Long rankingId,
                                              Long minPosition, Long maxPosition,
                                              String nick,
                                              Long minRankingValue, Long maxRankingValue,
                                              Long minTotal, Long maxTotal,
                                              Long minWins, Long maxWins,
                                              Long minDraws, Long maxDraws);

}
