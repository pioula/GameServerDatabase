package com.example.gameserver.leaderboard;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/leaderboards")
public class LeaderboardController {
    private final LeaderboardRepository leaderboardRepository;

    public LeaderboardController(LeaderboardRepository leaderboardRepository) {
        this.leaderboardRepository = leaderboardRepository;
    }

    @GetMapping
    public List<Leaderboard> getLeaderboards() {
        return leaderboardRepository.findAll();
    }

    @GetMapping("/list")
    public List<LeaderboardList> getLeaderboard(@RequestParam(name="game") Long gameId, @RequestParam(name="ranking") Long rankingId) {
        return leaderboardRepository.getLeaderboard(gameId, rankingId);
    }

    @GetMapping("/query")
    public List<LeaderboardList> getLeaderboardQuery(@RequestParam(name="game") Long gameId,
                     @RequestParam(name="ranking") Long rankingId,
                     @RequestParam(name="minPosition", required = false) Long minPosition,
                     @RequestParam(name="maxPosition", required = false) Long maxPosition,
                     @RequestParam(name="nick", required = false) String nick,
                     @RequestParam(name="minRanking", required = false) Long minRankingValue,
                     @RequestParam(name="maxRanking", required = false) Long maxRankingValue,
                     @RequestParam(name="minTotal", required = false) Long minTotal,
                     @RequestParam(name="maxTotal", required = false) Long maxTotal,
                     @RequestParam(name="minWins", required = false) Long minWins,
                     @RequestParam(name="maxWins", required = false) Long maxWins,
                     @RequestParam(name="minDraws", required = false) Long minDraws,
                     @RequestParam(name="maxDraws", required = false) Long maxDraws) {
        if (minPosition == null) minPosition = 0L;
        if (maxPosition == null) maxPosition = Long.MAX_VALUE;
        if (nick == null) nick = "";
        if (minRankingValue == null) minRankingValue = Long.MIN_VALUE;
        if (maxRankingValue == null) maxRankingValue = Long.MAX_VALUE;
        if (minTotal == null) minTotal = 0L;
        if (maxTotal == null) maxTotal = Long.MAX_VALUE;
        if (minWins == null) minWins = 0L;
        if (maxWins == null) maxWins = Long.MAX_VALUE;
        if (minDraws == null) minDraws = 0L;
        if (maxDraws == null) maxDraws = Long.MAX_VALUE;
        return leaderboardRepository.getLeaderboardQuery(gameId, rankingId,
                minPosition, maxPosition,
                nick,
                minRankingValue, maxRankingValue,
                minTotal, maxTotal,
                minWins, maxWins,
                minDraws, maxDraws);
    }

    @PostMapping
    public ResponseEntity<?> createLeaderboard(@RequestBody Leaderboard leaderboard) throws URISyntaxException {
        Leaderboard savedLeaderboard = leaderboardRepository.save(leaderboard);
        return ResponseEntity.created(new URI("/leaderboards/" + savedLeaderboard.getId())).body(savedLeaderboard);
    }
}