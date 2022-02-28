package com.example.gameserver.ranking;

import com.example.gameserver.games.Game;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface RankingRepository extends JpaRepository<Ranking, Long> {
    @Query("select a.id as id, a.name as name from Ranking a")
    List<RankingList> getRankingNames();

    List<Ranking> findByNameContaining(String name);
}
