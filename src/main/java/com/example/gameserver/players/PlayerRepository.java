package com.example.gameserver.players;

import com.example.gameserver.games.Game;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface PlayerRepository extends JpaRepository<Player, String> {
    List<Player> findByNickContainingAndFirstNameContainingAndLastNameContainingAndAgeBetween(String nick,
                                                                                                String firstName,
                                                                                                String lastName,
                                                                                                Integer minAge,
                                                                                                Integer maxAge);
}