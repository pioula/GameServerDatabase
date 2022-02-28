package com.example.gameserver.ranking;

import com.example.gameserver.games.Game;
import com.example.gameserver.games.GameRepository;
import com.example.gameserver.records.Record;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/rankings")
public class RankingController {
    private final RankingRepository rankingRepository;

    public RankingController(RankingRepository rankingRepository) {
        this.rankingRepository = rankingRepository;
    }

    @GetMapping
    public List<Ranking> getRankings() {
        return rankingRepository.findAll();
    }

    @GetMapping("/{id}")
    public Ranking getRanking(@PathVariable Long id) {
        return rankingRepository.findById(id).orElseThrow(RuntimeException::new);
    }

    @GetMapping("/list")
    public List<RankingList> getRankingList() {
        return rankingRepository.getRankingNames();
    }

    @PostMapping
    public ResponseEntity<?> createRanking(@RequestBody Ranking ranking) {
        try {
            Ranking savedRanking = rankingRepository.save(ranking);
            return ResponseEntity.created(new URI("/rankings/" + savedRanking.getId())).body(savedRanking);
        }
        catch(Exception exp) {
            return null;
        }
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteRanking(@PathVariable Long id) {
        rankingRepository.deleteById(id);
        return ResponseEntity.ok().build();
    }

    @GetMapping("/get-ranks-by-name")
    public List<Ranking> getGamesByName(@RequestParam(name = "name") String name) {
        return rankingRepository.findByNameContaining(name);
    }
}
