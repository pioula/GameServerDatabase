-- TABLES

create table Player (
    nick varchar2(20) primary key,
    password varchar2(20) not null,
    age int not null,
    first_name varchar2(20) not null,
    last_name varchar2(20) not null
);

create table Game (
    id int primary key,
    name varchar2(20) not null
);

create table Ranking (
    id int primary key,
    name varchar2(20) not null,
    base int not null,
    formula varchar2(100) not null
);

create table Leaderboard (
    nick varchar2(20) not null references Player,
    game_id int not null references Game,
    ranking_id int not null references Ranking,
    ranking_value int not null,
    constraint leaderboard_pk primary key (nick, game_id, ranking_id)
);

create table Stat (
    nick varchar2(20) not null references Player,
    game_id int not null references Game,
    wins int not null,
    draws int not null,
    total int not null,
    constraint stat_pk primary key (nick, game_id),
    constraint number_of_games check (total >= draws + wins)
);

create table Record (
    id int primary key,
    game_date date not null,
    moves varchar2(1000) not null,
    game_id int not null references Game,
    nick_one varchar2(20) not null references Player,
    nick_two varchar2(20) not null references Player,
    winner int not null
);

-- TRIGGERS

create or replace procedure init_player_stats(nick varchar2) is
    cursor games is (select id from Game);
    cursor rankings is (select id, base from Ranking);
begin
    for i in games
    loop
        insert into Stat values (nick, i.id, 0, 0, 0);
	for j in rankings
	loop
	    insert into Leaderboard values (nick, i.id, j.id, j.base);
	end loop;
    end loop;
end;
/

create or replace trigger add_player
after insert on Player
for each row
begin
    init_player_stats(:new.nick);
end;
/

create or replace trigger drop_player_stats
before delete on Player
for each row
begin
    delete from Stat where nick = :old.nick;
    delete from Leaderboard where nick = :old.nick;
end;
/

create or replace procedure init_game_stats(id int) is
    cursor players is (select nick from Player);
    cursor rankings is (select id, base from Ranking);
begin
    for i in players
    loop
        insert into Stat values (i.nick, id, 0, 0, 0);
	for j in rankings
	loop
	    insert into Leaderboard values (i.nick, id, j.id, j.base);
	end loop;
    end loop;
end;
/

create or replace trigger add_game
after insert on Game
for each row
begin
    init_game_stats(:new.id);
end;
/

create or replace trigger drop_game_stats
before delete on Game
for each row
begin
    delete from Stat where game_id = :old.id;
    delete from Leaderboard where game_id = :old.id;
end;
/

create or replace procedure init_ranking_stats(id int, base int) is
    cursor players is (select nick from Player);
    cursor games is (select id from Game);
begin
    for i in players
    loop
        for j in games
	loop
	    insert into Leaderboard values (i.nick, j.id, id, base);
	end loop;
    end loop;
end;
/

create or replace procedure update_new_ranking(id int, formula varchar2) is
    cursor records is (select game_id, nick_one, nick_two, winner
    from (select * from Record order by game_date));
    a int := 0;
    b int := 0;
    r int := 0;
    x number := 0;
begin
    for i in records
    loop
        if i.winner = 1 then
	    x := 1;
	else
            if i.winner = 2 then
	        x := 0;
	    else
	        x := 0.5;
	    end if;
        end if;
        select ranking_value into a from Leaderboard
	where nick = i.nick_one and game_id = i.game_id
	and ranking_id = id;
	select ranking_value into b from Leaderboard
	where nick = i.nick_two and game_id = i.game_id
	and ranking_id = id;
	with vars (name, val) as (
	    select 'a', a from dual union all
	    select 'b', b from dual union all
	    select 'x', x from dual
	    )
	select plcalc.eval(p_expr => formula,
	                   p_vars => cast(collect(plc_bind_var(name, val))
			   as plc_bind_list))
	into r from vars;
	update Leaderboard set ranking_value = a + (r - a)
	where nick = i.nick_one and game_id = i.game_id
	and ranking_id = id;
	update Leaderboard set ranking_value = b - (r - a)
	where nick = i.nick_two and game_id = i.game_id
	and ranking_id = id;
    end loop;
end;
/

create or replace trigger add_ranking
after insert on Ranking
for each row
begin
    init_ranking_stats(:new.id, :new.base);
    update_new_ranking(:new.id, :new.formula);
end;
/

create or replace trigger drop_ranking_stats
before delete on Ranking
for each row
begin
    delete from Leaderboard where ranking_id = :old.id;
end;
/

create or replace trigger update_stat
after insert on Record
for each row
begin
    if :new.winner = 1 then
        update Stat set wins = wins + 1, total = total + 1
	where nick = :new.nick_one and game_id = :new.game_id;
	update Stat set total = total + 1
	where nick = :new.nick_two and game_id = :new.game_id;
    else
        if :new.winner = 2 then
	    update Stat set wins = wins + 1, total = total + 1
	    where nick = :new.nick_two and game_id = :new.game_id;
	    update Stat set total = total + 1
	    where nick = :new.nick_one and game_id = :new.game_id;
	else
	    update Stat set draws = draws + 1, total = total + 1
	    where nick = :new.nick_one and game_id = :new.game_id;
	    update Stat set draws = draws + 1, total = total + 1
	    where nick = :new.nick_two and game_id = :new.game_id;
	end if;
    end if;
end;
/

create or replace procedure update_ranking
(nick_one varchar2, nick_two varchar2, id int, x number) is
    cursor rankings is (select id, formula from Ranking);
    a int := 0;
    b int := 0;
    r int := 0;
begin
    for i in rankings
    loop
        select ranking_value into a from Leaderboard
	where nick = nick_one and game_id = id and ranking_id = i.id;
	select ranking_value into b from Leaderboard
	where nick = nick_two and game_id = id and ranking_id = i.id;
	with vars (name, val) as (
	    select 'a', a from dual union all
	    select 'b', b from dual union all
	    select 'x', x from dual
	)
	select plcalc.eval(p_expr => i.formula,
	       		   p_vars => cast(collect(plc_bind_var(name, val))
			   as plc_bind_list))
	into r from vars;
	update Leaderboard set ranking_value = a + (r - a)
	where nick = nick_one and game_id = id and ranking_id = i.id;
	update Leaderboard set ranking_value = b - (r - a)
	where nick = nick_two and game_id = id and ranking_id = i.id;
    end loop;
end;
/

create or replace trigger update_leaderboard
after insert on Record
for each row
begin
    if :new.winner = 1 then
        update_ranking(:new.nick_one, :new.nick_two, :new.game_id, 1);
    else
        if :new.winner = 2 then
	    update_ranking(:new.nick_one, :new.nick_two, :new.game_id, 0);
	else
	    update_ranking(:new.nick_one, :new.nick_two, :new.game_id, 0.5);
	end if;
    end if;
end;
/
