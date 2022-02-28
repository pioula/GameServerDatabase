package com.example.gameserver.players;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/players")
public class PlayerController {
    private final Player emptyPlayer = new Player("empty", "empty", "empty", -1, "empty");
    private final PlayerRepository playerRepository;

    public PlayerController(PlayerRepository playerRepository) {
        this.playerRepository = playerRepository;
    }

    @GetMapping
    public List<Player> getPlayers() {
        return playerRepository.findAll();
    }

    @GetMapping("/{nick}")
    public Player getPlayer(@PathVariable String nick) {
        return playerRepository.findById(nick).orElse(emptyPlayer);
    }

    @GetMapping("/get-players-query")
    public List<Player> getPlayersQuery(@RequestParam(required = false, defaultValue = "") String nick,
                                        @RequestParam(required = false, defaultValue = "") String firstName,
                                        @RequestParam(required = false, defaultValue = "") String lastName,
                                        @RequestParam(required = false) Integer minAge,
                                        @RequestParam(required = false) Integer maxAge) {
        if (minAge == null) minAge = 0;
        if (maxAge == null) maxAge = Integer.MAX_VALUE;

        return playerRepository.findByNickContainingAndFirstNameContainingAndLastNameContainingAndAgeBetween(
                nick,
                firstName,
                lastName,
                minAge,
                maxAge);
    }

    @PostMapping
    public ResponseEntity<?> createPlayer(@RequestBody Player player) throws URISyntaxException {
        Player savedPlayer = playerRepository.save(player);
        return ResponseEntity.created(new URI("/players/" + savedPlayer.getNick())).body(savedPlayer);
    }
}
