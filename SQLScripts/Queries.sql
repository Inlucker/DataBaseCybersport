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
values(NULL, 1, 'Inlucker', 'Arseny', 'Pronin', 2000, 'Offlaner', 7000);


--For testing triggers
update tournaments set organizer_id = 4 where organizer_id = 3;

update tournaments set organizer_id = 4 where organizer_id = 9;
