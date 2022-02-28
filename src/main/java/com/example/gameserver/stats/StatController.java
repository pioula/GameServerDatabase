package com.example.gameserver.stats;


import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/stats")
public class StatController {
    private final StatRepository statRepository;

    public StatController(StatRepository statRepository) {
        this.statRepository = statRepository;
    }

    @GetMapping
    public List<Stat> getStats() {
        return statRepository.findAll();
    }

    @PostMapping
    public ResponseEntity<?> createStat(@RequestBody Stat stat) throws URISyntaxException {
        Stat savedStat = statRepository.save(stat);
        return ResponseEntity.created(new URI("/stats/" + savedStat.getId())).body(savedStat);
    }

}