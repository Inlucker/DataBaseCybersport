from random import randint


def generateTournamentTeams(records_number):
    f = open('TournamentTeams.csv', 'w')
    for i in range(records_number):
        tournament_id = randint(1, records_number)
        team_id = randint(1, records_number)
        line = "{0}|{1}\n".format(tournament_id,
                                  team_id)
        f.write(line)
    f.close()
    print("Finished generating TournamentTeams")


generateTournamentTeams(1000)
