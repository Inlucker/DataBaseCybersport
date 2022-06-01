--Удаление guest
REASSIGN OWNED BY guest TO postgres;
DROP OWNED BY guest;
drop role guest;
--Удаление team_captain
REASSIGN OWNED BY team_captain TO postgres;
DROP OWNED BY team_captain;
drop role team_captain;
--Удаление studio_owner
REASSIGN OWNED BY studio_owner TO postgres;
DROP OWNED BY studio_owner;
drop role studio_owner;
--Удаление studio_owner
REASSIGN OWNED BY tournament_organizer TO postgres;
DROP OWNED BY tournament_organizer;
drop role tournament_organizer;


--Создание guest
CREATE USER guest password 'guest';
--Добавление прав guest
grant pg_read_all_data to guest;
grant insert on users to guest;
grant update on users_id_seq to guest;

--Создание team_captain
CREATE USER team_captain password 'team_captain';
--Добавление прав team_captain
grant postgres to team_captain;

--Создание studio_owner
CREATE USER studio_owner password 'studio_owner';
--Добавление прав studio_owner
grant postgres to studio_owner;

--Создание tournament_organizer
CREATE USER tournament_organizer password 'tournament_organizer';
--Добавление прав tournament_organizer
grant postgres to tournament_organizer;
