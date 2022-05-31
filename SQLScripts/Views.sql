drop view players_view;
create or replace VIEW players_view AS
SELECT p.id, t.name as team, c.name as country, p.nickname, p.first_name, p.second_name, p.birth_year, p.main_role, p.rating, p.team_id, p.country_id
FROM players p
	LEFT OUTER JOIN teams t ON t.id = p.team_id
	LEFT OUTER JOIN countries c ON c.id = p.country_id;

--select * from players_view;

--drop view teams_avg;
create or replace VIEW teams_avg as
select t.id, avg(p.rating)
from teams t
	join players p on p.team_id = t.id
group by t.id;

--select * from teams_avg;

drop view teams_view;
create or replace VIEW teams_view AS
SELECT t.id, c.name as country, s.name as sponsor, u.login as captain, t.name, ta.avg as avg_rating, t.country_id, t.sponsor_id, t.captain_id
FROM teams t
	LEFT OUTER JOIN countries c  on c.id = t.country_id
	LEFT OUTER JOIN sponsors s   on s.id = t.sponsor_id
	LEFT OUTER JOIN users u      on u.id = t.captain_id
	LEFT OUTER JOIN teams_avg ta on ta.id = t.id;
	
select * from teams_view;