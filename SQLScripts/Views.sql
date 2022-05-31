--drop view players_view
create or replace VIEW players_view AS
SELECT p.id, t.name as team, c.name as country, p.nickname, p.first_name, p.second_name, p.birth_year, p.rating, p.team_id, p.country_id
FROM players p
	JOIN teams t ON t.id = p.team_id
	JOIN countries c ON c.id = p.country_id

select * from players_view