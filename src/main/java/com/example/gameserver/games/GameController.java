package com.example.gameserver.games;

import org.springframework.data.jpa.repository.Query;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/games")
public class GameController {
    private final GameRepository gameRepository;

    public GameController(GameRepository gameRepository) {
        this.gameRepository = gameRepository;
    }

    @GetMapping
    public List<Game> getGames() {
        return gameRepository.findAll();
    }

    @GetMapping("/{id}")
    public Game getGame(@PathVariable Long id) {
        return gameRepository.findById(id).orElseThrow(RuntimeException::new);
    }

    @GetMapping("/get-games-by-name")
    public List<Game> getGamesByName(@RequestParam(name = "name") String name) {
        return gameRepository.findByNameContaining(name);
    }

    @PostMapping
    public ResponseEntity<?> createGame(@RequestBody Game game) throws URISyntaxException {
        Game savedGame = gameRepository.save(game);
        return ResponseEntity.created(new URI("/games/" + savedGame.getId())).body(savedGame);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteGame(@PathVariable Long id) {
        gameRepository.deleteById(id);
        return ResponseEntity.ok().build();
    }
}
