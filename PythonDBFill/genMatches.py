from faker import Faker
from random import randint
from random import choice
import datetime


def checkDate(date):
    # year, month, day = map(int, date.split('-'))
    year, month, day = date.year, date.month, date.day
    now = datetime.datetime.now()
    winner_flag = False
    if (year < now.year):
        winner_flag = True
    elif (year > now.year):
        winner_flag = False
    else:
        if (month < now.month):
            winner_flag = True
        elif (month > now.month):
            winner_flag = False
        else:
            if (day < now.day):
                winner_flag = True
            elif (day > now.day):
                winner_flag = False
    return winner_flag


def generateMatches(records_number, tournaments_teams):
    faker = Faker()
    f = open('Matches.csv', 'w')
    for i in range(records_number):
        # tournament_id = randint(1, records_number)
        tournament_id = i+1

        teams_id = tournaments_teams[i]

        for j in range(len(teams_id)//2):
            team1_id = teams_id[j]
            team2_id = teams_id[len(teams_id)//2+j]
            winner = ''
            date = faker.date_this_year(True, True)
            if (checkDate(date)):
                winner = choice([team1_id, team2_id])
            studio_id = randint(1, records_number)
            commentator_id = randint(1, records_number)
            line = "{0}|{1}|{2}|{3}|{4}|{5}|{6}\n".format(team1_id,
                                                          team2_id,
                                                          winner,
                                                          studio_id,
                                                          commentator_id,
                                                          tournament_id,
                                                          date)
            f.write(line)
    f.close()
    print("Finished generating Matches")


# generateMatches(1000)
