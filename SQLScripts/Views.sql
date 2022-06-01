drop view if exists players_view;
create or replace VIEW players_view AS
SELECT p.id, t.name as team, c.name as country, p.nickname, p.first_name, p.second_name, p.birth_year, p.main_role, p.rating, p.team_id, p.country_id
FROM players p
	LEFT OUTER JOIN teams t ON t.id = p.team_id
	LEFT OUTER JOIN countries c ON c.id = p.country_id
order by p.id;

--select * from players_view;

drop view if exists players_view_by_teams;
create or replace VIEW players_view_by_teams AS
SELECT p.id, t.name as team, c.name as country, p.nickname, p.first_name, p.second_name, p.birth_year, p.main_role, p.rating, p.team_id, p.country_id, t.captain_id
FROM players p
	LEFT OUTER JOIN teams t ON t.id = p.team_id
	LEFT OUTER JOIN countries c ON c.id = p.country_id
order by t.name, p.id;

--select * from players_view_by_teams;

drop view if exists teams_avg;
create or replace VIEW teams_avg as
select t.id, avg(p.rating)
from teams t
	join players p on p.team_id = t.id
group by t.id
order by t.id;

--select * from teams_avg;

drop view if exists teams_view;
create or replace VIEW teams_view AS
SELECT t.id, c.name as country, s.name as sponsor, u.login as captain, t.name, ta.avg as avg_rating, t.country_id, t.sponsor_id, t.captain_id
FROM teams t
	LEFT OUTER JOIN countries c  on c.id = t.country_id
	LEFT OUTER JOIN sponsors s   on s.id = t.sponsor_id
	LEFT OUTER JOIN users u      on u.id = t.captain_id
	LEFT OUTER JOIN teams_avg ta on ta.id = t.id
order by t.id;
	
--select * from teams_view;

drop view if exists commentators_view;
create or replace VIEW commentators_view AS
SELECT c.id, s.name as studio, coun.name as country, c.nickname, c.first_name, c.second_name, c.birth_year, c.popularity, c.studio_id, c.country_id, s.owner_id
FROM commentators c
	LEFT OUTER JOIN studios s ON s.id = c.studio_id
	LEFT OUTER JOIN countries coun ON coun.id = c.country_id
order by c.id;

--select * from commentators_view;

drop view if exists studios_avg;
create or replace VIEW studios_avg as
select s.id, avg(c.popularity)
from studios s
	join commentators c on c.studio_id = s.id
group by s.id
order by s.id;

--select * from studios_avg;

drop view if exists studios_view;
create or replace VIEW studios_view AS
SELECT s.id, c.name as country, u.login as owner, s.name, sa.avg as avg_popularity, s.country_id, s.owner_id
FROM studios s
	LEFT OUTER JOIN countries c  on c.id = s.country_id
	LEFT OUTER JOIN users u      on u.id = s.owner_id
	LEFT OUTER JOIN studios_avg sa on sa.id = s.id
order by s.id;

--select * from studios_view;

drop view if exists tournaments_view;
create or replace VIEW tournaments_view AS
SELECT t.id, c.name as country, u.login as organizer, t.name, t.prizepool, t.country_id, t.organizer_id
FROM tournaments t
	LEFT OUTER JOIN countries c  on c.id = t.country_id
	LEFT OUTER JOIN users u      on u.id = t.organizer_id
order by t.id;

--select * from tournaments_view;

drop view if exists matches_view;
create or replace VIEW matches_view AS
SELECT t1.name as team1, t2.name as team2, w.name as winner, s.name as studio, c.nickname as commentator, t.name as tournament, m.date,
		m.team1_id, m.team2_id, m.winner_id, m.studio_id, m.commentator_id, m.tournament_id
FROM matches m
	LEFT OUTER JOIN teams t1 on m.team1_id = t1.id
	LEFT OUTER JOIN teams t2 on m.team2_id = t2.id
	LEFT OUTER JOIN teams w  on m.winner_id = w.id
	LEFT OUTER JOIN studios s  on m.studio_id = s.id
	LEFT OUTER JOIN commentators c  on m.commentator_id = c.id
	LEFT OUTER JOIN tournaments t  on m.tournament_id = t.id
order by m.date;

--select * from matches_view;

drop view if exists tournament_teams_view;
create or replace VIEW tournament_teams_view AS
SELECT t.id, c.name as country, s.name as sponsor, u.login as captain, t.name, ta.avg as avg_rating, t.country_id, t.sponsor_id, t.captain_id, tt.tournament_id
FROM tournamentteams tt
	LEFT OUTER JOIN teams t on tt.team_id = t.id
	LEFT OUTER JOIN countries c  on c.id = t.country_id
	LEFT OUTER JOIN sponsors s   on s.id = t.sponsor_id
	LEFT OUTER JOIN users u      on u.id = t.captain_id
	LEFT OUTER JOIN teams_avg ta on ta.id = t.id
order by tt.tournament_id;
	
--select * from tournament_teams_view;