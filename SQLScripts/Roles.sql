--�������� guest
REASSIGN OWNED BY guest TO postgres;
DROP OWNED BY guest;
drop role guest;
--�������� team_captain
REASSIGN OWNED BY team_captain TO postgres;
DROP OWNED BY team_captain;
drop role team_captain;
--�������� studio_owner
REASSIGN OWNED BY studio_owner TO postgres;
DROP OWNED BY studio_owner;
drop role studio_owner;
--�������� studio_owner
REASSIGN OWNED BY tournament_organizer TO postgres;
DROP OWNED BY tournament_organizer;
drop role tournament_organizer;


--�������� guest
CREATE USER guest password 'guest';
--���������� ���� guest
grant pg_read_all_data to guest;
grant insert on users to guest;
grant update on users_id_seq to guest;

--�������� team_captain
CREATE USER team_captain password 'team_captain';
--���������� ���� team_captain
grant postgres to team_captain;

--�������� studio_owner
CREATE USER studio_owner password 'studio_owner';
--���������� ���� studio_owner
grant postgres to studio_owner;

--�������� tournament_organizer
CREATE USER tournament_organizer password 'tournament_organizer';
--���������� ���� tournament_organizer
grant postgres to tournament_organizer;
