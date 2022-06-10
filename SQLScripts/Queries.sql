--Users
--select u.id, u.login, u.password, r.name as role
--FROM Users u join UserRoles r on u.role_id = r.id
--where login = 'palmerfernando' and password = '123';

select * from Users where login = 'palmerfernando' and password = '123';

--WITH tmp as
--(
--	select id as r_id, name as l, name as p
--	from UserRoles
--	where name = 'Team_Captain'
--)
--insert into Users(role_id, login, password) SELECT * from tmp;

insert into Users(role_id, login, password) values(4, 'User1', '123');

delete from Users where id=1001;

--Players

insert into Players(team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating)
values(NULL, 1, 'Inlucker', 'Arseny', 'Pronin', 2000, 'Offlaner', 7000) RETURNING id;


--For testing triggers
update tournaments set organizer_id = 4 where organizer_id = 3;

update tournaments set organizer_id = 4 where organizer_id = 9;

--For testing indexes
--test1 4/3
EXPLAIN ANALYZE select * from matches where tournament_id = 523;

drop index tournament_id_idx RESTRICT;
CREATE INDEX tournament_id_idx ON matches (tournament_id);

drop function getAnalysisMatches(int)
create OR REPLACE function getAnalysisMatches(id int)
returns float
as $$
    plan = plpy.prepare("EXPLAIN ANALYZE select * from matches where tournament_id = $1", ["int"])
    rez = 0.0
    for i in range(10000):
	    result = plpy.execute(plan, [id])
	    tmp = result[4]['QUERY PLAN']
	    tmp = tmp[tmp.find(':')+2:tmp.rfind('m')-1]
	    rez = rez + float(tmp)
	#rez = rez / 10000.0
    return rez
$$ LANGUAGE PLPYTHON3U;

select getAnalysisMatches(523)/10000 as avg_time;

--test2 4/6
EXPLAIN ANALYZE select * from players where team_id = 523;

drop index team_id_idx RESTRICT;
CREATE INDEX team_id_idx ON players (team_id);

drop function getAnalysisPlayers(int)
create OR REPLACE function getAnalysisPlayers(id int)
returns float
as $$
    plan = plpy.prepare("EXPLAIN ANALYZE select * from players where team_id = $1", ["int"])
    rez = 0.0
    for i in range(10000):
	    result = plpy.execute(plan, [id])
	    tmp = result[4]['QUERY PLAN']
	    tmp = tmp[tmp.find(':')+2:tmp.rfind('m')-1]
	    rez = rez + float(tmp)
    return rez
$$ LANGUAGE PLPYTHON3U;

select getAnalysisPlayers(523)/10000 as avg_time;

--test3 4/5
EXPLAIN ANALYZE select * from commentators where studio_id = 523;

drop index studio_id_idx RESTRICT;
CREATE INDEX studio_id_idx ON commentators (studio_id);

drop function getAnalysisCommentators(int)
create OR REPLACE function getAnalysisCommentators(id int)
returns float
as $$
    plan = plpy.prepare("EXPLAIN ANALYZE select * from commentators where studio_id = $1", ["int"])
    rez = 0.0
    for i in range(10000):
	    result = plpy.execute(plan, [id])
	    tmp = result[4]['QUERY PLAN']
	    tmp = tmp[tmp.find(':')+2:tmp.rfind('m')-1]
	    rez = rez + float(tmp)
    return rez
$$ LANGUAGE PLPYTHON3U;

select getAnalysisCommentators(523)/10000 as avg_time;
