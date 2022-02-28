drop trigger update_leaderboard;
drop procedure update_ranking;
drop trigger update_stat;
drop trigger drop_ranking_stats;
drop trigger add_ranking;
drop procedure init_ranking_stats;
drop trigger drop_game_stats;
drop trigger add_game;
drop procedure init_game_stats;
drop trigger drop_player_stats;
drop trigger add_player;
drop procedure init_player_stats;

drop table Record cascade constraints;
drop table Stat cascade constraints;
drop table Leaderboard cascade constraints;
drop table Ranking cascade constraints;
drop table Game cascade constraints;
drop table PLayer cascade constraints;
