--������� ��� �������� �������������--
/* ������ ��� �������� team_captain */
-- ������ ������� ��� ��������...
create or replace function whenDeleteTeamCaptain()
returns trigger 
as $$
BEGIN
	--RAISE notice 'old = %', (old.id);
	UPDATE players
	SET team_id = NULL
	WHERE team_id IN
		(SELECT id AS team_id
		 FROM teams t
		 WHERE t.captain_id = OLD.id);
		
	UPDATE users
	set deleted = TRUE
	where id = old.id;
	return NEW;
end
$$ language plpgsql;

--drop function whenDeleteTeamCaptain();

--������ �������
create or replace trigger tr_whenDeleteTeamCaptain
before delete
on Users
for each row
when (OLD.role_id = 4)
execute procedure whenDeleteTeamCaptain();

--DROP trigger tr_whenDeleteTeamCaptain on Users


/* ������ ��� �������� studio_owner */
-- ������ ������� ��� ��������...
create or replace function whenDeleteStudioOwner()
returns trigger 
as $$
BEGIN
	--RAISE notice 'old = %', (old.id);
	UPDATE commentators 
	SET studio_id = NULL
	WHERE studio_id IN
		(SELECT id AS studio_id
		 FROM studios s
		 WHERE s.owner_id = OLD.id);
		
	UPDATE users
	set deleted = TRUE
	where id = old.id;
	return NEW;
end
$$ language plpgsql;

--drop function whenDeleteStudioOwner();

--������ �������
create or replace trigger tr_whenDeleteStudioOwner
before delete
on Users
for each row
when (OLD.role_id = 3)
execute procedure whenDeleteStudioOwner();

--DROP trigger tr_whenDeleteStudioOwner on Users


/* ������ ��� �������� tournament_organizer */
-- ������ ������� ��� ��������...
create or replace function whenDeleteTournamentOrganizer()
returns trigger 
as $$
BEGIN
	--RAISE notice 'old = %', (old.id);
	UPDATE users
	set deleted = TRUE
	where id = old.id;

	return NEW;
end
$$ language plpgsql;

--drop function whenDeleteTournamentOrganizer();

--������ �������
create or replace trigger tr_whenDeleteTournamentOrganizer
before delete
on Users
for each row
when (OLD.role_id = 2)
execute procedure whenDeleteTournamentOrganizer();

--DROP trigger tr_whenDeleteTournamentOrganizer on Users