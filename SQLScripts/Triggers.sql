--Тригеры для удаления пользователей--
/* Тригер для удаления team_captain */
-- Создаём функцию для триггера...
create or replace function whenDeleteTeamCaptain()
returns trigger 
as $$
BEGIN
	UPDATE players
	SET team_id = NULL
	WHERE team_id IN
		(SELECT id AS team_id
		 FROM teams t
		 WHERE t.captain_id = OLD.id);
		
	UPDATE teams
	set captain_id = null
	where captain_id = old.id;
	return OLD;
end
$$ language plpgsql;

--drop function whenDeleteTeamCaptain();

--Теперь триггер
create or replace trigger tr_whenDeleteTeamCaptain
before delete
on Users
for each row
when (OLD.role_id = 4)
execute procedure whenDeleteTeamCaptain();

--DROP trigger tr_whenDeleteTeamCaptain on Users


/* Тригер для удаления studio_owner */
-- Создаём функцию для триггера...
create or replace function whenDeleteStudioOwner()
returns trigger 
as $$
BEGIN
	RAISE notice 'old = %', (old.id);
	UPDATE commentators 
	SET studio_id = NULL
	WHERE studio_id IN
		(SELECT id AS studio_id
		 FROM studios s
		 WHERE s.owner_id = OLD.id);
		
	UPDATE studios
	set owner_id = null
	where owner_id = old.id;
	return OLD;
end
$$ language plpgsql;

--drop function whenDeleteStudioOwner();

--Теперь триггер
create or replace trigger tr_whenDeleteStudioOwner
before delete
on Users
for each row
when (OLD.role_id = 3)
execute procedure whenDeleteStudioOwner();

--DROP trigger tr_whenDeleteStudioOwner on Users