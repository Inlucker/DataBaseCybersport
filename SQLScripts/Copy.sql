copy UserRoles from '/UserRoles.csv' delimiter '|' csv;

copy Users(role_id, login, password, deleted) from '/Users.csv' delimiter '|' csv;

copy Countries from '/Countries.csv' delimiter '|' csv;

copy Sponsors(country_id, name) from '/Sponsors.csv' delimiter '|' csv;

copy Teams(country_id, sponsor_id, captain_id, name) from '/Teams.csv' delimiter '|' csv;

copy Players(team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating) from '/Players.csv' delimiter '|' csv;

copy Studios(country_id, owner_id, name) from '/Studios.csv' delimiter '|' csv;

copy Commentators(studio_id, country_id, nickname, first_name, second_name, birth_year, popularity) from '/Commentators.csv' delimiter '|' csv;

copy Tournaments(country_id, organizer_id, name, prizepool) from '/Tournaments.csv' delimiter '|' csv;

copy Matches(team1_id, team2_id, winner_id, studio_id, commentator_id, tournament_id, date) from '/Matches.csv' delimiter '|' csv;

copy TournamentTeams(tournament_id, team_id) from '/TournamentTeams.csv' delimiter '|' csv;

/*
delete from UserRoles;
delete from Users;
delete from Countries;
delete from Sponsors;
delete from Teams;
delete from Players;
delete from Studios;
delete from Commentators;
delete from Tournaments;
delete from Matches;
delete from TournamentTeams;
*/