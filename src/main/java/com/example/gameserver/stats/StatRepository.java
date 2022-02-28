package com.example.gameserver.stats;

import org.springframework.data.jpa.repository.JpaRepository;

public interface StatRepository extends JpaRepository<Stat, StatId> {
}
