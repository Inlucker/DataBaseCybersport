--Удаление guest
REASSIGN OWNED BY guest TO postgres;
DROP OWNED BY guest;
drop role guest;
--Удаление canvas_user
REASSIGN OWNED BY team_captain TO postgres;
DROP OWNED BY team_captain;
drop role team_captain;

--Создание guest
CREATE USER guest password 'guest';
--Добавление прав guest
grant pg_read_all_data to guest;
grant insert on users to guest;
grant update on users_id_seq to guest;

--Создание canvas_user
CREATE USER team_captain password 'team_captain';
--Добавление прав canvas_user
grant postgres to team_captain;
