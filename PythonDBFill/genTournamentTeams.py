from random import randint


def generateTournamentTeams(records_number):
    f = open('TournamentTeams.csv', 'w')
    tournaments_teams = []
    for i in range(records_number):
        tournament_id = i+1

        teams_id = []
        for j in range(16):
            t_id = randint(1, records_number)
            while t_id in teams_id:
                t_id = randint(1, records_number)
            teams_id.append(t_id)
            line = "{0}|{1}\n".format(tournament_id,
                                      teams_id[j])
            f.write(line)
        tournaments_teams.append(teams_id)

        # team_id = randint(1, records_number)
        # line = "{0}|{1}\n".format(tournament_id, team_id)
        # f.write(line)
    f.close()
    print("Finished generating TournamentTeams")
    return tournaments_teams


# generateTournamentTeams(1000)
