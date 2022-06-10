--guest
CREATE USER guest password 'guest';
--granting access rights to guest
grant pg_read_all_data to guest;
grant insert on users to guest;
grant update on users_id_seq to guest;

--team_captain
CREATE USER team_captain password 'team_captain';
--granting access rights to team_captain
grant postgres to team_captain;

--studio_owner
CREATE USER studio_owner password 'studio_owner';
--granting access rights to studio_owner
grant postgres to studio_owner;

--tournament_organizer
CREATE USER tournament_organizer password 'tournament_organizer';
--granting access rights to tournament_organizer
grant postgres to tournament_organizer;
